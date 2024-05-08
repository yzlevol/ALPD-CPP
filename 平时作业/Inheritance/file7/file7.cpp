#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <ctime>
#include <conio.h>
#include <iomanip>

using namespace std;

inline void wait_for_press()
{
    cout << endl << "�����������..." << endl;
    _getch();
}
/*Date��*/
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
protected:
    int year, month, day;  
    //�ӿ�
    void plus_day(int d) {
        Date::day += d;
    }
    int show_day()
    {
        return day;
    }
    int leap(int year) const
    {
        return ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0);
    }
    int day_of_year(int year, int month, int day) const
    {
        int sum = day;
        int DAYS_IN_MONTH[] = { 31,28 + leap(year),31,30,31,30,31,31,30,31,30,31 };
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
    os << setfill('0') << setw(2) << date.year << "��";
    os << setw(2) << date.month << "��";
    os << setw(2) << date.day << "��" << " ";
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
    int ret = day_of_year(year, month, day);
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
int Date::operator+(Date& b)
{
    return (int)(int(*this) + int(b));
}
int Date::operator-(Date& b)
{
    return (int)(int(*this) - int(b));
}
Date Date::operator-(int days)
{
    Date afr(*this);
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

/*Time��*/
class Time
{
protected:
    int hour, min;
    long long sec;
    void normalize();
public:
    Time();
    Time(const char* s);
    Time(int h, int m, long long s);
    Time(long long seconds);
    void set(int h, int m, long long s);
    int set(long long seconds);
    friend ostream& operator<<(ostream& os, const Time& time);
    friend istream& operator>>(istream& in, Time& time);
    Time operator=(long long seconds);
    Time& operator+=(long long seconds);
    Time& operator-=(long long seconds);
    Time operator++(int);
    Time& operator++();
    Time operator--(int);
    Time& operator--();
    Time operator+(long long seconds) const;
    Time operator-(long long seconds) const;
    friend Time operator+(long long seconds, const Time& time);
    friend Time operator-(long long seconds, const Time& time);
    bool operator>(const Time& b) const;
    bool operator>=(const Time& b) const;
    bool operator==(const Time& b) const;
    bool operator<(const Time& b) const;
    bool operator<=(const Time& b) const;
    bool operator!=(const Time& b) const;
    long long getTotalSeconds() const;
};
Time::Time() :hour(0), min(0), sec(0) {};
Time::Time(const char* s)
{
    if (s == "now") {
        time_t nowtime;
        struct tm* nowdate;
        time(&nowtime);
        nowdate = localtime(&nowtime);
        hour = nowdate->tm_hour;
        min = nowdate->tm_min;
        sec = nowdate->tm_sec;
    }
}
Time::Time(int h, int m, long long s) :hour(h), min(m), sec(s)
{
    normalize();
}
Time::Time(long long seconds)
{
    hour = 0;
    min = 0;
    sec = 0;
    *this += seconds;
}
void Time::set(int h, int m, long long s)
{
    if (h != -1)
        hour = h;
    if (m != -1)
        min = m;
    if (s != -1)
        sec = s;
    normalize();
}
int Time::set(long long seconds)
{
    hour = 0;
    min = 0;
    sec = 0;
    *this += seconds;
    return((int)(seconds / (24 * 3600)));
}
ostream& operator<<(ostream& os, const Time& time)
{
    os << setfill('0') << setw(2) << time.hour << ":";
    os << setw(2) << time.min << ":";
    os << setw(2) << time.sec;
    return os;
}
istream& operator>>(istream& in, Time& time)
{
    in >> time.hour >> time.min >> time.sec;
    time.normalize();
    return in;
}
Time Time::operator=(long long seconds)
{
    hour = 0;
    min = 0;
    sec = 0;
    *this += seconds;
    return *this;
}
Time& Time::operator+=(long long seconds)
{
    long long totalSeconds = hour * 3600 + min * 60 + sec + seconds;
    hour = (int)(totalSeconds / 3600);
    min = (totalSeconds / 60) % 60;
    sec = totalSeconds % 60;
    normalize();
    return *this;
}
Time& Time::operator-=(long long seconds)
{
    return(*this += (-seconds));
}
Time Time::operator++(int)
{
    Time tmp = *this;
    *this += 1;
    return tmp;
}
Time& Time::operator++()
{
    *this += 1;
    return *this;
}
Time Time::operator--(int)
{
    Time tmp = *this;
    *this -= 1;
    return tmp;
}
Time& Time::operator--()
{
    *this -= 1;
    return *this;
}
Time Time::operator+(long long seconds) const
{
    Time tmp = *this;
    tmp += seconds;
    return tmp;
}
Time Time::operator-(long long seconds) const
{
    Time tmp = *this;
    tmp -= seconds;
    return tmp;
}
Time operator+(long long seconds, const Time& time)
{
    return time + seconds;
}
Time operator-(long long seconds, const Time& time)
{
    return time - seconds;
}
bool Time::operator>(const Time& b) const
{
    if (hour > b.hour)
        return true;
    else if (hour == b.hour && min > b.min)
        return true;
    else if (hour == b.hour && min == b.min && sec > b.sec)
        return true;
    else
        return false;
}
bool Time::operator>=(const Time& b) const
{
    return(*this > b) || (*this == b);
}
bool Time::operator<(const Time& b) const
{
    return !(*this > b) && !(*this == b);
}
bool Time::operator<=(const Time& b) const
{
    return !(*this > b);
}
bool Time::operator==(const Time& b) const
{
    return (hour==b.hour&&min==b.min&&sec==b.sec);
}
bool Time::operator!=(const Time& b) const
{
    return !(*this == b);
}
void Time::normalize()
{
    if (sec >= 60) {
        min += (int)(sec / 60);
        sec %= 60;
    }
    if (min >= 60) {
        hour += min / 60;
        min %= 60;
    }
    if (hour >= 24) {
        hour %= 24;
    }
}
long long Time::getTotalSeconds() const {
    long long totalSeconds = hour * 3600 + min * 60 + sec;
    return totalSeconds;
}
/*������*/
class DateTime :public Date, public Time
{
public:
    explicit operator int() const = delete;
    explicit operator long long() const = delete;
    explicit operator Date() const = delete;
    explicit operator Time() const = delete;
    explicit operator DateTime() const = delete;
    DateTime();
    DateTime(int year, int month, int day, int hour, int min, int sec);
    DateTime(int hour, int min, int sec);
    DateTime(long long seconds);
    void set(int year, int month, int day, int hour, int min, int sec);
    void set(int year, int month, int day);
    void set(long long seconds);
    friend ostream& operator<<(ostream& os, const DateTime& dt);
    friend istream& operator>>(istream& is, DateTime& dt);
    //���������
    DateTime operator=(int seconds);
    DateTime& operator+=(long long seconds);
    DateTime& operator-=(long long seconds);
    DateTime operator++(int);
    DateTime& operator++();
    DateTime operator--(int);
    DateTime& operator--();
    bool operator>(const DateTime& dt) const;
    bool operator>=(const DateTime& dt) const;
    bool operator==(const DateTime& dt) const;
    bool operator<(const DateTime& dt) const;
    bool operator<=(const DateTime& dt) const;
    bool operator!=(const DateTime& dt) const;
    friend DateTime operator+(long long seconds, DateTime& dt);
    friend DateTime operator+(long long seconds, DateTime& dt);
    DateTime operator+(long long seconds) const;
    DateTime operator-(long long seconds) const;
    //�ӿ�
    void normalize() {
        long long extraMinutes = sec / 60;
        sec %= 60;
        min += (int)extraMinutes;
        int extraHours = min / 60;
        min %= 60;
        hour += extraHours;
        int extraDays = hour / 24;
        hour %= 24;
        plus_day(extraDays);

        while (day > daysInMonth(year, month)) {
            day -= daysInMonth(year, month);
            month++;
            if (month > 12) {
                month = 1;
                year++;
            }
        }
        while (day <= 0) {
            month--;
            if (month < 1) {
                month = 12;
                year--;
            }
            day += daysInMonth(year, month);
        }

        while (sec < 0) {
            min--;
            sec += 60;
        }
        while (min < 0) {
            hour--;
            min += 60;
        }
        while (hour < 0) {
            day--;
            hour += 24;
        }

        Time::normalize();
    }

};
DateTime::DateTime() :Date(1900, 1, 1), Time(0, 0, 0) {};
DateTime::DateTime(int year, int month, int day, int hour, int min, int sec)
    :Date(year, month, day), Time(hour, min, sec) {};
DateTime::DateTime(int hour, int min, int sec)
    :Date(1900, 1, 1), Time(hour, min, sec) {};
DateTime::DateTime(long long seconds) :Date(1900, 1, 1), Time(seconds) //��1900-1-1��������
{
    int overDays = 0;
    overDays = Time::set(seconds);
    Date::operator+=(overDays);
};
void DateTime::set(int year, int month, int day, int hour, int min, int sec)
{
    Date::set(year, month, day);
    Time::set(hour, min, sec);
}
void DateTime::set(int year, int month, int day)
{
    Date::set(year, month, day);
}
void DateTime::set(long long seconds) //��1900-1-1��������
{
    int overDays = 0;
    overDays = Time::set(seconds);
    int deltaD=overDays-Date::Date(1900, 1, 0);
    if(deltaD>=0)
        Date::operator+=(overDays-Date::operator int());
}
ostream& operator<<(ostream& os, const DateTime& dt) {
    os << static_cast<const Date&>(dt) << static_cast<const Time&>(dt);
    return os;
}
istream& operator>>(istream& is, DateTime& dt) {
    is >> static_cast<Date&>(dt) >> static_cast<Time&>(dt);
    return is;
}
DateTime DateTime::operator=(int seconds) {
    Date::operator=(seconds / (24 * 3600));
    Time::operator=(seconds % (24 * 3600));
    return *this;
}
DateTime& DateTime::operator+=(long long seconds) {
    long long totalSeconds = (long long)(Date::operator int()) * (24 * 3600) + Time::getTotalSeconds() + seconds;
    DateTime::set(totalSeconds);
    DateTime::normalize();
    return *this;
}
DateTime& DateTime::operator-=(long long seconds) {
    *this += -seconds;
    DateTime::normalize();
    return *this;
}
DateTime& DateTime::operator++() {
    *this += 1;
    DateTime::normalize();
    return *this;
}
DateTime DateTime::operator++(int) {
    DateTime tmp = *this;
    ++(*this);
    DateTime::normalize();
    return tmp;
}
DateTime& DateTime::operator--() {
    *this -= 1;
    DateTime::normalize();
    return *this;
}
DateTime DateTime::operator--(int) {
    DateTime temp = *this;
    --(*this);
    DateTime::normalize();
    return temp;
}
DateTime operator+(long long seconds, DateTime& dt)
{
    DateTime result = dt;
    result += seconds;
    result.normalize();
    return result;
}
DateTime operator-(long long seconds, DateTime& dt)
{
    DateTime result = dt;
    result -= seconds;
    result.normalize();
    return result;
}
DateTime DateTime::operator+(long long seconds) const {
    DateTime result = *this;
    result.sec += seconds;
    result.normalize();
    return result;
}
DateTime DateTime::operator-(long long seconds) const {
    DateTime result = *this;
    result.sec -= seconds;
    result.normalize();
    return result;
}
bool DateTime::operator>(const DateTime& dt) const {
    if (static_cast<const Date&>(*this) > static_cast<const Date&>(dt)) {
        return true;
    }
    else if (static_cast<const Date&>(*this) == static_cast<const Date&>(dt)) {
        return static_cast<const Time&>(*this) > static_cast<const Time&>(dt);
    }
    return false;
}
bool DateTime::operator>=(const DateTime& dt) const {
    return (*this > dt) || (*this == dt);
}
bool DateTime::operator==(const DateTime& dt) const {
    return (static_cast<const Date&>(*this) == static_cast<const Date&>(dt)) &&
        (static_cast<const Time&>(*this) == static_cast<const Time&>(dt));
}
bool DateTime::operator<(const DateTime& dt) const {
    return !(*this >= dt);
}
bool DateTime::operator<=(const DateTime& dt) const {
    return !(*this > dt);
}
bool DateTime::operator!=(const DateTime& dt) const {
    return !(*this == dt);
}



int main()
{
    cout << "������ʾDate��Time��DateTime" << endl;
    cout << "-------Date����ʾ��ʼ-------:" << endl;
    
    {
        Date d1;
        Date d2(1907, 5, 20);

        cout << "���Գ�ʼ����cout����" << endl;

        cout << "d1Ӧ���ǽ��죬 ʵ��Ϊ��" << d1 << endl;
        cout << "d2Ӧ����1907��05��20�գ�ʵ��Ϊ��" << d2 << endl;

        wait_for_press();
    }

    {
        Date d1, d2, d3, d4;

        cout << "����set��cin����" << endl;
        d1.set(1907, 5, 20);
        d2.set(1907, 5);
        d3.set(1907);

        cout << "d1Ӧ����1907��05��20�գ� ʵ��Ϊ��" << d1 << endl;
        cout << "d2Ӧ����1907��05��01�գ� ʵ��Ϊ��" << d2 << endl;
        cout << "d3Ӧ����1907��01��01�գ� ʵ��Ϊ��" << d3 << endl;

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

        cout << "d1Ӧ����1900��01��10�գ� ʵ��Ϊ��" << d1 << endl;
        cout << "d2Ӧ����1900��09��07�գ� ʵ��Ϊ��" << d2 << endl;
        cout << "d3Ӧ����1903��08��07�գ� ʵ��Ϊ��" << d3 << endl;
        cout << "d4Ӧ����1935��12��28�գ� ʵ��Ϊ��" << d4 << endl;

        Date d5, d6;
        d5 = 30041;
        cout << "d5Ӧ����1982��04��01�գ� ʵ��Ϊ��" << d5 << endl;

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
        cout << "d2Ӧ����2696��  ʵ��Ϊ��" << int(d2) << endl;
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
        cout << "d2Ӧ����1907��05��17�գ�    ʵ��Ϊ��" << d2 << endl;

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
        cout << "d1Ӧ����1907��05��21�գ�  ʵ��Ϊ��" << d1 << endl;
        cout << "d2Ӧ����1907��05��20�գ�  ʵ��Ϊ��" << d2 << endl;

        d1.set(1907, 5, 20);
        d2 = ++d1;
        cout << "d1Ӧ����1907��05��21�գ�  ʵ��Ϊ��" << d1 << endl;
        cout << "d2Ӧ����1907��05��21�գ�  ʵ��Ϊ��" << d2 << endl;

        d1.set(1907, 1, 1);
        d2 = d1--;
        cout << "d1Ӧ����1906��12��31�գ�  ʵ��Ϊ��" << d1 << endl;
        cout << "d2Ӧ����1907��01��01�գ�  ʵ��Ϊ��" << d2 << endl;

        d1.set(1907, 1, 1);
        d2 = --d1;
        cout << "d1Ӧ����1906��12��31�գ�  ʵ��Ϊ��" << d1 << endl;
        cout << "d2Ӧ����1906��12��31�գ�  ʵ��Ϊ��" << d2 << endl;

        d1.set(2016, 2, 28);
        d2 = d1++;
        cout << "d1Ӧ����2016��02��29�գ�  ʵ��Ϊ��" << d1 << endl;
        cout << "d2Ӧ����2016��02��28�գ�  ʵ��Ϊ��" << d2 << endl;

        d1.set(2018, 3, 1);
        d2 = d1--;
        cout << "d1Ӧ����2018��02��28�գ�  ʵ��Ϊ��" << d1 << endl;
        cout << "d2Ӧ����2018��03��01�գ�  ʵ��Ϊ��" << d2 << endl;

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
    
    cout << "-------Date����ʾ����-------:" << endl << endl;

    cout << "-------Time����ʾ��ʼ-------:" << endl;
    
    {
        Time t1;
        Time t2(13, 23, 33);
        Time t3(3665);
        Time t4("now");
        cout << "���Գ�ʼ����cout����" << endl;
        cout << "t1Ӧ����00:00:00��    ʵ��Ϊ��" << t1 << endl;
        cout << "t2Ӧ����13:23:33��    ʵ��Ϊ��" << t2 << endl;
        cout << "t3Ӧ����01:01:05��    ʵ��Ϊ��" << t3 << endl;
        cout << "t4Ӧ���ǵ�ǰʱ�䣬    ʵ��Ϊ��" << t4 << endl;
        wait_for_press();
    }

    {
        Time t1, t2, t3, t4;
        cout << "����set��cin����" << endl;
        t1.set(20, 14, 13);
        t2.set(-1, 13, 14);
        t3.set(84813);
        cout << "t1Ӧ����20:14:13��    ʵ��Ϊ��" << t1 << endl;
        cout << "t2Ӧ����00:13:14��    ʵ��Ϊ��" << t2 << endl;
        cout << "t3Ӧ����23:33:33��    ʵ��Ϊ��" << t3 << endl;
        cout << "������ĳ��ʱ��" << endl;
        cin >> t4;
        cout << "t3Ӧ�������������ʱ�䣬ʵ��Ϊ��" << t4 << endl;
        wait_for_press();
    }

    {
        Time t1(10);
        Time t2(250);
        Time t3(1314);
        Time t4(13145);
        cout << "����ת�����캯��" << endl;
        cout << "t1Ӧ����00:00:10��    ʵ��Ϊ��" << t1 << endl;
        cout << "t2Ӧ����00:04:10��    ʵ��Ϊ��" << t2 << endl;
        cout << "t3Ӧ����00:21:54��    ʵ��Ϊ��" << t3 << endl;
        cout << "t4Ӧ����03:39:05��    ʵ��Ϊ��" << t4 << endl;
        Time t5, t6;
        t5 = 30041;
        cout << "t5Ӧ����08:20:41��    ʵ��Ϊ��" << t5 << endl;
        t6 = 42301;
        cout << "t6Ӧ����11:45:01��    ʵ��Ϊ��" << t6 << endl;
        wait_for_press();
    }

    {
        Time t1(12, 20, 30);
        Time t2;
        cout << "��������+/-" << endl;
        t2 = t1 + 520;
        cout << "t2Ӧ����12:29:10��    ʵ��Ϊ��" << t2 << endl;
        t2 = 520 + t1;
        cout << "t2Ӧ����12:29:10��    ʵ��Ϊ��" << t2 << endl;
        t2 = t1 - 7205;
        cout << "t2Ӧ����10:20:25��    ʵ��Ϊ��" << t2 << endl;
        wait_for_press();
    }

    {
        Time t1, t2;

        cout << "��������++/--" << endl;

        t1.set(16, 29, 31);
        t2 = t1++;
        cout << "t1Ӧ����16:29:32��    ʵ��Ϊ��" << t1 << endl;
        cout << "t2Ӧ����16:29:31��    ʵ��Ϊ��" << t2 << endl;

        t1.set(17, 59, 59);
        t2 = ++t1;
        cout << "t1Ӧ����18:00:00��    ʵ��Ϊ��" << t1 << endl;
        cout << "t2Ӧ����18:00:00��    ʵ��Ϊ��" << t2 << endl;

        t1.set(16, 29, 31);
        t2 = --t1;
        cout << "t1Ӧ����16:29:30��    ʵ��Ϊ��" << t1 << endl;
        cout << "t2Ӧ����16:29:30��    ʵ��Ϊ��" << t2 << endl;

        t1.set(17, 59, 59);
        t2 = t1--;
        cout << "t1Ӧ����17:59:58��    ʵ��Ϊ��" << t1 << endl;
        cout << "t2Ӧ����17:59:59��    ʵ��Ϊ��" << t2 << endl;

        wait_for_press();
    }

    {
        Time t1(12, 25, 39);
        Time t2(14, 24, 16);
        Time t3(12, 25, 39);

        cout << "���ԱȽ������" << endl;

        cout << "�ȽϽ��ӦΪ0��ʵ��Ϊ��" << (t1 > t2) << endl;
        cout << "�ȽϽ��ӦΪ0��ʵ��Ϊ��" << (t1 >= t2) << endl;
        cout << "�ȽϽ��ӦΪ1��ʵ��Ϊ��" << (t1 < t2) << endl;
        cout << "�ȽϽ��ӦΪ1��ʵ��Ϊ��" << (t1 <= t2) << endl;
        cout << "�ȽϽ��ӦΪ1��ʵ��Ϊ��" << (t1 == t3) << endl;
        cout << "�ȽϽ��ӦΪ1��ʵ��Ϊ��" << (t1 != t2) << endl;

        wait_for_press();
    }
    
    cout << "-------Time����ʾ����-------:" << endl << endl;

    cout << "-------DateTime����ʾ��ʼ-------:" << endl;

    {
        DateTime dt1;
        DateTime dt2(2023, 5, 29, 12, 30, 0);
        DateTime dt3(19, 16, 59);
        DateTime dt4(3600 * 25 + 3665);

        cout << "���Գ�ʼ����cout����" << endl;

        cout << "dt1Ӧ����1900-01-01 00:00:00��    ʵ��Ϊ��" << dt1 << endl;
        cout << "dt2Ӧ����2023-05-29 12:30:00��    ʵ��Ϊ��" << dt2 << endl;
        cout << "dt3Ӧ����1900-01-01 19:16:59��    ʵ��Ϊ��" << dt3 << endl;
        cout << "dt4Ӧ����1900-01-02 02:01:05��    ʵ��Ϊ��" << dt4 << endl;

        wait_for_press();
    }


    {
        DateTime dt1, dt2, dt3, dt4;

        cout << "����set��cin����" << endl;

        dt1.set(2023, 5, 29, 20, 14, 13);
        dt2.set(2023, 5, 29);
        dt3.set(84813);

        cout << "dt1Ӧ����2023-05-29 20:14:13��    ʵ��Ϊ��" << dt1 << endl;
        cout << "dt2Ӧ����2023-05-29 00:00:00��    ʵ��Ϊ��" << dt2 << endl;
        cout << "dt3Ӧ����1900-01-01 23:33:33��    ʵ��Ϊ��" << dt3 << endl;

        cout << "������ĳ������ʱ��" << endl;
        cin >> dt4;
        cout << "dt4Ӧ�����������������ʱ�䣬ʵ��Ϊ��" << dt4 << endl;

        wait_for_press();
    }

    {
        DateTime dt1(2005, 2, 28, 23, 59, 58);
        DateTime dt2;

        cout << "��������+=/-=" << endl;
        cout << "dt1Ӧ����2005-02-28 23:59:58��    ʵ��Ϊ��" << dt1 << endl;
        dt2 = dt1;
        dt2 += 10;
        cout << "dt2Ӧ����2005-03-10 00:00:08��    ʵ��Ϊ��" << dt2 << endl;

        dt2 = dt1;
        dt2 += 3 * 3600 * 24;
        cout << "dt2Ӧ����2005-03-03 23:59:58��    ʵ��Ϊ��" << dt2 << endl;

        dt2 = dt1;
        dt2 -= 2 * 3600 * 24+659;
        cout << "dt2Ӧ����2005-02-26 23:48:59��    ʵ��Ϊ��" << dt2 << endl;

        wait_for_press();
    }


    {
        DateTime dt1(2023, 5, 29, 12, 20, 30);
        DateTime dt2;

        cout << "��������+/-" << endl;

        dt2 = dt1 + 520;
        cout << "dt2Ӧ����2023-05-29 12:29:10��    ʵ��Ϊ��" << dt2 << endl;
        dt2 = 521 + dt1;
        cout << "dt2Ӧ����2023-05-29 12:29:11��    ʵ��Ϊ��" << dt2 << endl;
        dt2 = dt1 + 3*3600*24;
        cout << "dt2Ӧ����2023-06-01 12:20:30��    ʵ��Ϊ��" << dt2 << endl;
        dt2 = dt1 - 2 * 3600 * 24;
        cout << "dt2Ӧ����2023-05-27 12:20:30��    ʵ��Ϊ��" << dt2 << endl;
        wait_for_press();
    }

    {
        DateTime dt1, dt2;

        cout << "��������++/--" << endl;

        dt1.set(2023, 5, 29, 16, 29, 31);
        dt2 = dt1++;
        cout << "dt1Ӧ����2023-05-29 16:29:32��    ʵ��Ϊ��" << dt1 << endl;
        cout << "dt2Ӧ����2023-05-29 16:29:31��    ʵ��Ϊ��" << dt2 << endl;

        dt1.set(2023, 5, 29, 17, 59, 59);
        dt2 = ++dt1;
        cout << "dt1Ӧ����2023-05-29 18:00:00��    ʵ��Ϊ��" << dt1 << endl;
        cout << "dt2Ӧ����2023-05-29 18:00:00��    ʵ��Ϊ��" << dt2 << endl;

        dt1.set(2023, 5, 29, 16, 29, 31);
        dt2 = --dt1;
        cout << "dt1Ӧ����2023-05-29 16:29:30��    ʵ��Ϊ��" << dt1 << endl;
        cout << "dt2Ӧ����2023-05-29 16:29:30��    ʵ��Ϊ��" << dt2 << endl;

        dt1.set(2023, 5, 29, 17, 59, 59);
        dt2 = dt1--;
        cout << "dt1Ӧ����2023-05-29 17:59:58��    ʵ��Ϊ��" << dt1 << endl;
        cout << "dt2Ӧ����2023-05-29 17:59:59��    ʵ��Ϊ��" << dt2 << endl;

        wait_for_press();
    }

    {
        DateTime dt1(2023, 5, 29, 12, 25, 39);
        DateTime dt2(2023, 5, 29, 14, 24, 16);
        DateTime dt3(1999, 5, 30, 5, 24, 9);

        cout << "���ԱȽ������" << endl;

        cout << "�ȽϽ��ӦΪ0��ʵ��Ϊ��" << (dt1 > dt2) << endl;
        cout << "�ȽϽ��ӦΪ0��ʵ��Ϊ��" << (dt1 >= dt2) << endl;
        cout << "�ȽϽ��ӦΪ1��ʵ��Ϊ��" << (dt1 < dt2) << endl;
        cout << "�ȽϽ��ӦΪ1��ʵ��Ϊ��" << (dt1 <= dt2) << endl;
        cout << "�ȽϽ��ӦΪ0��ʵ��Ϊ��" << (dt1 == dt3) << endl;
        cout << "�ȽϽ��ӦΪ1��ʵ��Ϊ��" << (dt1 != dt2) << endl;

        wait_for_press();
    }

    cout << "-------DateTime����ʾ����-------:" << endl;

    return 0;
}