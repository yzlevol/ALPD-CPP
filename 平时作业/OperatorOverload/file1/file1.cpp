#include<iostream>
using namespace std;

class Matrix //矩阵类
{
private:
	int row, col; //行和列
	int matx[2][3];
public:
	Matrix();
	Matrix(int r, int c);
	~Matrix() {};
	friend Matrix operator+(const Matrix& x1, const Matrix& x2);   //矩阵+运算，双目
	void readFromKeyboard();           //设置矩阵
	void display();                    //输出
};
Matrix::Matrix()
{
	row = 0;
	col = 0;
}
Matrix::Matrix(int r, int c) :row(r), col(c) 
{
	for (int i = 0; i < row; ++i)
		for (int j = 0; j < col; ++j)
			matx[i][j] = 0;
}
Matrix operator+(const Matrix& x1,const Matrix& x2)
{
	Matrix tmp(x1.row, x1.col);
	for (int i = 0; i < x1.row; ++i) {
		for (int j = 0; j < x1.col; ++j) {
			tmp.matx[i][j] = x1.matx[i][j] + x2.matx[i][j];
		}
	}
	return tmp;
}
void Matrix::readFromKeyboard()
{
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			cin >> matx[i][j];
		}
	}
}
void Matrix::display()
{
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			cout << matx[i][j] << " ";
		}
		cout << endl;
	}
}

int main()
{
	//Matrix a, b, c;
	Matrix a(2, 3);
	Matrix b(2, 3);
	Matrix c(2, 3);
	cout << "请输入矩阵a:" << endl;
	a.readFromKeyboard();
	cout << "矩阵a为:" << endl;
	a.display();
	cout << "请输入矩阵b:" << endl;
	b.readFromKeyboard();
	cout << "矩阵b为:" << endl;
	b.display();
	cout << "矩阵c = a + b为:" << endl;
	c = a + b;
	c.display();
	return 0;
}