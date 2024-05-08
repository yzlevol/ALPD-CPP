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

class Student1 : protected Student
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
    cout << "请输入学号，姓名，性别，年龄，地址: " << endl;
    cin >> num >> name >> sex;
    cin >> age >> addr;
}

void Student1::display1()
{
    cout << "学号: " << num << endl;
    cout << "姓名: " << name << endl;
    cout << "性别: " << sex << endl;
    cout << "年龄: " << age << endl;
    cout << "地址: " << addr << endl;
}

int main()
{
    Student1 stud1;
    stud1.get_value1();
    stud1.display1();
    return 0;
}