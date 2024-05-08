#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <bitset>

// Huffman树节点
struct HuffmanNode {
    int frequency;
    unsigned char pixel;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(int freq, unsigned char pix) : frequency(freq), pixel(pix), left(nullptr), right(nullptr) {}
};

// 比较函数，用于构建优先队列
struct Compare {
    bool operator()(HuffmanNode* a, HuffmanNode* b) {
        return a->frequency > b->frequency;
    }
};

// 构建Huffman树
HuffmanNode* buildHuffmanTree(const std::unordered_map<unsigned char, int>& frequencies) {
    std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, Compare> pq;
    for (const auto& pair : frequencies) {
        pq.push(new HuffmanNode(pair.second, pair.first));
    }

    while (pq.size() > 1) {
        HuffmanNode* left = pq.top();
        pq.pop();
        HuffmanNode* right = pq.top();
        pq.pop();

        HuffmanNode* parent = new HuffmanNode(left->frequency + right->frequency, 0);
        parent->left = left;
        parent->right = right;
        pq.push(parent);
    }

    HuffmanNode* root = pq.top();
    pq.pop();
    return root;
}

// 构建Huffman编码表
void buildHuffmanTable(HuffmanNode* node, const std::string& code, std::unordered_map<unsigned char, std::string>& table) {
    if (node->left == nullptr && node->right == nullptr) {
        table[node->pixel] = code;
        return;
    }

    buildHuffmanTable(node->left, code + "0", table);
    buildHuffmanTable(node->right, code + "1", table);
}

// 压缩数据
std::vector<unsigned char> compressHuffman(const std::vector<unsigned char>& data) {
    std::unordered_map<unsigned char, int> frequencies;

    // 统计每个像素值的频率
    for (unsigned char pixel : data) {
        ++frequencies[pixel];
    }

    HuffmanNode* root = buildHuffmanTree(frequencies);
    std::unordered_map<unsigned char, std::string> huffmanTable;
    buildHuffmanTable(root, "", huffmanTable);

    std::vector<unsigned char> compressedData;
    std::string encodedBits;

    // 将每个像素值编码为Huffman编码
    for (unsigned char pixel : data) {
        encodedBits += huffmanTable[pixel];

        // 每8位编码进行一次输出
        while (encodedBits.length() >= 8) {
            std::bitset<8> bits(encodedBits.substr(0, 8));
            compressedData.push_back(bits.to_ulong());
            encodedBits = encodedBits.substr(8);
        }
    }

    // 剩余不足8位的编码进行补0并输出
    if (!encodedBits.empty()) {
        std::bitset<8> bits(encodedBits);
        bits <<= (8 - encodedBits.length());
        compressedData.push_back(bits.to_ulong());
    }

    return compressedData;
}

// 解压缩数据
std::vector<unsigned char> decompressHuffman(const std::vector<unsigned char>& compressedData, HuffmanNode* root, int originalSize) {
    std::vector<unsigned char> decompressedData;

    HuffmanNode* currentNode = root;
    for (unsigned char byte : compressedData) {
        std::bitset<8> bits(byte);

        // 遍历每个比特位
        for (int i = 7; i >= 0; --i) {
            if (currentNode->left == nullptr && currentNode->right == nullptr) {
                decompressedData.push_back(currentNode->pixel);
                currentNode = root;
            }

            currentNode = (bits[i] == 0) ? currentNode->left : currentNode->right;
        }
    }

    if (currentNode->left == nullptr && currentNode->right == nullptr) {
        decompressedData.push_back(currentNode->pixel);
    }

    // 将解压缩数据截断为原始大小
    decompressedData.resize(originalSize);

    return decompressedData;
}

int main() {
    // 读取原始图像数据
    std::vector<unsigned char> image = { /* 原始图像数据 */ };

    // 压缩图像数据
    std::vector<unsigned char> compressedData = compressHuffman(image);

    // 解压缩图像数据
    HuffmanNode* root = buildHuffmanTree(frequencies);
    std::vector<unsigned char> decompressedData = decompressHuffman(compressedData, root, image.size());

    // 打印压缩前后的图像数据大小
    std::cout << "Original size: " << image.size() << " bytes" << std::endl;
    std::cout << "Compressed size: " << compressedData.size() << " bytes" << std::endl;

    return 0;
}

