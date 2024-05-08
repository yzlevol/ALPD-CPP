#include<iostream>
using namespace std;

class dateToDay
{
public:
    dateToDay(int y, int m, int d) : year(y), month(m), day(d)    // 通过传参构建
    {
        if (!checkValid()) {
            cout << "输入有误！程序退出" << endl;
            exit(-1);
        }
    }
    void display();              // 将计算结果输出(即本年内第几天)
private:
    bool checkLeap();            // 该函数用于检查闰年
    bool checkValid();           // 该函数用于检查合法
    int computeDay();            // 该函数用于计算日期
    int year;
    int month;
    int day;
    int days[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
};

void dateToDay::display()  // 将计算结果输出(即本年内第几天)
{
    cout << year << "-" << month << "-" << day;
    cout << "是" << year << "年的第" << computeDay() << "天" << endl;
}

bool dateToDay::checkLeap() // 该函数用于检查闰年
{
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
        return true;
    else
        return false;
}

bool dateToDay::checkValid() // 该函数用于检查合法
{
    if (!(year >= 1 && year <= 9999))
        return false;
    if (!(month >= 1 && month <= 12))
        return false;

    days[2 - 1] += checkLeap();
    if (days[month - 1] >= day && day >= 1)
        return true;
    else
        return false;
}

int dateToDay::computeDay() // 该函数用于计算日期
{
    int sum = 0;
    for (int i = 0; i < month-1; ++i) {
        sum += days[i];
    }
    sum += day;
    return sum;
}

int main()
{
    int y, m, d;
    cout << "请输入一个日期:" << endl;
    cin >> y >> m >> d;
    if (cin.good() == 1) {
        dateToDay d1(y, m, d);
        d1.display();
    }
    else {
        cout << "输入有误！程序退出";
        exit(-1);
    }
    cout << "请输入一个日期:" << endl;
    cin >> y >> m >> d;
    if (cin.good() == 1) {
        dateToDay d2(y, m, d);
        d2.display();
    }
    else {
        cout << "输入有误！程序退出";
        exit(-1);
    }
    return 0;
}