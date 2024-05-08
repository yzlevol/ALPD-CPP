#include"FileHead.h"

struct Node {    //哈夫曼树节点
    char ch;     //节点字符
    int freq;    //字符频率
    Node* left;  //左子节点
    Node* right; //右子节点

    Node(char ch, int freq) : ch(ch), freq(freq), left(nullptr), right(nullptr) {};
};

struct Compare {
    bool operator()(Node* left, Node* right) {
        return left->freq > right->freq;
    }
};

int lastProgress = 0;
bool flag = 1;
// 进度条显示函数
void showProgressBar(double progress) {
    progress *= 100;
    if (int(progress) == lastProgress)
        flag = 0;
    else
        flag = 1;
    if (flag == 0) {
        return;
    }
    else {
        int barWidth = 70;
        cout << "[";
        int pos = (int)(barWidth * progress / 100);
        for (int i = 0; i < barWidth; ++i) {
            if (i < pos) cout << "=";
            else if (i == pos) cout << ">";
            else cout << " ";
        }
        cout << "] " << setw(3) << static_cast<int>(progress * 1.0) << "%\r";
        cout.flush();
        lastProgress = (int)progress;
    }
}

int get_osize(ofstream& ff)
{
    streampos currentPosition = ff.tellp();
    ff.seekp(0, ios::end);
    int size = (int)ff.tellp();
    ff.seekp(currentPosition);
    return size;
}
int get_isize(ifstream& ff)
{
    streampos currentPosition = ff.tellg();
    ff.seekg(0, ios::end);
    int size = (int)ff.tellg();
    ff.seekg(currentPosition);
    return size;
}
int getfilesize(const string file)
{
    ifstream fp(file, ios::binary);
    if (fp.is_open()) {
        fp.seekg(0, ios::end);
        int fileSize = (int)fp.tellg();
        fp.close();
        return fileSize;
    }
    return -1;
}

// 生成哈夫曼编码
void Huffman_encode(Node* root, string str, string* huffmanCode) {
    if (root == nullptr) {
        return;
    }
    if (!root->left && !root->right) {
        huffmanCode[(int)root->ch] = str;
    }
    Huffman_encode(root->left, str + "0", huffmanCode);
    Huffman_encode(root->right, str + "1", huffmanCode);
}

// 释放哈夫曼树
void freeHuffmanTree(Node* root) {
    if (root == nullptr) {
        return;
    }
    freeHuffmanTree(root->left);
    freeHuffmanTree(root->right);
    delete root;
}


// 压缩函数
int huffman_compress(const string& input, const string& output, int fileSize) {
    ifstream inFile(input, ios::binary);
    ofstream outFile(output, ios::binary);

    const int MAX_CHAR = 256; // ASCII 字符集共有 256 个字符
    int freq[MAX_CHAR] = { 0 }; // 存储字符频率的数组

    char ch;
    // 读取文件并计算字符频率
    while (inFile.get(ch)) {
        freq[(int)ch]++;
    }

    // 创建优先级队列，用于构建哈夫曼树
    priority_queue<Node*, vector<Node*>, Compare> pq;
    for (int i = 0; i < MAX_CHAR; ++i) {
        if (freq[i] != 0) {
            pq.push(new Node(char(i), freq[i]));
        }
    }

    // 构建哈夫曼树
    while (pq.size() != 1) {
        Node* left = pq.top();
        pq.pop();
        Node* right = pq.top();
        pq.pop();
        int sum = left->freq + right->freq;
        Node* parent = new Node('\0', sum);
        parent->left = left;
        parent->right = right;
        pq.push(parent);
    }

    Node* root = pq.top();


        // 生成哈夫曼编码
        string huffmanCode[MAX_CHAR];
    Huffman_encode(root, "", huffmanCode);


        // 写入字符频率表
        outFile << pq.size() << "\n";
    for (int i = 0; i < MAX_CHAR; ++i) {
        if (freq[i] != 0) {
            outFile << char(i) << " " << freq[i] << "\n";
        }
    }

    // 重置文件读取位置，准备开始压缩
    inFile.clear();
    inFile.seekg(0, ios::beg);

    // 开始压缩
    string buffer = "";
    int bitCount = 0;
    char outByte = 0;
    while (inFile.get(ch)) {
        buffer += huffmanCode[(int)ch];
        while (buffer.length() >= 8) {
            for (int i = 0; i < 8; ++i) {
                outByte <<= 1;
                if (buffer[i] == '1') {
                    outByte |= 1;
                }
            }
            outFile.put(outByte);
            bitCount += 8;
            buffer.erase(0, 8);
        }
    }

    // 写入剩余的不足 8 位的数据
    if (buffer.length() > 0) {
        while (buffer.length() < 8) {
            buffer += '0';
        }
        for (int i = 0; i < 8; ++i) {
            outByte <<= 1;
            if (buffer[i] == '1') {
                outByte |= 1;
            }
        }
        outFile.put(outByte);
        bitCount += 8;
    }

    // 释放内存
    freeHuffmanTree(root);

    // 关闭文件
    inFile.close();
    outFile.close();

    // 返回压缩率
    return (int)((1 - (double)(get_osize(outFile)) / fileSize) * 100);
}

// 解压函数
void huffman_decompress(const string& input, const string& output) {
    ifstream inFile(input, ios::binary);
    ofstream outFile(output, ios::binary);


        // 读取字符频率表
        int numSymbols;
    inFile >> numSymbols;
    inFile.get(); // 读取换行符
    int freq[256] = { 0 };
    for (int i = 0; i < numSymbols; ++i) {
        char ch;
        int f;
        inFile.get(ch);
        inFile >> f;
        inFile.get(); // 读取换行符
        freq[(int)ch] = f;
    }

    // 创建优先级队列，用于构建哈夫曼树
    priority_queue<Node*, vector<Node*>, Compare> pq;
    for (int i = 0; i < 256; ++i) {
        if (freq[i] != 0) {
            pq.push(new Node(char(i), freq[i]));
        }
    }

    // 构建哈夫曼树
    while (pq.size() != 1) {
        Node* left = pq.top();
        pq.pop();
        Node* right = pq.top();
        pq.pop();
        int sum = left->freq + right->freq;
        Node* parent = new Node('\0', sum);
        parent->left = left;
        parent->right = right;
        pq.push(parent);
    }

    Node* root = pq.top();

    // 解压缩
    int bitCount = 0;
    Node* currentNode = root;
    char ch;
    while (inFile.get(ch)) {
        for (int i = 7; i >= 0; --i) {
            bool bit = (ch >> i) & 1;
            if (bit) {
                currentNode = currentNode->right;
            }
            else {
                currentNode = currentNode->left;
            }
            if (!currentNode->left && !currentNode->right) {
                outFile.put(currentNode->ch);
                currentNode = root;
            }
            bitCount++;
        }
        showProgressBar((double)bitCount / get_isize(inFile));
    }

    // 释放内存
    freeHuffmanTree(root);

    // 关闭文件
    inFile.close();
    outFile.close();
}