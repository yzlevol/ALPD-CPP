#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

class Teacher
{
public:
	Teacher(const char* n, int no, char s);
	void display();
protected:
	int id;
	char name[20];
	char sex;
};
Teacher::Teacher(const char* n, int no, char s)
{
	strcpy(name, n);
	id = no;
	sex = s;
}
void Teacher::display()
{
	cout << "����: " << name << endl;
	cout << "�̹���: " << id << endl;
	cout << "�Ա�: " << sex << endl;
}
class BirthDate
{
public:
	BirthDate(int y, int m, int d);
	void display();
	void set_birthday(int y, int m, int d);
private:
	int year;
	int month;
	int day;
};
BirthDate::BirthDate(int y, int m, int d)
{
	year = y;
	month = m;
	day = d;
}
void BirthDate::set_birthday(int y, int m, int d)
{
	year = y;
	month = m;
	day = d;
}
void BirthDate::display()
{
	cout << "����: " << year << "-" << month << "-" << day << endl;
}
class Professor :public Teacher, public BirthDate
{
public:
	Professor(const char* n, int id, char s, int y, int m, int d);
	void display();
	void setName(const char* n);
	void setId(int no);
	void setSex(char s);
private:

};
Professor::Professor(const char* n, int no, char s, int y, int m, int d)
	: Teacher(n, no, s), BirthDate(y, m, d) {};
void Professor::display()
{
	Teacher::display();
	BirthDate::display();
}
void Professor::setName(const char* n)
{
	strcpy(name, n);
}
void Professor::setId(int no)
{
	id = no;
}
void Professor::setSex(char s)
{
	sex = s;
}
void func1(Professor& t)
{
	t.setName("����");
	t.setId(10000);
	t.setSex('m');
}
void func2(Professor& t)
{
	int y, m, d;
	cout << "����ı������:" << endl;
	cin >> y >> m >> d;
	t.set_birthday(y,m,d);
}
int main()
{
	const char* name = "����";
	int id = 12345;
	char sex = 'M';
	Professor prof1(name,id,sex,1999,9,9);
	func1(prof1);
	cout << "���ڵĳ�ʼ��Ϣ���£�" << endl;
	prof1.display();
	func2(prof1);
	cout << "�޸ĺ�Ľ�����Ϣ���£�" << endl;
	prof1.display();
	return 0;
}