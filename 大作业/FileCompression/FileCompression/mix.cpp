#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <bitset>
#include <queue>

const int WINDOW_SIZE = 1024;
const int BUFFER_SIZE = 256;

struct Node {
    char ch;
    int freq;
    int left;
    int right;

    Node(char ch, int freq, int left = -1, int right = -1) : ch(ch), freq(freq), left(left), right(right) {}
};

// 自定义比较器
struct Compare {
    bool operator()(const Node& left, const Node& right) {
        return left.freq > right.freq;
    }
};

void compress(const std::string& input, const std::string& output) {
    std::ifstream inFile(input, std::ios::binary);
    if (!inFile.is_open()) {
        std::cerr << "Failed to open input file!\n";
        return;
    }

    std::ofstream outFile(output, std::ios::binary);
    if (!outFile.is_open()) {
        std::cerr << "Failed to create output file!\n";
        return;
    }

    std::vector<char> window(WINDOW_SIZE, '\0');
    std::unordered_map<std::string, int> buffer;

    std::vector<Node> huffmanTree;
    std::unordered_map<char, std::string> huffmanCode;

    while (true) {
        // 读取WINDOW_SIZE个字符到窗口中
        std::fill(window.begin(), window.end(), '\0');
        inFile.read(window.data(), WINDOW_SIZE);

        if (inFile.eof()) {
            break;
        }

        // 查找最长匹配
        int maxLen = 0;
        int maxOffset = 0;
        for (int j = 1; j <= WINDOW_SIZE; j++) {
            std::string subStr(window.begin(), window.begin() + j);
            if (buffer.count(subStr)) {
                maxOffset = buffer[subStr];
                maxLen = j;
            }
        }

        // 将匹配结果写入输出文件
        if (maxLen > 0 && maxOffset >= 0) {
            int offset = maxOffset;
            int length = maxLen;

            outFile.write(reinterpret_cast<const char*>(&offset), sizeof(offset));
            outFile.write(reinterpret_cast<const char*>(&length), sizeof(length));

            char ch;
            inFile.get(ch);
            outFile.put(ch);

            window.erase(window.begin(), window.begin() + maxLen);
            buffer.clear();
        }
        else {
            char ch = window[0];
            outFile.write(reinterpret_cast<const char*>(&ch), sizeof(ch));

            window.erase(window.begin());
            buffer.clear();
        }

        // 更新字典
        std::string matchStr(window.end() - maxLen, window.end());
        matchStr.push_back(inFile.peek());
        buffer[matchStr] = WINDOW_SIZE - static_cast<int>(window.size());

        // 构造哈夫曼树
        std::unordered_map<char, int> freq;
        for (char c : window) {
            freq[c]++;
        }

        std::priority_queue<Node, std::vector<Node>, Compare> pq;
        for (const auto& pair : freq) {
            pq.push(Node(pair.first, pair.second));
        }

        while (pq.size() > 1) {
            Node left = pq.top(); pq.pop();
            Node right = pq.top(); pq.pop();

            huffmanTree.push_back(Node('\0', left.freq + right.freq, static_cast<int>(huffmanTree.size()), static_cast<int>(huffmanTree.size() + 1)));
            pq.push(Node('\0', left.freq + right.freq, static_cast<int>(huffmanTree.size() - 1), -1));
        }

        // 生成哈夫曼编码
        int rootIndex = static_cast<int>(huffmanTree.size() - 1);
        std::vector<bool> codeBits;
        for (char c : window) {
            Node current = huffmanTree[rootIndex];
            while (current.left != -1 && current.right != -1) {
                if (huffmanTree[current.left].ch == c) {
                    codeBits.push_back(false);
                    current = huffmanTree[current.left];
                }
                else {
                    codeBits.push_back(true);
                    current = huffmanTree[current.right];
                }
            }
        }

        Node current = huffmanTree[rootIndex];
        while (current.left != -1 && current.right != -1) {
            Node leftChild = huffmanTree[current.left];
            Node rightChild = huffmanTree[current.right];
            if (leftChild.ch == window.back()) {
                codeBits.push_back(false);
                current = leftChild;
            }
            else {
                codeBits.push_back(true);
                current = rightChild;
            }
        }

        std::string codeStr;
        for (bool bit : codeBits) {
            codeStr += (bit ? "1" : "0");
        }

        huffmanCode.clear();
        for (const auto& pair : freq) {
            char c = pair.first;
            std::string code;
            Node current = huffmanTree[rootIndex];
            while (current.left != -1 && current.right != -1) {
                Node leftChild = huffmanTree[current.left];
                Node rightChild = huffmanTree[current.right];
                if (leftChild.ch == c) {
                    code.push_back('0');
                    current = leftChild;
                }
                else {
                    code.push_back('1');
                    current = rightChild;
                }
            }
            huffmanCode[c] = code;
        }

        // 将哈夫曼编码转换为二进制
        int padding = 8 - (codeStr.length() % 8);
        codeStr += std::string(padding, '0');
        outFile.write(reinterpret_cast<const char*>(&padding), sizeof(padding));

        for (size_t i = 0; i < codeStr.length(); i += 8) {
            uint8_t byte = std::bitset<8>(codeStr.substr(i, 8)).to_ulong();
            outFile.put(byte);
        }

        huffmanTree.clear();
    }

    inFile.close();
    outFile.close();

    std::cout << "LZ77+Huffman compression complete. Compressed file saved to: " << output << "\n";
}

