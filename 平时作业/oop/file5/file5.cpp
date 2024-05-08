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

void fun(Student& stu)
{
    stu.display();
    stu.change(101, 80.5);
    stu.display();
}

int main()
{
    Student stud(101, 78.5);
    fun(stud);
    //stud.display();
    //stud.change(101, 80.5);
    //stud.display();
    return 0;
}
//增加一个函数 fun(Student&)，然后改写 main 函数，将 change 和 display 的操作移入 fun 函数中，并在 main 内调用 fun 函数。

