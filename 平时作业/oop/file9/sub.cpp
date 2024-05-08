/* sub.cpp */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

class TString
{
private:
    char* content; // 指向字符串的指针
    int   len;     // 字符串的长度，不含尾零
public:
    TString(char* s = NULL);
    TString(const TString&);
    ~TString();
    char* get_content();
    void set(char* s = NULL);
    void set(const TString&);
    int length();
};

TString::TString(char* s)
{
    content = s;
    //len = length();
}
TString::TString(const TString& str)
{
    content = str.content;
    len = str.len;
}
TString::~TString()
{
    cout << endl;
}
char* TString::get_content()
{
    return content;
}
void TString::set(char* s)
{
    content = s;
    //len = length();
}
void TString::set(const TString& str)
{
    content = str.content;
    len=str.len;
}
int TString::length()
{
    if (content == NULL && len == 0)
        return 0;
    else {
        int i = 0;
        for (char* p = content; *p; ++p, ++i);
        return i;
    }
}
