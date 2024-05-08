#include"FileHead.h"

struct Node {    //���������ڵ�
    char ch;     //�ڵ��ַ�
    int freq;    //�ַ�Ƶ��
    Node* left;  //���ӽڵ�
    Node* right; //���ӽڵ�

    Node(char ch, int freq) : ch(ch), freq(freq), left(nullptr), right(nullptr) {};
};

struct Compare {   //�������ȶ��бȽ�
    bool operator()(Node* left, Node* right) {
        return left->freq > right->freq;  
    }
};

int lastProgress = 0;
bool flag = 1;
// ��������ʾ����
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
// ���ɹ���������
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


// �ͷŹ�������
void freeHuffmanTree(Node* root) {
    if (root == nullptr) {
        return;
    }
    freeHuffmanTree(root->left);
    freeHuffmanTree(root->right);
    delete root;
}

// ѹ������

int huffman_compress(const string& input, const string& output, int FileSize) {
    ifstream inFile(input, ios::binary);
    ofstream outFile(output, ios::binary);

    vector<pair<char, int>> freq;

    // ��ȡ�ļ��������ַ�Ƶ��
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


    // ���ȶ��� ������������
    priority_queue<Node*, vector<Node*>, Compare> pq;
    int freqSize = (int)freq.size();
    for (int i = 0; i < freqSize; ++i) {
        pq.push(new Node(freq[i].first, freq[i].second));
    }

    // ������������
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
    Node* root = pq.top(); //��

    // ���ɹ���������
    vector<pair<char, string>> huffmanCode;
    Huffman_encode(root, huffmanCode);

    // д���ַ�Ƶ�ʱ�
    outFile << freq.size() << "\n";
    int freqSize0 = (int)freq.size();
    for (int i = 0; i < freqSize0; ++i) {
        outFile << freq[i].first << " " << freq[i].second << "\n";
    }


    // �����ļ�ָ��
    inFile.clear();
    inFile.seekg(0);

    // ѹ������
    string compressedData;
    size_t huffmanCodeSize = huffmanCode.size();
    while (inFile.get(ch)) {
        for (size_t i = 0; i < huffmanCodeSize; ++i) {
            if (huffmanCode[i].first == ch) {
                compressedData += huffmanCode[i].second;
                break;
            }
        }
        // ��ʾ������
        double progress = static_cast<double>(inFile.tellg()) / FileSize;
        showProgressBar(progress);
    }


    // ��ѹ����Ķ���������ת��Ϊ�ֽ�
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

    // �ͷŹ�������
    freeHuffmanTree(root);

    int size1 = get_osize(outFile);
    inFile.close();
    outFile.close();
    return size1;
}


// ��ѹ����
void huffman_decompress(const string& input, const string& output) {
    int FileSize = getfilesize(input);
    ifstream inFile(input, ios::binary);
    ofstream outFile(output, ios::binary);

    size_t numChars;
    inFile >> numChars;

    // ��ȡ�ַ�Ƶ��
    vector<pair<char, int>> freq;
    char ch;
    int f;
    for (size_t i = 0; i < numChars; ++i) {
        inFile.get(ch); // ��ȡ�ո�
        inFile.get(ch);
        inFile >> f;
        freq.push_back(make_pair(ch, f));
    }

    // ���ȶ��� ������������
    priority_queue<Node*, vector<Node*>, Compare> pq;

    for (size_t i = 0; i < freq.size(); ++i) {
        pq.push(new Node(freq[i].first, freq[i].second));
    }

     // ������������
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

    // ��ȡ���λ
    int padding;
    inFile >> padding;
    inFile.get(ch); // ��ȡ���з�

    // ��ѹ����
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
        // ������Ȳ���ʾ������
        double progress = static_cast<double>(inFile.tellg()) / FileSize;
        showProgressBar(progress);
    }

    // �Ƴ����λ
    outFile.seekp(-padding, ios::end);
    outFile.write("", 1);

    // �ͷŹ�������
    freeHuffmanTree(root);

    inFile.close();
    outFile.close();
}

