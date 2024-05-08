#include"FileHead.h"

struct Node {    //���������ڵ�
    char ch;     //�ڵ��ַ�
    int freq;    //�ַ�Ƶ��
    Node* left;  //���ӽڵ�
    Node* right; //���ӽڵ�

    Node(char ch, int freq) : ch(ch), freq(freq), left(nullptr), right(nullptr) {};
};

struct Compare {
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

// ���ɹ���������
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
int huffman_compress(const string& input, const string& output, int fileSize) {
    ifstream inFile(input, ios::binary);
    ofstream outFile(output, ios::binary);

    const int MAX_CHAR = 256; // ASCII �ַ������� 256 ���ַ�
    int freq[MAX_CHAR] = { 0 }; // �洢�ַ�Ƶ�ʵ�����

    char ch;
    // ��ȡ�ļ��������ַ�Ƶ��
    while (inFile.get(ch)) {
        freq[(int)ch]++;
    }

    // �������ȼ����У����ڹ�����������
    priority_queue<Node*, vector<Node*>, Compare> pq;
    for (int i = 0; i < MAX_CHAR; ++i) {
        if (freq[i] != 0) {
            pq.push(new Node(char(i), freq[i]));
        }
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


        // ���ɹ���������
        string huffmanCode[MAX_CHAR];
    Huffman_encode(root, "", huffmanCode);


        // д���ַ�Ƶ�ʱ�
        outFile << pq.size() << "\n";
    for (int i = 0; i < MAX_CHAR; ++i) {
        if (freq[i] != 0) {
            outFile << char(i) << " " << freq[i] << "\n";
        }
    }

    // �����ļ���ȡλ�ã�׼����ʼѹ��
    inFile.clear();
    inFile.seekg(0, ios::beg);

    // ��ʼѹ��
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

    // д��ʣ��Ĳ��� 8 λ������
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

    // �ͷ��ڴ�
    freeHuffmanTree(root);

    // �ر��ļ�
    inFile.close();
    outFile.close();

    // ����ѹ����
    return (int)((1 - (double)(get_osize(outFile)) / fileSize) * 100);
}

// ��ѹ����
void huffman_decompress(const string& input, const string& output) {
    ifstream inFile(input, ios::binary);
    ofstream outFile(output, ios::binary);


        // ��ȡ�ַ�Ƶ�ʱ�
        int numSymbols;
    inFile >> numSymbols;
    inFile.get(); // ��ȡ���з�
    int freq[256] = { 0 };
    for (int i = 0; i < numSymbols; ++i) {
        char ch;
        int f;
        inFile.get(ch);
        inFile >> f;
        inFile.get(); // ��ȡ���з�
        freq[(int)ch] = f;
    }

    // �������ȼ����У����ڹ�����������
    priority_queue<Node*, vector<Node*>, Compare> pq;
    for (int i = 0; i < 256; ++i) {
        if (freq[i] != 0) {
            pq.push(new Node(char(i), freq[i]));
        }
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

    // ��ѹ��
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

    // �ͷ��ڴ�
    freeHuffmanTree(root);

    // �ر��ļ�
    inFile.close();
    outFile.close();
}