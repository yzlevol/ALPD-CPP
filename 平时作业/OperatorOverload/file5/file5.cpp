#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <conio.h>

using namespace std;

inline void wait_for_press()
{
    cout << endl << "按任意键继续..." << endl;
    _getch();
}

/**********************************************
*
*    TO-DO:
*        请补全该区域的代码，并只提交在这个区域的代码。
*
***********************************************/

class Book_Sale {
public:
    Book_Sale() :number(0), isbn((char*)"\0"), sales_volume(0), original_price(0), discount(0.0), real_price(0), gross_sales(0) {};
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
    int number;   //isbn段
    char* isbn; // 指向书籍编号的指针
    int   sales_volume;   // 销售量
    int original_price; // 原始价格 
    double discount;       // 折扣
    int real_price;     // 实售价格
    int gross_sales;    // 销售总额
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
    cout << "该书的ISBN号为:" << isbn <<"，";
    cout << "销量为:" << sales_volume << "本" << "，";
    cout << "原价为:" << fixed << original_price << "元" << "，";
    cout << "折扣为:" << fixed << discount << "，";
    cout << "现价为:" << fixed << real_price << "元" << "，";
    cout << "总销售额为:" << fixed << gross_sales << "元" << endl;
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
    b.set(isbn_t, slv, price, dsc);
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
    {
        Book_Sale b1(95995, 3418, 100, 0.9);
        Book_Sale b2 = b1;
        Book_Sale b3;
        b3 = b1;

        cout << "测试初始化，display和cin重载" << endl;

        cout << "b1应该是该书的ISBN号为:978-7-121-95995-0，销量为:3418本，原价为:100元，折扣为:0.9，现价为:90元，总销售额为:307620元\n实际为：";
        b1.display();
        cout << "b2应该是同上，实际为：";
        b2.display();
        cout << "b3应该是同上，实际为：";
        b3.display();

        Book_Sale b4;
        cout << "请输入某书籍销售信息：" << endl;
        cin >> b4;
        cout << "b4应该是您刚输入的信息，实际为：";
        b4.display();

        wait_for_press();
    }

    {
        Book_Sale b1, b2, b3(95995, 3418, 100, 1);

        cout << "测试set" << endl;

        b1.set(95995, 3418, 100, 0.9);
        b2.set(95995, 3418, 100);
        b3.set(-1, 3500, -1, 0.8);

        cout << "b1应该是该书的ISBN号为:978-7-121-95995-0，销量为:3418本，原价为:100元，折扣为:0.9，现价为:90元，总销售额为:307620元\n实际为：";
        b1.display();
        cout << "b2应该是该书的ISBN号为:978-7-121-95995-0，销量为:3418本，原价为:100元，折扣为:1，现价为:100元，总销售额为:341800元\n实际为：";
        b2.display();
        cout << "b3应该是该书的ISBN号为:978-7-121-95995-0，销量为:3500本，原价为:100元，折扣为:0.8，现价为:80元，总销售额为:280000元\n实际为：";
        b3.display();

        wait_for_press();
    }

    {
        Book_Sale b1(95995, 3418, 100, 0.9);

        cout << "测试重载+=/-=" << endl;

        b1 += 10;
        cout << "b1应该是该书的ISBN号为:978-7-121-95995-0，销量为:3428本，原价为:100元，折扣为:0.9，现价为:90元，总销售额为:308520元\n实际为：";
        b1.display();

        b1 -= 10;
        cout << "b1应该是该书的ISBN号为:978-7-121-95995-0，销量为:3418本，原价为:100元，折扣为:0.9，现价为:90元，总销售额为:307620元\n实际为：";
        b1.display();


        wait_for_press();
    }

    {
        Book_Sale b1(95994, 3000, 100, 0.8);
        Book_Sale b2(95996, 4800, 100, 0.5);
        Book_Sale b3(95998, 2000, 100, 0.9);

        cout << "测试比较运算符" << endl;

        cout << "比较结果应为1，实际为：" << (b1 > b3) << endl;
        cout << "比较结果应为1，实际为：" << (b2 >= b3) << endl;
        cout << "比较结果应为0，实际为：" << (b1 < b3) << endl;
        cout << "比较结果应为0，实际为：" << (b2 <= b3) << endl;
        cout << "比较结果应为1，实际为：" << (b1 == b2) << endl;
        cout << "比较结果应为0，实际为：" << (b1 != b1) << endl;

        wait_for_press();
    }

    return 0;
}