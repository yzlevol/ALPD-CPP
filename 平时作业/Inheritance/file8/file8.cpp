#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <conio.h>
using namespace std;

inline void wait_for_press()
{
    cout << endl << "�����������..." << endl;
    _getch();
}

class Book_Sale {
public:
    Book_Sale() :number(0), isbn((char*)"\0"), sales_volume(0), original_price(0), discount(0.0), real_price(0), gross_sales(0) {};
    Book_Sale(int num, int slv, int orp, double dsc);
    Book_Sale(const Book_Sale& other);
    void isbn_plus();
    void display();
    friend istream& operator>>(istream& in, Book_Sale& b);
    friend ostream& operator<<(ostream& os, const Book_Sale& book);
    Book_Sale& operator+=(int safr);
    Book_Sale& operator-=(int safr);
    void set(int num, int slv, int orp, double dsc = 1);
    Book_Sale& operator=(const Book_Sale& b);
    bool operator>(const Book_Sale& b1)const;
    bool operator>=(const Book_Sale& b1)const;
    bool operator==(const Book_Sale& b1)const;
    bool operator<(const Book_Sale& b1)const;
    bool operator<=(const Book_Sale& b1)const;
    bool operator!=(const Book_Sale& b1)const;
protected:
    int number;   //isbn��
    char* isbn; // ָ���鼮��ŵ�ָ��
    int   sales_volume;   // ������
    int original_price; // ԭʼ�۸� 
    double discount;       // �ۿ�
    int real_price;     // ʵ�ۼ۸�
    int gross_sales;    // �����ܶ�
};
void Book_Sale::isbn_plus()
{
    char isbn_final[20] = "978-7-121-";
    char num_str[10];
    sprintf(num_str, "%d", number);
    strcat(isbn_final, num_str);
    strcat(isbn_final, "-");

    int x[14] = { 0 };
    for (int i = 12; i >= 8; i--) {
        x[i] = number % 10;
        if (i != 8)
            number /= 10;
    }

    x[13] = 10 - (67 + 3 * x[8] + x[9] + 3 * x[10] + x[11] + 3 * x[12]) % 10;
    if (x[13] == 10)
        x[13] = 0;

    char check_str[2];
    sprintf(check_str, "%d", x[13]);

    strcat(isbn_final, check_str);
    strcat(isbn_final, "\0");

    isbn = new char[strlen(isbn_final) + 1];
    strcpy(isbn, isbn_final);
}
Book_Sale::Book_Sale(int num, int slv, int orp, double dsc)
{
    number = num;
    sales_volume = slv;
    original_price = orp;
    discount = dsc;
    real_price = (int)(original_price * discount);
    gross_sales = real_price * sales_volume;
    isbn_plus();
}
Book_Sale::Book_Sale(const Book_Sale& b)
{
    isbn = b.isbn;
    number = b.number;
    sales_volume = b.sales_volume;
    original_price = b.original_price;
    discount = b.discount;
    real_price = b.real_price;
    gross_sales = b.gross_sales;
}
void Book_Sale::display()
{
    cout << "�����ISBN��Ϊ:" << isbn << "��";
    cout << "����Ϊ:" << sales_volume << "��" << "��";
    cout << "ԭ��Ϊ:" << fixed << original_price << "Ԫ" << "��";
    cout << "�ۿ�Ϊ:" << fixed << discount << "��";
    cout << "�ּ�Ϊ:" << fixed << real_price << "Ԫ" << "��";
    cout << "�����۶�Ϊ:" << fixed << gross_sales << "Ԫ" << endl;
}
void Book_Sale::set(int num, int slv, int orp, double dsc)
{
    if (num != -1) {
        number = num;
        isbn_plus();
    }
    if (slv != -1)
        sales_volume = slv;
    if (orp != -1)
        original_price = orp;
    if (dsc != -1)
        discount = dsc;
    real_price = (int)(original_price * discount);
    gross_sales = real_price * sales_volume;
}
istream& operator>>(istream& in, Book_Sale& b)
{
    int isbn_t, slv, price;
    double dsc;
    in >> isbn_t >> slv >> price >> dsc;
    b.set(isbn_t, slv, price, dsc);
    return in;
}
ostream& operator<<(ostream& os, const Book_Sale& b)
{
    os << "ISBN��:" << b.isbn << "��";
    os << "����Ϊ:" << b.sales_volume << "��" << "��";
    os << "ԭ��Ϊ:" << fixed << b.original_price << "Ԫ" << "��";
    os << "�ۿ�Ϊ:" << fixed << b.discount << "��";
    os << "�ּ�Ϊ:" << fixed << b.real_price << "Ԫ" << "��";
    os << "�����۶�Ϊ:" << fixed << b.gross_sales << "Ԫ��";
    return os;
}
Book_Sale& Book_Sale::operator=(const Book_Sale& b)
{
    if (this == &b)
        return *this;
    isbn = b.isbn;
    number = b.number;
    sales_volume = b.sales_volume;
    original_price = b.original_price;
    discount = b.discount;
    real_price = b.real_price;
    gross_sales = b.gross_sales;
    return *this;
}
Book_Sale& Book_Sale::operator+=(int safr)
{
    sales_volume += safr;
    gross_sales += safr * real_price;
    return *this;
}
Book_Sale& Book_Sale::operator-=(int safr)
{
    sales_volume -= safr;
    gross_sales -= safr * real_price;
    return *this;
}
bool Book_Sale::operator>(const Book_Sale& b)const
{
    return gross_sales > b.gross_sales;
}
bool Book_Sale::operator>=(const Book_Sale& b)const
{
    return gross_sales >= b.gross_sales;
}
bool Book_Sale::operator==(const Book_Sale& b)const
{
    return gross_sales == b.gross_sales;
}
bool Book_Sale::operator<(const Book_Sale& b)const
{
    return gross_sales < b.gross_sales;
}
bool Book_Sale::operator<=(const Book_Sale& b)const
{
    return gross_sales <= b.gross_sales;
}
bool Book_Sale::operator!=(const Book_Sale& b)const
{
    return gross_sales != b.gross_sales;
}

