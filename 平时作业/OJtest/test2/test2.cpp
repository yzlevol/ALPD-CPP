#define _CRT_SECURE_NO_WARNINGS // 针对MSVC绕过C函数安全检查
#include<iostream>
using namespace std;
int main()
{
	//int A = 0, B = 0;
	//cin >> A;
	//if (cin.fail() == 1) {
	//	cout << "Error!" << endl;

	//}
	//else {
	//	cin >> B;
	//	if (cin.fail() == 0)
	//		cout << "A+B=" << A + B << endl;
	//	else
	//		cout << "Error!" << endl;
	//}


	int A, B;
	int c=scanf("%d %d", &A, &B);
	if (c == 2) {
		printf("A+B=%d", A + B);

	}
	else
		printf("Error!");
	return 0;
}