#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<iomanip>
using namespace std;

class Book_Sale
{
private:
    char* isbn; // 指向书籍编号的指针
    // 存放书籍编号的空间需动态申请
    // 书籍编号由 5 段 13 位数字组成，如 978-7-121-15535-2
    int    sales_volume;   // 销售量
    double original_price; // 原始价格
    double real_price;     // 实售价格
    double discount;       // 折扣
    double gross_sales;    // 销售总额

public:
    /* 可以接受 istream & 并从中读取书籍销售信息的构造函数Book_Sale (istream &)，析构函数以及其他必要的成员函数 */
    Book_Sale(istream& cin);
    void set_data(int number, int slv, double price, double dsct);
    void display();                     //输出
    void isbn_plus();
};
Book_Sale::Book_Sale(istream& cin)
{
    int number=0;
    int slv;
    double price;
    double dsct;
    if (number == -1)
        return;
    cin >> number >> slv >> price >> dsct;
    //set_isbn(number);
    set_data(number, slv, price, dsct);
    sales_volume = slv;
    original_price = price;
    discount = dsct;
    real_price = price * dsct;
    gross_sales = real_price * slv;
}
void Book_Sale::isbn_plus()
{
    string isbn_final;
    isbn_final = "978-7-121-";
    // 将number转换成char类型，按位加入isbn_final字符串中
    for (int i = 0; i < 4; ++i) {
        isbn_final += char(number % 10 + '0');
        number /= 10;
    }
    isbn_final += "-";
    int x[6] = { 0 };
    for (int i = 4; i < 10; ++i) {
        x[i-4] = number % 10;
        number /= 10;
    }
    x[5] = 10 - (67 + 3 * x[0] + x[1] + 3 * x[2] + x[3] + 3 * x[4]) % 10;
    if (x[5] == 10)
        x[5] = 0;
    for (int i = 5; i >= 0; --i) {
        isbn_final += char(x[i] + '0');
    }
    isbn_final += '\0';
    // 给isbn分配动态内存，复制isbn_final字符串到isbn指向的内存空间
    isbn = new char[isbn_final.length() + 1];
    strcpy(isbn, isbn_final.c_str());
}

void Book_Sale::display()
{
    cout << "该书的ISBN号为:" << isbn << endl;
    cout << "销量为:" << sales_volume << "本" << endl;
    cout << "原价为:" << fixed << setprecision(4) << original_price << "元" << endl;
    cout << "折扣为:" << fixed << setprecision(4) << discount << endl;
    cout << "现价为:" << fixed << setprecision(4) << real_price << "元" << endl;
    cout << "总销售额为:" << fixed << setprecision(4) << gross_sales << "元" << endl;

    delete isbn;
}

int main()
{
    int number;
    int slv;
    double price;
    double dsct;
    cout << "请输入数据:" << endl;
    Book_Sale book(cin);
    book.display();
    while (1) {
        cout << "请输入数据: " << endl;
        cin >> number;
        if (number == -1) {
            break;
        }
        cin >> slv >> price >> dsct;
        book.set_data(number, slv, price, dsct);
        book.display();
    }
    cout << "-*程序结束*-" << endl;
    return 0;
}
