#include<iostream>
using namespace std;

class Matrix //������
{
private:
	int row, col; //�к���
	int matx[2][3];
public:
	Matrix();
	Matrix(int r, int c);
	~Matrix() {};
	Matrix operator+(const Matrix& x2);   //����+���㣬˫Ŀ
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
	cout << "���������a:" << endl;
	cin >> a;
	cout << "����aΪ:" << endl;
	cout << a;
	cout << "���������b:" << endl;
	cin >> b;
	cout << "����bΪ:" << endl;
	cout << b;
	cout << "����c = a + bΪ:" << endl;
	c = a + b;
	cout << c;
	return 0;
}