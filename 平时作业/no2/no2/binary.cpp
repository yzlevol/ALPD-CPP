#include<iostream>
#include<iomanip>
using namespace std;

void itobs(int num, char* buffer) {
    /* 将整数转换为二进制并存入 buffer 字符串 */

    for (int j = 31; j >= 0; j--) {
        if (num & (1 << j))
            buffer[j] = 1;
        else
            buffer[j] = 0;
    }
    /* 例：1964 的二进制是：00000000 00000000 00000111 10101100 */
    cout << num << " 的二进制是：";
    for (int i = 31; i >= 0; i--) {
        if ((i+1) % 8 == 0)
            cout << " ";
        cout << (int)buffer[i];
    }
    //cout << endl;
    cout << " ";
}

int main()
{
    char buffer[33];
    int num;
    cout << "输入一些整数： " << endl;
    while (1) {
        //cout << "请输入int32 (4 字节有符号整数)" << endl;
        cin >> num;
        if (cin.good() == 1)
            itobs(num, buffer);
        else
            break;
    }
    cout << "------程序结束------" << endl;
	return 0;
}