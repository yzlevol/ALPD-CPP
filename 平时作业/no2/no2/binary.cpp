#include<iostream>
#include<iomanip>
using namespace std;

void itobs(int num, char* buffer) {
    /* ������ת��Ϊ�����Ʋ����� buffer �ַ��� */

    for (int j = 31; j >= 0; j--) {
        if (num & (1 << j))
            buffer[j] = 1;
        else
            buffer[j] = 0;
    }
    /* ����1964 �Ķ������ǣ�00000000 00000000 00000111 10101100 */
    cout << num << " �Ķ������ǣ�";
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
    cout << "����һЩ������ " << endl;
    while (1) {
        //cout << "������int32 (4 �ֽ��з�������)" << endl;
        cin >> num;
        if (cin.good() == 1)
            itobs(num, buffer);
        else
            break;
    }
    cout << "------�������------" << endl;
	return 0;
}