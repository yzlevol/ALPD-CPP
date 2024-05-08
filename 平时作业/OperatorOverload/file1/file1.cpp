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
	friend Matrix operator+(const Matrix& x1, const Matrix& x2);   //����+���㣬˫Ŀ
	void readFromKeyboard();           //���þ���
	void display();                    //���
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
	cout << "���������a:" << endl;
	a.readFromKeyboard();
	cout << "����aΪ:" << endl;
	a.display();
	cout << "���������b:" << endl;
	b.readFromKeyboard();
	cout << "����bΪ:" << endl;
	b.display();
	cout << "����c = a + bΪ:" << endl;
	c = a + b;
	c.display();
	return 0;
}