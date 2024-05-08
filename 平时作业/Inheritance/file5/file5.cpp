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
	char title[20]; //ְ��
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
	cout << "����: " << name << endl;
	cout << "����: " << age << endl;
	cout << "�Ա�: " << sex << endl;
	cout << "ְ��: " << title << endl;
	cout << "��ַ: " << addr << endl;
	cout << "�绰: " << phone << endl;
}

class Cadre
{
protected:
	char name[20];
	int age;
	char sex;
	char addr[50];
	char phone[20];
	char post[20]; //ְ��
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
	cout << "����: " << name << endl;
	cout << "����: " << age << endl;
	cout << "�Ա�: " << sex << endl;
	cout << "ְ��: " << post << endl;
	cout << "��ַ: " << addr << endl;
	cout << "�绰: " << phone << endl;
}

class Teacher_Cadre :public Teacher, public Cadre
{
protected:
	double wages;//����
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
	cout << "��ʦ��ɲ�����Ϣ���£�" << endl;
	Teacher::display();
	cout << "ְ��: " << Cadre::post << endl;
	cout << "����: " << wages << endl;
}
int main()
{
	char n[20], ads[50], ph[20];
	int a;
	char s;
	int option = 0;
	cout << "��ѡ��������������ͣ�0-��ʦ��1-�ɲ���2-��ʦ��ɲ�����" << endl;
	cin >> option;
	if (option == 0)
	{
		char t[20];
		cout << "�������ʦ�����������䡢�Ա𡢵�ַ���绰��ְ��: " << endl;
		cin >> n >> a >> s >> ads >> ph >> t;
		Teacher teacher(n, a, s, ads, ph, t);
		cout << "��ʦ����Ϣ���£�" << endl;
		teacher.display();
	}
	else if (option == 1)
	{
		char p[20];
		cout << "������ɲ������������䡢�Ա𡢵�ַ���绰��ְ��: " << endl;
		cin >> n >> a >> s >> ads >> ph >> p;
		Cadre cadre(n, a, s, ads, ph, p);
		cout << "�ɲ�����Ϣ���£�" << endl;
		cadre.display();
	}
	else if (option == 2)
	{
		char t[20];
		char p[20];
		double w;
		cout << "�������ʦ��ɲ������������䡢�Ա𡢵�ַ���绰��ְ�ơ�ְ��͹���: " << endl;
		cin >> n >> a >> s >> ads >> ph >> t >> p >> w;
		Teacher_Cadre teacher_cadre(n, a, s, ads, ph, t, p, w);
		teacher_cadre.show();
	}
	else
	{
		cout << "�������󣬳����˳�!" << endl;
	}
	return 0;
}