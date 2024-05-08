#pragma once
#include<iostream>
#include<fstream>
#include<ctime>
#include<iomanip>
#include<string>
#include <queue>
using namespace std;


//获取文件大小
int get_osize(ofstream& ff);
int get_isize(ifstream& ff);
int getfilesize(const string file);

//Huffman
struct Node; //声明 哈夫曼节点
struct Compare;//声明 比较左右  
void Huffman_encode(Node* root, vector<pair<char, string>>& huffmanCode);              //哈夫曼编码
void freeHuffmanTree(Node* root);                                                      //释放哈夫曼树
int huffman_compress(const std::string& input, const std::string& output,int FileSize);//哈夫曼压缩函数
void huffman_decompress(const std::string& input, const std::string& output);          //哈夫曼解压函数

 