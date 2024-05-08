#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Teacher
{
protected:
	char name[20];
	int age;
	char sex;
	char addr[50];
	char phone[20];
	char title[20]; //职称
public:
	Teacher(const char* n, int a, char s, const char* addr, const char* ph, const char* t);
	void display();
};
Teacher::Teacher(const char* n, int a, char s, const char* ads, const char* ph, const char* t)
{
	strcpy(name, n);
	age = a;
	sex = s;
	strcpy(addr, ads);
	strcpy(phone, ph);
	strcpy(title, t);
}
void Teacher::display()
{
	cout << "姓名: " << name << endl;
	cout << "年龄: " << age << endl;
	cout << "性别: " << sex << endl;
	cout << "职称: " << title << endl;
	cout << "地址: " << addr << endl;
	cout << "电话: " << phone << endl;
}

class Cadre
{
protected:
	char name[20];
	int age;
	char sex;
	char addr[50];
	char phone[20];
	char post[20]; //职务
public:
	Cadre(const char* n, int a, char s, const char* addr, const char* ph, const char* p);
	void display();
};
Cadre::Cadre(const char* n, int a, char s, const char* ads, const char* ph, const char* p)
{
	strcpy(name, n);
	age = a;
	sex = s;
	strcpy(addr, ads);
	strcpy(phone, ph);
	strcpy(post, p);
}
void Cadre::display()
{
	cout << "姓名: " << name << endl;
	cout << "年龄: " << age << endl;
	cout << "性别: " << sex << endl;
	cout << "职务: " << post << endl;
	cout << "地址: " << addr << endl;
	cout << "电话: " << phone << endl;
}

class Teacher_Cadre :public Teacher, public Cadre
{
protected:
	double wages;//工资
public:
	Teacher_Cadre(const char* n, int a, char s, const char* ads, const char* ph, const char* t, const char* p, double w);
	void show();
};
Teacher_Cadre::Teacher_Cadre(const char* n, int a, char s, const char* ads, const char* ph, const char* t, const char* p, double w) :Teacher(n, a, s, ads, ph, t), Cadre(n, a, s, ads, ph, p)
{
	wages = w;
}
void Teacher_Cadre::show()
{
	cout << "教师兼干部的信息如下：" << endl;
	Teacher::display();
	cout << "职务: " << Cadre::post << endl;
	cout << "工资: " << wages << endl;
}
int main()
{
	char n[20], ads[50], ph[20];
	int a;
	char s;
	int option = 0;
	cout << "请选择输入的数据类型（0-教师，1-干部，2-教师兼干部）：" << endl;
	cin >> option;
	if (option == 0)
	{
		char t[20];
		cout << "请输入教师的姓名、年龄、性别、地址、电话和职称: " << endl;
		cin >> n >> a >> s >> ads >> ph >> t;
		Teacher teacher(n, a, s, ads, ph, t);
		cout << "教师的信息如下：" << endl;
		teacher.display();
	}
	else if (option == 1)
	{
		char p[20];
		cout << "请输入干部的姓名、年龄、性别、地址、电话和职务: " << endl;
		cin >> n >> a >> s >> ads >> ph >> p;
		Cadre cadre(n, a, s, ads, ph, p);
		cout << "干部的信息如下：" << endl;
		cadre.display();
	}
	else if (option == 2)
	{
		char t[20];
		char p[20];
		double w;
		cout << "请输入教师兼干部的姓名、年龄、性别、地址、电话、职称、职务和工资: " << endl;
		cin >> n >> a >> s >> ads >> ph >> t >> p >> w;
		Teacher_Cadre teacher_cadre(n, a, s, ads, ph, t, p, w);
		teacher_cadre.show();
	}
	else
	{
		cout << "输入有误，程序退出!" << endl;
	}
	return 0;
}