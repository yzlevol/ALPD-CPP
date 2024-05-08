#include <iostream>

using namespace std;

class Date
{
public:
	Date(int = 1, int = 1, int = 2005);
	/*
	* ��Ϊ��������ȫ��Ĭ��ֵ����ôһ����0��1��2, 3�����������Ե��ô˺���
	* ���캯��ʹ��Ĭ�ϲ����󣬾Ͳ�����ʹ�ö�����صĹ��캯��������ᵼ�²�֪�������ĸ����캯���������
	* ɾ�������������캯������
	*/
	void display();
private:
	int month;
	int day;
	int year;
};
Date::Date(int m, int d, int y) : month(m), day(d), year(y) {}

void Date::display()
{
	cout << month << "/" << day << "/" << year << endl;
}
int main()
{
	Date d1(10, 13, 2005);
	Date d2(12, 30);
	Date d3(10);
	Date d4;
	d1.display();
	d2.display();
	d3.display();
	d4.display();
	return 0;
}