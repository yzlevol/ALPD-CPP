#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstring>
#include <ctime>

using namespace std;

bool is_gbk_chinese_char(unsigned char c1, unsigned char c2) {
    return (c1 >= 0x81 && c1 <= 0xFE && c2 >= 0x40 && c2 <= 0xFE && c2 != 0x7F);
}

bool is_zh_string(const char* str) {
    const size_t len = strlen(str);
    for (size_t i = 0; i < len; ++i) {
        const unsigned char c = static_cast<unsigned char>(str[i]);
        if (c < 0x80) { 
            continue;
        }
        if (i + 1 < len) {
            const unsigned char c2 = static_cast<unsigned char>(str[i + 1]);
            if (c >= 0x81 && c <= 0xFE && c2 >= 0x40 && c2 <= 0xFE && c2 != 0x7F) {
                return true; 
            }
            else {
                return false; 
            }
        }
    }
    return false; 
}

bool valid(const char* thisline) {
    if (!is_zh_string(thisline)) {
        for (size_t i = 0; i < strlen(thisline); ++i) {
            if (!(thisline[i] >= '0' && thisline[i] <= '9')) {
                return false;
            }
        }
        return (strlen(thisline) == 11);
    }
    else {
        return false;
    }
}

int main(int argc, char* argv[]) {
    int count = 0;
    if (argc != 3) {
        cerr << "������ļ�����ǰ��λ����" << endl;
        return -1;
    }
    ifstream in(argv[1]);
    if (!in) {
        cerr << "�޷��������ļ�" << endl;
        return -1;
    }
    else {
        if (atoi(argv[2]) >= 130 && atoi(argv[2]) <= 199) {
            stringstream first(argv[2], 3);
            char eveline[1024];
            char resultmax[12] = "";
            bool is_first_same = true;
            //ѭ��ÿһ��
            while (in.getline(eveline, 1024)) {
                if (valid(eveline)) {
                    is_first_same = (strncmp(eveline, first.str().c_str(), 3) == 0);
                    if (is_first_same) {
                        if (strlen(eveline) == 11) {
                            count++;
                            if (strcmp(resultmax, eveline) < 0) {
                                strcpy(resultmax, eveline);
                            }
                        }
                    }
                }
            }
            cout << resultmax << endl;
        }
        else {
            return -1;
        }
    }
    /* ͨ��argv[2]�������кϷ���Ϣ���������ƥ������ֵ */
    /* ��Ҫע��argv��Ϊ�ַ������ͣ��������Ҫ�Ըò�������ת�� */
    return 0;
}
