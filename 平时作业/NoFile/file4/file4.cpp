#include<iostream>
#include<fstream>
using namespace std;
int main()
{
	int line=0;
	char str[1024];
	long long pianyi[1024] = { 0 };
	cout << "-*�������ļ�����*-" << endl;
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
		//׷��
		ofstream foo("foo.bar", ios::out | ios::app);
		if (foo.is_open()) {
			foo << endl << line << " ";
			for (int i = 0; i <= line; i++) {
				foo << pianyi[i] << " ";
			}
		}
		else {
			cout << "�ļ���ʧ��!" << endl;
			return -1;
		}
		foo.close();
		cout << "-*�޸ĺ��ļ�*-" << endl;
		ifstream fprint("foo.bar", ios::in);
		while (!fprint.eof()) {
			fprint.getline(str, 1024, '\n');
			cout << str;
		}
		cout << endl<< "-*end*-" << endl;
		fprint.close();
	}
	else {
		cout << "�ļ���ʧ��!" << endl;
		return -1;
	}
	return 0;
}