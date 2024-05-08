#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <ctime>
#include <conio.h>

using namespace std;

inline void wait_for_press()
{
    cout << endl << "�����������..." << endl;
    _getch();
}

/**********************************************
*
*    TO-DO:
*        �벹ȫ������Ĵ��룬��ֻ�ύ���������Ĵ��롣
*
***********************************************/

class Date {
public:
    Date() 
    {
        time_t nowtime;
        struct tm* nowdate;
        time(&nowtime);
        nowdate = localtime(&nowtime);
        year = nowdate->tm_year + 1900;
        month = nowdate->tm_mon + 1;
        day = nowdate->tm_mday;
    };
    Date(int y, int m, int d) :year(y), month(m), day(d) {};
    Date(int days);
    void set(int y, int m = 1, int d = 1);
    friend ostream& operator<<(ostream& os, const Date& date);
    friend istream& operator>>(istream& is, Date& date);
    Date operator=(int days);
    Date& operator+=(int days);
    Date& operator-=(int days);

    Date operator++(int);
    Date& operator++();
    Date operator--(int);
    Date& operator--();
    Date operator+(int days);
    int operator+(Date& b);
    int operator-(Date& b);
    Date operator-(int days);
    operator int() const;
    bool operator>(const Date& b) const;
    bool operator>=(const Date& b) const;
    bool operator==(const Date& b) const;
    bool operator<(const Date& b) const;
    bool operator<=(const Date& b) const;
    bool operator!=(const Date& b) const;

    //void set(int);
private:
    int year, month, day;
    int leap(int year) const 
    {
        return ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0);
    }
    int day_of_year(int year,int month,int day) const
    {
        int sum = day;
        int DAYS_IN_MONTH[] = { 31,28+leap(year),31,30,31,30,31,31,30,31,30,31};
        for (int i = 0; i < month - 1; ++i) {
            sum += DAYS_IN_MONTH[i];
        }
        return sum;
    }

    int daysInMonth(int year, int month) const 
    {
        int days[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
        return days[month] + (month == 2 && leap(year));
    }
    int daysInYear(int year) const
    {
        return 365 + leap(year);
    }
};
Date::Date(int days)
{
    year = 1900;
    month = 1;
    day = 0;
    *this += days;
}
void Date::set(int y, int m, int d)
{
    if (y != 0)
        year = y;
    if (m != 0)
        month = m;
    if (d != 0)
        day = d;
}
istream& operator>>(istream& in, Date& date)
{
    in >> date.year >> date.month >> date.day;
    return in;
}
ostream& operator<<(ostream& os, const Date& date)
{
    os << date.year << "��" << date.month << "��" << date.day << "��"<<endl;
    return os;
}
Date Date::operator=(int days)
{
    year = 1900;
    month = 1;
    day = 0;
    *this += days;
    return *this;
}
Date::operator int() const
{
    int ret = day_of_year(year,month,day);
    for (int i = 1900; i < year; i++) {
        ret += (i % 4 == 0 && (i % 100 != 0 || i % 400 == 0)) ? 366 : 365;
    }
    if (ret == 0)
        ret = 1;
    return ret;
}
Date& Date::operator+=(int days)
{
    int yearDays = daysInYear(year);
    int totalDays = day_of_year(year, month, day) + days;

    while (totalDays < 1) {
        yearDays = daysInYear(--year);
        totalDays += yearDays;
    }

    while (totalDays > yearDays) {
        totalDays -= yearDays;
        yearDays = daysInYear(++year);
    }

    int m = 1;
    while (totalDays > daysInMonth(year, m)) {
        totalDays -= daysInMonth(year, m++);
    }

    day = totalDays;
    month = m;
    return *this;
}

Date& Date::operator-=(int days)
{
    return (*this += -days);
}
Date& Date::operator++()
{
    return (*this += 1);
}
Date Date::operator++(int)
{
    Date tmp(*this);
    ++(*this);
    return tmp;
}
Date& Date::operator--()
{
    return (*this -= 1);
}
Date Date::operator--(int)
{
    Date tmp(*this);
    --(*this);
    return tmp;
}
Date Date::operator+(int days)
{
    Date afr = (*this);
    afr += days;
    return afr;
}
int Date::operator+(Date & b)
{
    return (int)(int(*this) + int(b));
}
int Date::operator-(Date& b)
{
    return (int)(int(*this) - int(b));
}
Date Date::operator-(int days)
{
    Date afr (*this);
    afr -= days;
    return afr;
}


bool Date::operator>(const Date& b) const
{
    return int(*this) > int(b);
}
bool Date::operator>=(const Date& b) const
{
    return int(*this) >= int(b);
}
bool Date::operator==(const Date& b) const
{
    return int(*this) == int(b);
}
bool Date::operator<(const Date& b) const
{
    return int(*this) < int(b);
}
bool Date::operator<=(const Date& b) const
{
    return int(*this) <= int(b);
}
bool Date::operator!=(const Date& b) const
{
    return int(*this) != int(b);
}
/**********************************************
*
*    TO-DO END
*
***********************************************/

