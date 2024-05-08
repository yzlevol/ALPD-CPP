#include <iostream>

using namespace std;

class Student
{
public:
    Student(int n, float s) :num(n), score(s) {}
    void change(int n, float s) { num = n; score = s; }
    void display() { cout << num << " " << score << endl; }
private:
    int num;
    float score;
};

int main()
{
    Student stud(101, 78.5);
    stud.display();
    stud.change(101, 80.5);
    stud.display();
    return 0;
}
/*
- *Result - *
output:
101 78.5
101 80.5
- *end * -
Analysis
这是一个利用自定义类，进行学生学号成绩读入与修改的示例程序。
在Student类中，学号num和成绩score为私有成员，无法在外部访问。公有成员有同名的自定义构造函数和函数成员change(用于修改学生信息)，和display(用于输出学生信息)
构造函数Student使用含参列表的形式对num和score进行初始化
change函数将参数n赋值给num，s赋值给score达到修改的目的
display输出当前的学生信息
main函数中新建了stud对象，并调用上述构造函数初始化，然后输出
接着调用change函数修改学生信息，然后再输出
*/