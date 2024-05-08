#include <iostream>

using namespace std;

class Date
{
public:
	Date(int = 1, int = 1, int = 2005);
	/*
	* 因为三个参数全有默认值，那么一下有0，1，2, 3个参数都可以调用此函数
	* 构造函数使用默认参数后，就不能再使用多个重载的构造函数，否则会导致不知道调用哪个构造函数造成歧义
	* 删除另外三个构造函数即可
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