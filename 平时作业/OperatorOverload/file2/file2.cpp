#include<iostream>
using namespace std;

class Matrix //¾ØÕóÀà
{
private:
	int row, col; //ÐÐºÍÁÐ
	int matx[2][3];
public:
	Matrix();
	Matrix(int r, int c);
	~Matrix() {};
	Matrix operator+(const Matrix& x2);   //¾ØÕó+ÔËËã£¬Ë«Ä¿
	friend istream& operator>>(istream& in, Matrix& x);
	friend ostream& operator<<(ostream& out, Matrix& x);
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
Matrix Matrix::operator+(const Matrix& x2)
{
	Matrix tmp(row, col);
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			tmp.matx[i][j] = matx[i][j] + x2.matx[i][j];
		}
	}
	return tmp;
}
istream& operator>>(istream& in, Matrix& x)
{
	for (int i = 0; i < x.row; i++) {
		for (int j = 0; j < x.col; j++) {
			in >> x.matx[i][j];
		}
	}
	return in;
}
ostream& operator<<(ostream& out, Matrix& x)
{
	for (int i = 0; i < x.row; i++) {
		for (int j = 0; j < x.col; j++) {
			out << x.matx[i][j] <<" ";
		}
		out << endl;
	}
	return out;
}

int main()
{
	//Matrix a, b, c;
	Matrix a(2, 3);
	Matrix b(2, 3);
	Matrix c(2, 3);
	cout << "ÇëÊäÈë¾ØÕóa:" << endl;
	cin >> a;
	cout << "¾ØÕóaÎª:" << endl;
	cout << a;
	cout << "ÇëÊäÈë¾ØÕób:" << endl;
	cin >> b;
	cout << "¾ØÕóbÎª:" << endl;
	cout << b;
	cout << "¾ØÕóc = a + bÎª:" << endl;
	c = a + b;
	cout << c;
	return 0;
}