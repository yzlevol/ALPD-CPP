#include <iostream>
using namespace std;

class Student
{
public:


protected:
    int num;
    char name[20];
    char sex;
};

class Student1 : public Student
{
public:
    void get_value1();
    void display1();
private:
    int age;
    char addr[20];
};

void Student1::get_value1()
{
    cout << "������ѧ�ţ��������Ա����䣬��ַ: " << endl;
    cin >> num >> name >> sex;
    cin >> age >> addr;
}

void Student1::display1()
{
    cout << "ѧ��: " << num << endl;
    cout << "����: " << name << endl;
    cout << "�Ա�: " << sex << endl;
    cout << "����: " << age << endl;
    cout << "��ַ: " << addr << endl;
}

int main()
{
    Student1 stud1;
    stud1.get_value1();
    stud1.display1();
    return 0;
}

//���������
// ������������������̳в���������������ʻ���Ĺ��к��ܱ�����Ա��
// ������������������̳в������ڷ��ʻ���Ĺ��к��ܱ�����Ա�����޷�����������������ʻ����public��Ա��