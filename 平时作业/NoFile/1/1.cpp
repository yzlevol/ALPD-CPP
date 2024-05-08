#include<iostream>
#include<sstream>
#include<fstream>
#include<string>
#include<time.h>
using namespace std;

bool is_gbk_chinese_char(unsigned char c1, unsigned char c2) {
    return (c1 >= 0x81 && c1 <= 0xFE && c2 >= 0x40 && c2 <= 0xFE && c2 != 0x7F);
}

//bool is_zh_string(string str)
//{
//        for (int i = 0; i < (int)(str.length()); i++) {
//            if ((unsigned char)str[i] > 0x7F) {  
//                if (i + 1 < (int)(str.length()) && is_gbk_chinese_char((unsigned char)str[i], (unsigned char)str[i + 1])) {
//                    return true;
//                }
//            }
//        }
//        return false;
//}
bool is_zh_string(const string& str) {
    const size_t len = str.length();
    for (size_t i = 0; i < len; ++i) {
        const unsigned char c = static_cast<unsigned char>(str[i]);
        if (c < 0x80) {  // 非汉字字符
            continue;
        }
        if (i + 1 < len) {
            const unsigned char c2 = static_cast<unsigned char>(str[i + 1]);
            if (c >= 0x81 && c <= 0xFE && c2 >= 0x40 && c2 <= 0xFE && c2 != 0x7F) {
                return true;  // 是汉字字符
            }
        }
        return false;  // 不是汉字字符，直接返回
    }
    return false;  // 没有汉字字符
}

//bool is_zh_string(const std::string& str) {
//    for (int i = 0; i < str.length(); i++) {
//        if ((unsigned char)str[i] > 0x7F) {
//            if (i + 1 < str.length() && is_gbk_chinese_char((unsigned char)str[i], (unsigned char)str[i + 1])) {
//                return true;
//            }
//        }
//    }
//    return false;
//}


bool valid(string thisline)
{
    bool is_number = true;
    if (!is_zh_string(thisline)) {
        for (char c : thisline)
        {
            if (!(c>=48&&c<=57)) {
                is_number = false;
                break;
            }
        }
        if (is_number)
            return 1;
        else
            return 0;
    }
    else
        return 0;
}

int main(int argc, char* argv[]) {
    clock_t start1 = clock();    // the code need to measure time    

    int count = 0;
    if (argc != 3) {
        cerr << "请给出文件名和前三位号码" << endl;
        return -1;
    }
    ifstream in(argv[1]);
    if (!in) {
        cerr << "无法打开输入文件" << endl;
        return -1;
    }
    else {
        if (atoi(argv[2]) >= 130 && atoi(argv[2]) <= 199) {
            stringstream first(argv[2], 3);
            string eveline;
            string resultmax ;
            bool is_first_same = 1;
            //循环每一行
            while (!in.eof()) {
                //in >> eveline;
                getline(in, eveline);
                if (valid(eveline)) {
                    is_first_same = (eveline.substr(0, 3).compare(first.str()) == 0);
                    if (is_first_same) {
                        if (eveline.length() == 11) {
                            count++;
                            if (resultmax < eveline)
                                resultmax = eveline;
                        }
                    }
                }
                else
                    continue;
            }
            //cout << "Found " << count << "." << endl;
            cout << resultmax << endl;
        }
        else {
            return -1;
        }
    }
    /* 通过argv[2]查找所有合法信息，并输出所匹配的最大值 */
    /* 需要注意argv均为字符串类型，你可能需要对该参数进行转换 */
    clock_t end1 = clock();
    double timeSpend = (double)((end1) - (start1)) / CLOCKS_PER_SEC; //得到的结果是秒，(end-start)得到的结果是毫秒
    cout << "#" << timeSpend << "#" << endl;
    return 0;
}