int main()
{
    {
        Date d1;
        Date d2(1907, 5, 20);

        cout << "���Գ�ʼ����cout����" << endl;

        cout << "d1Ӧ���ǽ��죬 ʵ��Ϊ��" << d1 << endl;
        cout << "d2Ӧ����1907��5��20�գ�ʵ��Ϊ��" << d2 << endl;

        wait_for_press();
    }

    {
        Date d1, d2, d3, d4;

        cout << "����set��cin����" << endl;
        d1.set(1907, 5, 20);
        d2.set(1907, 5);
        d3.set(1907);

        cout << "d1Ӧ����1907��5��20�գ�ʵ��Ϊ��" << d1 << endl;
        cout << "d2Ӧ����1907��5��1�գ� ʵ��Ϊ��" << d2 << endl;
        cout << "d3Ӧ����1907��1��1�գ� ʵ��Ϊ��" << d3 << endl;

        cout << "������ĳ����" << endl;
        cin >> d4;
        d4.set(0, 0, 0);
        cout << "d4Ӧ����������������ڣ�ʵ��Ϊ��" << d4 << endl;

        wait_for_press();
    }

    {
        Date d1(10);
        Date d2(250);
        Date d3(1314);
        Date d4(13145);

        cout << "����ת�����캯��" << endl;

        cout << "d1Ӧ����1900��1��10�գ�  ʵ��Ϊ��" << d1 << endl;
        cout << "d2Ӧ����1900��9��7�գ�ʵ��Ϊ��" << d2 << endl;
        cout << "d3Ӧ����1903��8��7�գ�  ʵ��Ϊ��" << d3 << endl;
        cout << "d4Ӧ����1935��12��28�գ�ʵ��Ϊ��" << d4 << endl;

        Date d5, d6;
        d5 = 30041;
        cout << "d5Ӧ����1982��4��1�գ� ʵ��Ϊ��" << d5 << endl;

        d6 = 42301;
        cout << "d6Ӧ����2015��10��25�գ� ʵ��Ϊ��" << d6 << endl;

        wait_for_press();
    }

    {
        Date d1(1900, 1, 1);
        Date d2(1907, 5, 20);
        Date d3(1982, 4, 1);
        Date d4(2015, 10, 25);

        cout << "��������ת������" << endl;

        cout << "d1Ӧ����1��     ʵ��Ϊ��" << int(d1) << endl;
        cout << "d2Ӧ����2696�� ʵ��Ϊ��" << int(d2) << endl;
        cout << "d3Ӧ����30041�� ʵ��Ϊ��" << int(d3) << endl;
        cout << "d4Ӧ����42301�� ʵ��Ϊ��" << int(d4) << endl;

        wait_for_press();
    }

    {
        Date d1(1907, 5, 20);
        Date d2;

        cout << "��������+/-" << endl;

        d2 = d1 + 520;
        cout << "d2Ӧ����1908��10��21�գ�    ʵ��Ϊ��" << d2 << endl;

        d2 = 520 + d1;
        cout << "d2Ӧ����1908��10��21�գ�    ʵ��Ϊ��" << d2 << endl;

        d2 = d1 - 3;
        cout << "d2Ӧ����1907��5��17�գ�   ʵ��Ϊ��" << d2 << endl;

        d1.set(2016, 5, 20);
        d2.set(2015, 5, 20);
        cout << "d1-d2Ӧ����366��ʵ��Ϊ��" << d1 - d2 << endl;

        d1.set(2018, 5, 20);
        d2.set(2017, 5, 20);
        cout << "d1-d2Ӧ����365��ʵ��Ϊ��" << d1 - d2 << endl;

        wait_for_press();
    }

    {
        Date d1, d2;

        cout << "��������++/--" << endl;

        d1.set(1907, 5, 20);
        d2 = d1++;
        cout << "d1Ӧ����1907��5��21�գ�  ʵ��Ϊ��" << d1 << endl;
        cout << "d2Ӧ����1907��5��20�գ�  ʵ��Ϊ��" << d2 << endl;

        d1.set(1907, 5, 20);
        d2 = ++d1;
        cout << "d1Ӧ����1907��5��21�գ�  ʵ��Ϊ��" << d1 << endl;
        cout << "d2Ӧ����1907��5��21�գ�  ʵ��Ϊ��" << d2 << endl;

        d1.set(1907, 1, 1);
        d2 = d1--;
        cout << "d1Ӧ����1906��12��31�գ� ʵ��Ϊ��" << d1 << endl;
        cout << "d2Ӧ����1907��1��1�գ�  ʵ��Ϊ��" << d2 << endl;

        d1.set(1907, 1, 1);
        d2 = --d1;
        cout << "d1Ӧ����1906��12��31�գ� ʵ��Ϊ��" << d1 << endl;
        cout << "d2Ӧ����1906��12��31�գ� ʵ��Ϊ��" << d2 << endl;

        d1.set(2016, 2, 28);
        d2 = d1++;
        cout << "d1Ӧ����2016��2��29�գ� ʵ��Ϊ��" << d1 << endl;
        cout << "d2Ӧ����2016��2��28�գ� ʵ��Ϊ��" << d2 << endl;

        d1.set(2018, 3, 1);
        d2 = d1--;
        cout << "d1Ӧ����2018��2��28�գ� ʵ��Ϊ��" << d1 << endl;
        cout << "d2Ӧ����2018��3��1�գ�  ʵ��Ϊ��" << d2 << endl;

        wait_for_press();
    }


    {
        Date d1(1907, 5, 20);
        Date d2(1907, 5, 20);
        Date d3(1907, 1, 1);

        cout << "���ԱȽ������" << endl;

        cout << "�ȽϽ��ӦΪ1��ʵ��Ϊ��" << (d1 > d3) << endl;
        cout << "�ȽϽ��ӦΪ1��ʵ��Ϊ��" << (d2 >= d3) << endl;
        cout << "�ȽϽ��ӦΪ0��ʵ��Ϊ��" << (d1 < d3) << endl;
        cout << "�ȽϽ��ӦΪ0��ʵ��Ϊ��" << (d2 <= d3) << endl;
        cout << "�ȽϽ��ӦΪ1��ʵ��Ϊ��" << (d1 == d2) << endl;
        cout << "�ȽϽ��ӦΪ0��ʵ��Ϊ��" << (d1 != d1) << endl;

        wait_for_press();
    }

    return 0;
}