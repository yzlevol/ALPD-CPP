#include"FileHead.h"

struct Node {    //哈夫曼树节点
    char ch;     //节点字符
    int freq;    //字符频率
    Node* left;  //左子节点
    Node* right; //右子节点

    Node(char ch, int freq) : ch(ch), freq(freq), left(nullptr), right(nullptr) {};
};

struct Compare {   //用于优先队列比较
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
    if (flag==0) {
        return;
    }
    else {
        int barWidth = 70;
        cout << "[";
        int pos = (int)(barWidth * progress/100);
        for (int i = 0; i < barWidth; ++i) {
            if (i < pos) cout << "=";
            else if (i == pos) cout << ">";
            else cout << " ";
        }
        cout << "] " << setw(3) << static_cast<int>(progress*1.0) << "%\r";
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
void Huffman_encode(Node* root, vector<pair<char, string>>& huffmanCode) {
    if (root == nullptr) {
        return;
    }

    queue<pair<Node*, string>> q;
    q.push({ root, "" });

    while (!q.empty()) {
        Node* node = q.front().first;
        string code = q.front().second;
        q.pop();

        if (!node->left && !node->right) {
            huffmanCode.push_back({ node->ch, code });
        }

        if (node->left) {
            q.push({ node->left, code + "0" });
        }
        if (node->right) {
            q.push({ node->right, code + "1" });
        }
    }
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

int huffman_compress(const string& input, const string& output, int FileSize) {
    ifstream inFile(input, ios::binary);
    ofstream outFile(output, ios::binary);

    vector<pair<char, int>> freq;

    // 读取文件并计算字符频率
    char ch;
    while (inFile.get(ch)) {
        bool found = false;
        for (size_t i = 0; i < freq.size(); ++i) {
            if (freq[i].first == ch) {
                freq[i].second++;
                found = true;
                break;
            }
        }
        if (!found) {
            freq.push_back({ ch, 1 });
        }
    }


    // 优先队列 构建哈夫曼树
    priority_queue<Node*, vector<Node*>, Compare> pq;
    int freqSize = (int)freq.size();
    for (int i = 0; i < freqSize; ++i) {
        pq.push(new Node(freq[i].first, freq[i].second));
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
    Node* root = pq.top(); //根

    // 生成哈夫曼编码
    vector<pair<char, string>> huffmanCode;
    Huffman_encode(root, huffmanCode);

    // 写入字符频率表
    outFile << freq.size() << "\n";
    int freqSize0 = (int)freq.size();
    for (int i = 0; i < freqSize0; ++i) {
        outFile << freq[i].first << " " << freq[i].second << "\n";
    }


    // 重置文件指针
    inFile.clear();
    inFile.seekg(0);

    // 压缩数据
    string compressedData;
    size_t huffmanCodeSize = huffmanCode.size();
    while (inFile.get(ch)) {
        for (size_t i = 0; i < huffmanCodeSize; ++i) {
            if (huffmanCode[i].first == ch) {
                compressedData += huffmanCode[i].second;
                break;
            }
        }
        // 显示进度条
        double progress = static_cast<double>(inFile.tellg()) / FileSize;
        showProgressBar(progress);
    }


    // 将压缩后的二进制数据转换为字节
    int padding = 8 - (compressedData.length() % 8);
    compressedData += string(padding, '0');
    outFile << padding << "\n";

    uint8_t byte = 0;
    int bitCount = 0;
    for (size_t i = 0; i < compressedData.length(); ++i) {
        byte <<= 1;
        if (compressedData[i] == '1') {
            byte |= 1;
        }
        ++bitCount;
        if (bitCount == 8) {
            outFile.put(byte);
            byte = 0;
            bitCount = 0;
        }
    }

    // 释放哈夫曼树
    freeHuffmanTree(root);

    int size1 = get_osize(outFile);
    inFile.close();
    outFile.close();
    return size1;
}


// 解压函数
void huffman_decompress(const string& input, const string& output) {
    int FileSize = getfilesize(input);
    ifstream inFile(input, ios::binary);
    ofstream outFile(output, ios::binary);

    size_t numChars;
    inFile >> numChars;

    // 读取字符频率
    vector<pair<char, int>> freq;
    char ch;
    int f;
    for (size_t i = 0; i < numChars; ++i) {
        inFile.get(ch); // 读取空格
        inFile.get(ch);
        inFile >> f;
        freq.push_back(make_pair(ch, f));
    }

    // 优先队列 构建哈夫曼树
    priority_queue<Node*, vector<Node*>, Compare> pq;

    for (size_t i = 0; i < freq.size(); ++i) {
        pq.push(new Node(freq[i].first, freq[i].second));
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

    // 读取填充位
    int padding;
    inFile >> padding;
    inFile.get(ch); // 读取换行符

    // 解压数据
    Node* current = root;
    while (inFile.get(ch)) {
        uint8_t bits = static_cast<uint8_t>(ch);
        for (int i = 0; i < 8; ++i) {
            current = (bits & (1 << (7 - i))) ? current->right : current->left;
            if (!current->left && !current->right) {
                outFile.put(current->ch);
                current = root;
            }
        }
        // 计算进度并显示进度条
        double progress = static_cast<double>(inFile.tellg()) / FileSize;
        showProgressBar(progress);
    }

    // 移除填充位
    outFile.seekp(-padding, ios::end);
    outFile.write("", 1);

    // 释放哈夫曼树
    freeHuffmanTree(root);

    inFile.close();
    outFile.close();
}

