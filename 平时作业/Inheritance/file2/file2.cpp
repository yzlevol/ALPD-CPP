#include<iostream>
using namespace std;

class Student
{
public:
    void get_value()
    {
        cin >> num >> name >> sex;
    }

    void display()
    {
        cout << "����: " << name << endl;
        cout << "ѧ��: " << num << endl;
        cout << "�Ա�: " << sex << endl;
    }

private:
    int num;
    char name[20];
    char sex;
};
class Student1 : private Student
{
public:
    void get_value_1()
    {
        cout << "������ѧ�ţ��������Ա����䣬��ַ: " << endl;
        get_value();
        cin >> age >> addr;
    }

    void display_1()
    {
        display();
        cout << "����: " << age << endl;
        cout << "��ַ: " << addr << endl;
    }
private:
    int age;
    char addr[20];
};
int main()
{
    Student1 stud;
    stud.get_value_1();
    stud.display_1();
	return 0;
}