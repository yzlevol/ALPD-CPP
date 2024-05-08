#include<iostream>
#include<iomanip>

using namespace std;

int pick_len(double num[],int nums)
{
	int len = 1;
	int maxlen = 0;
	for (int i = 0; i < nums; i++) {
		int tmp = (int)(fabs)(num[i]);
		len = 1;
		while (tmp / 10 != 0) {
			tmp /= 10;
			len++;
		}
		if (len > maxlen)
			maxlen = len;
	}
	return maxlen;
}
int main()
{
	double num[100] = { 0 };
	int i = 0;
	cout << "请输入一些浮点数，以q结束:";
	while (true) {
		cin >> num[i++];
		if (cin.good() != 1) {
			break;
		}
	}
	int maxlen = 12;//pick_len(num, i);
	for (int j = 0; j < i-1; j++) {
		/*cout << setiosflags(ios::fixed) << setiosflags(ios::right) << setprecision(3) ;
		cout << setw(12) << floor(num[j]*1000.0)/1000.0 << endl;*/
		cout.width(maxlen);
		cout.setf(ios::right | ios::fixed);
		cout.precision(3);
		cout << (int)(num[j]*1000)/1000.0 << endl;
	}
	cout << "------程序结束------" << endl;
	return 0;
}