class Book_Sale_Limit : public Book_Sale {
public:
    Book_Sale_Limit() : Book_Sale(), discount_limit(0) {}
    Book_Sale_Limit(int num, int slv, int orp, double dsc, int limit);
    void set(int num, int slv, int orp, double dsc, int limit);
    void display();
    friend istream& operator>>(istream& in, Book_Sale_Limit& b);
    friend ostream& operator<<(ostream& os, const Book_Sale_Limit& book);
    void refresh();
    int show_dsc_limit() {
        return discount_limit;
    }
private:
    int discount_limit;   // �ۿ�����
};

Book_Sale_Limit::Book_Sale_Limit(int num, int slv, int orp, double dsc, int limit)
    : Book_Sale(num, slv, orp, dsc), discount_limit(limit) {}

void Book_Sale_Limit::set(int num, int slv, int orp, double dsc, int limit) {
    Book_Sale::set(num, slv, orp, dsc);
    discount_limit = limit;
}
void Book_Sale_Limit::refresh()
{

    int limited_sales = min(sales_volume, discount_limit);
    int excess_sales = max(sales_volume - discount_limit, 0);
    int limited_sales_gross_sales = limited_sales * real_price;
    int excess_sales_gross_sales = excess_sales * original_price;
    gross_sales = limited_sales_gross_sales + excess_sales_gross_sales;
}
void Book_Sale_Limit::display() {
    refresh();
    cout << "ISBN��: " << isbn << "��";
    cout << "����Ϊ: " << sales_volume << "����";
    cout << "ԭ��Ϊ: " << original_price << "Ԫ��";
    cout << "�ۿ�Ϊ: " << discount << "��";
    cout << "�ּ�Ϊ: " << real_price << "Ԫ��";
    cout << "�ۿ�����Ϊ: " << discount_limit << "����";
    cout << "�����۶�Ϊ: " << gross_sales << "Ԫ" << endl;
}
istream& operator>>(istream& in, Book_Sale_Limit& b)
{
    int isbn_t, slv, price ,lim;
    double dsc;
    in >> isbn_t >> slv >> price >> dsc >>lim;
    b.set(isbn_t, slv, price, dsc, lim);
    return in;
}
ostream& operator<<(ostream& os,Book_Sale_Limit& b) 
{
    b.refresh();
    cout << static_cast<Book_Sale>(b);
    os << "�ۿ�����Ϊ: " << b.show_dsc_limit() << "��" << endl;
    return os;
}
int main()
{
    {
        Book_Sale_Limit b1(95995, 3418, 100, 0.9, 3000);
        Book_Sale_Limit b2 = b1;
        Book_Sale_Limit b3;
        b3 = b1;
        cout << "���Գ�ʼ����cout��cin����" << endl;
        cout << "b1Ӧ����ISBN��:978-7-121-95995-0������Ϊ:3418����ԭ��Ϊ:100Ԫ���ۿ�Ϊ:0.9���ּ�Ϊ:90Ԫ�������۶�Ϊ:311800Ԫ���ۿ�����Ϊ:3000��\nʵ��Ϊ��";
        cout << b1;
        cout << "b2Ӧ����ͬ�ϣ�ʵ��Ϊ��";
        cout << b2;
        cout << "b3Ӧ����ͬ�ϣ�ʵ��Ϊ��";
        cout << b3;
        Book_Sale_Limit b4;
        cout << "������ĳ�鼮������Ϣ��" << endl;
        cin >> b4;
        cout << "b4Ӧ���������������Ϣ��ʵ��Ϊ��";
        cout << b4;
        wait_for_press();
    }

    {
        Book_Sale_Limit b1, b2, b3(95995, 3418, 100, 1, 4000);
        cout << "����set" << endl;
        b1.set(95995, 3418, 100, 0.9, 3000);
        b2.set(95995, 3418, 100, 0.9, 4000);
        b3.set(-1, 3500, -1, 0.8, 4000);
        cout << "b1Ӧ����ISBN��:978-7-121-95995-0������Ϊ:3418����ԭ��Ϊ:100Ԫ���ۿ�Ϊ:0.9���ּ�Ϊ:90Ԫ�������۶�Ϊ:311800Ԫ���ۿ�����Ϊ:3000��\nʵ��Ϊ��";
        cout << b1;
        cout << "b2Ӧ����ISBN��:978-7-121-95995-0������Ϊ:3418����ԭ��Ϊ:100Ԫ���ۿ�Ϊ:0.9���ּ�Ϊ:90Ԫ�������۶�Ϊ:307620Ԫ���ۿ�����Ϊ:4000��\nʵ��Ϊ��";
        cout << b2;
        cout << "b3Ӧ����ISBN��:978-7-121-95995-0������Ϊ:3500����ԭ��Ϊ:100Ԫ���ۿ�Ϊ:0.8���ּ�Ϊ:80Ԫ�������۶�Ϊ:280000Ԫ���ۿ�����Ϊ:4000��\nʵ��Ϊ��";
        cout << b3;
        wait_for_press();
    }

    {
        Book_Sale_Limit b1(95995, 3418, 100, 0.9, 5000);
        cout << "��������+=/-=" << endl;
        b1 += 10;
        cout << "b1Ӧ����ISBN��:978-7-121-95995-0������Ϊ:3428����ԭ��Ϊ:100Ԫ���ۿ�Ϊ:0.9���ּ�Ϊ:90Ԫ�������۶�Ϊ:308520Ԫ���ۿ�����Ϊ:5000��\nʵ��Ϊ��";
        cout << b1;
        b1 -= 10;
        cout << "b1Ӧ����ISBN��:978-7-121-95995-0������Ϊ:3418����ԭ��Ϊ:100Ԫ���ۿ�Ϊ:0.9���ּ�Ϊ:90Ԫ�������۶�Ϊ:307620Ԫ���ۿ�����Ϊ:5000��\nʵ��Ϊ��";
        cout << b1;
        wait_for_press();
    }

    {
        Book_Sale_Limit b1(95994, 3000, 100, 0.8, 2000);
        Book_Sale_Limit b2(95996, 4800, 100, 0.5, 4000);
        Book_Sale_Limit b3(95998, 2000, 100, 0.9, 1000);
        cout << "���ԱȽ������" << endl;
        cout << "�ȽϽ��ӦΪ1��ʵ��Ϊ��" << (b1 > b3) << endl;
        cout << "�ȽϽ��ӦΪ1��ʵ��Ϊ��" << (b2 >= b3) << endl;
        cout << "�ȽϽ��ӦΪ0��ʵ��Ϊ��" << (b1 < b3) << endl;
        cout << "�ȽϽ��ӦΪ0��ʵ��Ϊ��" << (b2 <= b3) << endl;
        cout << "�ȽϽ��ӦΪ1��ʵ��Ϊ��" << (b1 == b2) << endl;
        cout << "�ȽϽ��ӦΪ0��ʵ��Ϊ��" << (b1 != b1) << endl;
        wait_for_press();
    }

    return 0;
}