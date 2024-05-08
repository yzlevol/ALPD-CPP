#pragma once
#include<iostream>
#include<fstream>
#include<ctime>
#include<iomanip>
#include<string>
#include <queue>
using namespace std;


//��ȡ�ļ���С
int get_osize(ofstream& ff);
int get_isize(ifstream& ff);
int getfilesize(const string file);

//Huffman
struct Node; //���� �������ڵ�
struct Compare;//���� �Ƚ�����  
void Huffman_encode(Node* root, vector<pair<char, string>>& huffmanCode);              //����������
void freeHuffmanTree(Node* root);                                                      //�ͷŹ�������
int huffman_compress(const std::string& input, const std::string& output,int FileSize);//������ѹ������
void huffman_decompress(const std::string& input, const std::string& output);          //��������ѹ����

 