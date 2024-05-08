#include<iostream>
#include<istream>
using namespace std;

istream& f(istream& in)
{
    /* 复读整数，并拒绝错误输入 */
    int num = 0;
    while (!in.eof()) {
        in >> num;
        if (in.fail() == 1) {
            cout << " 输入非法！请重新输入";
            in.clear();
            in.ignore(1024,' ');
        }
        else if (num == EOF)
            break;
        else {
            cout << "你说了:" << num << " ";
        }
    }

    auto in_state = in.rdstate(); // 保存流入函数的状态
    // do something
    in.setstate(in_state);        // 复位流
    return in;
}

int main()
{
    int num;
	cout << "请输入一些整数，以-1或Ctrl+Z结束。" << endl;
	f(cin);
    cout << "------程序结束------" << endl;
	return 0;
}