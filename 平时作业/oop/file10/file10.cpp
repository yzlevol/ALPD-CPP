#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<iomanip>
using namespace std;

class Book_Sale
{
private:
    char* isbn; // ָ���鼮��ŵ�ָ��
    // ����鼮��ŵĿռ��趯̬����
    // �鼮����� 5 �� 13 λ������ɣ��� 978-7-121-15535-2
    int    sales_volume;   // ������
    double original_price; // ԭʼ�۸�
    double real_price;     // ʵ�ۼ۸�
    double discount;       // �ۿ�
    double gross_sales;    // �����ܶ�

public:
    /* ���Խ��� istream & �����ж�ȡ�鼮������Ϣ�Ĺ��캯��Book_Sale (istream &)�����������Լ�������Ҫ�ĳ�Ա���� */
    Book_Sale(istream& cin);
    void set_data(int number, int slv, double price, double dsct);
    void display();                     //���
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
    // ��numberת����char���ͣ���λ����isbn_final�ַ�����
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
    // ��isbn���䶯̬�ڴ棬����isbn_final�ַ�����isbnָ����ڴ�ռ�
    isbn = new char[isbn_final.length() + 1];
    strcpy(isbn, isbn_final.c_str());
}

void Book_Sale::display()
{
    cout << "�����ISBN��Ϊ:" << isbn << endl;
    cout << "����Ϊ:" << sales_volume << "��" << endl;
    cout << "ԭ��Ϊ:" << fixed << setprecision(4) << original_price << "Ԫ" << endl;
    cout << "�ۿ�Ϊ:" << fixed << setprecision(4) << discount << endl;
    cout << "�ּ�Ϊ:" << fixed << setprecision(4) << real_price << "Ԫ" << endl;
    cout << "�����۶�Ϊ:" << fixed << setprecision(4) << gross_sales << "Ԫ" << endl;

    delete isbn;
}

int main()
{
    int number;
    int slv;
    double price;
    double dsct;
    cout << "����������:" << endl;
    Book_Sale book(cin);
    book.display();
    while (1) {
        cout << "����������: " << endl;
        cin >> number;
        if (number == -1) {
            break;
        }
        cin >> slv >> price >> dsct;
        book.set_data(number, slv, price, dsct);
        book.display();
    }
    cout << "-*�������*-" << endl;
    return 0;
}
