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

/**********************************************
*
*    TO-DO:
*        �벹ȫ������Ĵ��룬��ֻ�ύ���������Ĵ��롣
*
***********************************************/

class Book_Sale {
public:
    Book_Sale() {
    	number = 0;
        isbn[0] = '\0';
        sales_volume = 0;
        original_price = 0;
        discount = 0.0;
        real_price = 0;
        gross_sales = 0;
    }
    Book_Sale(int num, int slv, int orp, double dsc);
    Book_Sale(const Book_Sale& other);
    void isbn_plus();
    void display();
    friend istream& operator>>(istream& in, Book_Sale& b);
    Book_Sale& operator+=(int safr);
    Book_Sale& operator-=(int safr);
    void set(int num, int slv, int orp, double dsc=1);
    Book_Sale& operator=(const Book_Sale& b);
    bool operator>(const Book_Sale& b1)const;
    bool operator>=(const Book_Sale& b1)const;
    bool operator==(const Book_Sale& b1)const;
    bool operator<(const Book_Sale& b1)const;
    bool operator<=(const Book_Sale& b1)const;
    bool operator!=(const Book_Sale& b1)const;
private:
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
    cout << "�����ISBN��Ϊ:" << isbn << endl;
    cout << "����Ϊ:" << sales_volume << "��" << endl;
    cout << "ԭ��Ϊ:" << fixed << original_price << "Ԫ" << endl;
    cout << "�ۿ�Ϊ:" << fixed << discount << endl;
    cout << "�ּ�Ϊ:" << fixed << real_price << "Ԫ" << endl;
    cout << "�����۶�Ϊ:" << fixed << gross_sales << "Ԫ" << endl;
}
void Book_Sale::set(int num,int slv,int orp,double dsc)
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
    return in;
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
/**********************************************
*
*    TO-DO END
*
***********************************************/

int main()
{
	Book_Sale b1(95995, 3418, 100, 0.9);
	b1.display();
	b1.set(-1,3500,-1,0.8);
	b1.display();
	Book_Sale b2=b1;
	b2.display();
	Book_Sale b3;
	//b3=b1;
	
	return 0;
 } 
