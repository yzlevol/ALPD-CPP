#include<iostream>
using namespace std;

class dateToDay
{
public:
    dateToDay(int y, int m, int d) : year(y), month(m), day(d)    // ͨ�����ι���
    {
        if (!checkValid()) {
            cout << "�������󣡳����˳�" << endl;
            exit(-1);
        }
    }
    void display();              // �����������(�������ڵڼ���)
private:
    bool checkLeap();            // �ú������ڼ������
    bool checkValid();           // �ú������ڼ��Ϸ�
    int computeDay();            // �ú������ڼ�������
    int year;
    int month;
    int day;
    int days[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
};

void dateToDay::display()  // �����������(�������ڵڼ���)
{
    cout << year << "-" << month << "-" << day;
    cout << "��" << year << "��ĵ�" << computeDay() << "��" << endl;
}

bool dateToDay::checkLeap() // �ú������ڼ������
{
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
        return true;
    else
        return false;
}

bool dateToDay::checkValid() // �ú������ڼ��Ϸ�
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

int dateToDay::computeDay() // �ú������ڼ�������
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
    cout << "������һ������:" << endl;
    cin >> y >> m >> d;
    if (cin.good() == 1) {
        dateToDay d1(y, m, d);
        d1.display();
    }
    else {
        cout << "�������󣡳����˳�";
        exit(-1);
    }
    cout << "������һ������:" << endl;
    cin >> y >> m >> d;
    if (cin.good() == 1) {
        dateToDay d2(y, m, d);
        d2.display();
    }
    else {
        cout << "�������󣡳����˳�";
        exit(-1);
    }
    return 0;
}