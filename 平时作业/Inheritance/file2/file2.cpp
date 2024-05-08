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
        cout << "姓名: " << name << endl;
        cout << "学号: " << num << endl;
        cout << "性别: " << sex << endl;
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
        cout << "请输入学号，姓名，性别，年龄，地址: " << endl;
        get_value();
        cin >> age >> addr;
    }

    void display_1()
    {
        display();
        cout << "年龄: " << age << endl;
        cout << "地址: " << addr << endl;
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