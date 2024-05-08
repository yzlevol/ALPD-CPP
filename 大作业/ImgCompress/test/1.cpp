#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <bitset>

// Huffman���ڵ�
struct HuffmanNode {
    int frequency;
    unsigned char pixel;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(int freq, unsigned char pix) : frequency(freq), pixel(pix), left(nullptr), right(nullptr) {}
};

// �ȽϺ��������ڹ������ȶ���
struct Compare {
    bool operator()(HuffmanNode* a, HuffmanNode* b) {
        return a->frequency > b->frequency;
    }
};

// ����Huffman��
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

// ����Huffman�����
void buildHuffmanTable(HuffmanNode* node, const std::string& code, std::unordered_map<unsigned char, std::string>& table) {
    if (node->left == nullptr && node->right == nullptr) {
        table[node->pixel] = code;
        return;
    }

    buildHuffmanTable(node->left, code + "0", table);
    buildHuffmanTable(node->right, code + "1", table);
}

// ѹ������
std::vector<unsigned char> compressHuffman(const std::vector<unsigned char>& data) {
    std::unordered_map<unsigned char, int> frequencies;

    // ͳ��ÿ������ֵ��Ƶ��
    for (unsigned char pixel : data) {
        ++frequencies[pixel];
    }

    HuffmanNode* root = buildHuffmanTree(frequencies);
    std::unordered_map<unsigned char, std::string> huffmanTable;
    buildHuffmanTable(root, "", huffmanTable);

    std::vector<unsigned char> compressedData;
    std::string encodedBits;

    // ��ÿ������ֵ����ΪHuffman����
    for (unsigned char pixel : data) {
        encodedBits += huffmanTable[pixel];

        // ÿ8λ�������һ�����
        while (encodedBits.length() >= 8) {
            std::bitset<8> bits(encodedBits.substr(0, 8));
            compressedData.push_back(bits.to_ulong());
            encodedBits = encodedBits.substr(8);
        }
    }

    // ʣ�಻��8λ�ı�����в�0�����
    if (!encodedBits.empty()) {
        std::bitset<8> bits(encodedBits);
        bits <<= (8 - encodedBits.length());
        compressedData.push_back(bits.to_ulong());
    }

    return compressedData;
}

// ��ѹ������
std::vector<unsigned char> decompressHuffman(const std::vector<unsigned char>& compressedData, HuffmanNode* root, int originalSize) {
    std::vector<unsigned char> decompressedData;

    HuffmanNode* currentNode = root;
    for (unsigned char byte : compressedData) {
        std::bitset<8> bits(byte);

        // ����ÿ������λ
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

    // ����ѹ�����ݽض�Ϊԭʼ��С
    decompressedData.resize(originalSize);

    return decompressedData;
}

int main() {
    // ��ȡԭʼͼ������
    std::vector<unsigned char> image = { /* ԭʼͼ������ */ };

    // ѹ��ͼ������
    std::vector<unsigned char> compressedData = compressHuffman(image);

    // ��ѹ��ͼ������
    HuffmanNode* root = buildHuffmanTree(frequencies);
    std::vector<unsigned char> decompressedData = decompressHuffman(compressedData, root, image.size());

    // ��ӡѹ��ǰ���ͼ�����ݴ�С
    std::cout << "Original size: " << image.size() << " bytes" << std::endl;
    std::cout << "Compressed size: " << compressedData.size() << " bytes" << std::endl;

    return 0;
}

