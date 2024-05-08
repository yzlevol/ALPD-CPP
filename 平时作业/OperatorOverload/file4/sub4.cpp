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
    os << date.year << "Äê" << date.month << "ÔÂ" << date.day << "ÈÕ"<<endl;
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
