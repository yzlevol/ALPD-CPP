#include <iostream>

using namespace std;

class Date
{
public:
    Date(int, int, int);
    Date(int, int);
    Date(int);
    Date();
    void display();

private:
    int month;
    int day;
    int year;
};

Date::Date(int m, int d, int y) : month(m), day(d), year(y) {}

Date::Date(int m, int d) : month(m), day(d)
{
    year = 2005;
}

Date::Date(int m) : month(m)
{
    day = 1;
    year = 2005;
}

Date::Date()
{
    month = 1;
    day = 1;
    year = 2005;
}

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
/*
- *Result - *
output:
10/13/2005 
12/30/2005 
10/1/2005 
1/1/2005
- *end * -
Analysis
这是一个构造函数重载的示例程序
在类Date中定义了多个构造函数，以便对类对象提供不同的初始化的方法，供用户选用。这些构造函数具有和类相同的名字，而参数的个数或参数的类型不相同。
Date类中构造函数和display函数公有，数据成员month，day，year私有，不可在外部调用更改。
d1传入三个参数调用了构造函数Date::Date(int m, int d, int y) : month(m), day(d), year(y)
d2传入两个参数调用了构造函数Date::Date(int m, int d) : month(m), day(d)
d3传入一个参数调用了构造函数Date::Date(int m) : month(m)
d4传入0个参数调用了构造函数Date::Date()
构造函数对数据成员进行初始化，然后在调用display函数进行输出，最后调用默认的析构函数，依次释放d4,d3,d2,d1
*/