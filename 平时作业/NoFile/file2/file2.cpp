#include<iostream>
#include<istream>
using namespace std;

istream& f(istream& in)
{
    /* �������������ܾ��������� */
    int num = 0;
    while (!in.eof()) {
        in >> num;
        if (in.fail() == 1) {
            cout << " ����Ƿ�������������";
            in.clear();
            in.ignore(1024,' ');
        }
        else if (num == EOF)
            break;
        else {
            cout << "��˵��:" << num << " ";
        }
    }

    auto in_state = in.rdstate(); // �������뺯����״̬
    // do something
    in.setstate(in_state);        // ��λ��
    return in;
}

int main()
{
    int num;
	cout << "������һЩ��������-1��Ctrl+Z������" << endl;
	f(cin);
    cout << "------�������------" << endl;
	return 0;
}