#include<iostream>
#include<fstream>
using namespace std;
int main()
{
	int line=0;
	char str[1024];
	long long pianyi[1024] = { 0 };
	cout << "-*以下是文件内容*-" << endl;
	ifstream foi("foo.bar", ios::in | ios::binary);
	if (foi.is_open()) {
		while (!foi.eof()) {
			foi.getline(str, 1024,'\n');
			cout << str;
			pianyi[++line] = foi.tellg();
		}
		pianyi[line] = pianyi[line - 1] + strlen(str) +1;

		cout << "-*end*-" << endl;
		foi.close();
		//追加
		ofstream foo("foo.bar", ios::out | ios::app);
		if (foo.is_open()) {
			foo << endl << line << " ";
			for (int i = 0; i <= line; i++) {
				foo << pianyi[i] << " ";
			}
		}
		else {
			cout << "文件打开失败!" << endl;
			return -1;
		}
		foo.close();
		cout << "-*修改后文件*-" << endl;
		ifstream fprint("foo.bar", ios::in);
		while (!fprint.eof()) {
			fprint.getline(str, 1024, '\n');
			cout << str;
		}
		cout << endl<< "-*end*-" << endl;
		fprint.close();
	}
	else {
		cout << "文件打开失败!" << endl;
		return -1;
	}
	return 0;
}