void decompress(const std::string& input, const std::string& output) {
    std::ifstream inFile(input, std::ios::binary);
    if (!inFile.is_open()) {
        std::cerr << "Failed to open input file!\n";
        return;
    }

    std::ofstream outFile(output, std::ios::binary);
    if (!outFile.is_open()) {
        std::cerr << "Failed to create output file!\n";
        return;
    }

    std::vector<char> window(WINDOW_SIZE, '\0');
    std::unordered_map<std::string, int> buffer;

    std::vector<Node> huffmanTree;
    std::unordered_map<std::string, char> huffmanCode;

    while (true) {
        // 如果已经到达文件末尾，则停止解压缩
        if (inFile.eof()) {
            break;
        }

        int maxOffset;
        int length;
        char ch;

        // 尝试读取最长匹配的偏移量和长度
        if (inFile.read(reinterpret_cast<char*>(&maxOffset), sizeof(maxOffset)) &&
            inFile.read(reinterpret_cast<char*>(&length), sizeof(length))) {
            // 从窗口中复制相应数量的字符到输出中
            for (int i = 0; i < length; i++) {
                outFile.put(window[maxOffset + i]);
            }

            // 读取一个字节并写入输出中
            inFile.get(ch);
            outFile.put(ch);

            // 将新的字符添加到窗口和字典中
            window.erase(window.begin(), window.begin() + length + 1);
            for (int i = 0; i <= length; i++) {
                window.push_back(ch);
                buffer[std::string(window.end() - i - 1, window.end())] = WINDOW_SIZE - static_cast<int>(window.size()) + i + 1;
            }
        }
        else {
            // 读取一个字节并写入输出中
            inFile.get(ch);
            outFile.put(ch);

            // 将新的字符添加到窗口和字典中
            window.erase(window.begin());
            window.push_back(ch);
            buffer.clear();
            for (int i = std::max(0, static_cast<int>(window.size()) - BUFFER_SIZE); i < static_cast<int>(window.size()); i++) {
                buffer[std::string(window.begin() + i, window.end())] = WINDOW_SIZE - static_cast<int>(window.size()) + i;
            }
        }

        // 如果字典中的项数达到了最大值，则清空字典
        if (buffer.size() >= 1 << 16) {
            buffer.clear();
        }

        // 如果当前窗口大小小于哈夫曼编码所需的最小长度，则不进行解压缩
        if (window.size() < huffmanTree.size()) {
            continue;
        }

        // 读取填充位数并计算出哈夫曼编码的长度
        int padding;
        inFile.read(reinterpret_cast<char*>(&padding), sizeof(padding));
        int codeLength = (WINDOW_SIZE - static_cast<int>(window.size())) * 8 - padding;

        // 读取哈夫曼编码并将其解码为字符
        std::string codeStr;
        for (int i = 0; i < codeLength; i += 8) {
            uint8_t byte;
            inFile.read(reinterpret_cast<char*>(&byte), sizeof(byte));
            codeStr += std::bitset<8>(byte).to_string();
        }
        codeStr.erase(codeLength);

        std::vector<char> codeBits;
        std::transform(codeStr.begin(), codeStr.end(), std::back_inserter(codeBits), [](char c) { return (c == '1'); });

        // 根据哈夫曼树解码字符
        std::string decodeStr;
        Node current = huffmanTree.back();
        for (char bit : codeBits) {
            if (bit) {
                current = huffmanTree[current.right];
            }
            else {
                current = huffmanTree[current.left];
            }

            if (current.left == -1 && current.right == -1) {
                decodeStr.push_back(current.ch);
                current = huffmanTree.back();
            }
        }

        // 如果解码的字符串不为空，则将其写入输出中并将其添加到窗口和哈夫曼编码表中
        if (!decodeStr.empty()) {
            outFile.write(decodeStr.data(), decodeStr.length());

            window.erase(window.begin(), window.begin() + decodeStr.length());
            for (char c : decodeStr) {
                window.push_back(c);
                buffer[std::string(window.end() - std::min(BUFFER_SIZE, static_cast<int>(window.size())), window.end())] = WINDOW_SIZE - static_cast<int>(window.size());
                huffmanCode[std::string(window.end() - 1, window.end())] = c;
            }

            // 如果哈夫曼编码表中的项数达到了最大值，则清空哈夫曼编码表
            if (huffmanCode.size() >= 1 << 16) {
                huffmanCode.clear();
            }
        }

        // 如果当前窗口大小达到了最大值，则重建哈夫曼树
        if (window.size() == WINDOW_SIZE) {
            std::unordered_map<char, int> freq;
            for (char c : window) {
                freq[c]++;
            }

            std::priority_queue<Node, std::vector<Node>, Compare> pq;
            for (const auto& pair : freq) {
                pq.push(Node(pair.first, pair.second));
            }

            while (pq.size() > 1) {
                Node left = pq.top(); pq.pop();
                Node right = pq.top(); pq.pop();

                huffmanTree.push_back(Node('\0', left.freq + right.freq, static_cast<int>(huffmanTree.size()), static_cast<int>(huffmanTree.size() + 1)));
                pq.push(Node('\0', left.freq + right.freq, static_cast<int>(huffmanTree.size() - 1), -1));
            }
        }
    }

    inFile.close();
    outFile.close();

    std::cout << "LZ77+Huffman decompression complete. Decompressed file saved to: " << output << "\n";
}

int main(int argc, char* argv[])
{
    if (argc < 4 || std::string(argv[1]) != "-c" && std::string(argv[1]) != "-d") {
        std::cerr << "Usage: " << argv[0] << " -c/-d input_file output_file\n";
        return 1;
    }
    std::string input = argv[2];
    std::string output = argv[3];

    if (std::string(argv[1]) == "-c") {
        compress(input, output);
    }
    else {
        decompress(input, output);
    }

    return 0;
}