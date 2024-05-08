#include <iostream>
#include <cmath>

using namespace std;

/**********************************************
*
*    TO-DO:
*        请补全该区域的代码，并只提交在这个区域的代码。
*
***********************************************/
class Shape
{
public:
    virtual double area() const = 0;
};

class Circle :public Shape
{
private:
    double rad;
public:
    Circle(double r) :rad(r) {}
    double area() const {
        cout << "圆形的面积是：";
        return (3.14159) * rad * rad;
    }
};

class Square :public Shape
{
private:
    double side;
public:
    Square(double s) :side(s) {}
    double area() const
    {
        cout << "正方形的面积是：";
        return side * side;
    }
};

class Rectangle :public Shape
{
private:
    double length;
    double width;
public:
    Rectangle(double l, double w) :length(l), width(w) {}
    double area() const
    {
        cout << "长方形的面积是：";
        return length * width;
    }
};

class Trapezoid :public Shape
{
private:
    double upSide;
    double downSide;
    double height;
public:
    Trapezoid(double u, double d, double h) :upSide(u), downSide(d), height(h) {}
    double area() const
    {
        cout << "梯形的面积是：";
        return (upSide + downSide) * height / 2.0;
    }
};

class Triangle :public Shape
{
private:
    double side1;
    double side2;
    double side3;
public:
    Triangle(double s1, double s2, double s3) : side1(s1), side2(s2), side3(s3) {}
    double area() const {
        cout << "三角形的面积是：";
        double p = (side1 + side2 + side3) / 2.0;
        return sqrt(p * (p - side1) * (p - side2) * (p - side3));
    }
};


/**********************************************
*
*    TO-DO END
*
***********************************************/

int main() {
    Circle    c1(2);
    Square    s1(3);
    Rectangle r1(4, 5);
    Trapezoid t1(6, 7, 8);
    Triangle  t2(3, 4, 5);

    Shape* s[5] = { &c1, &s1, &r1, &t1, &t2 };

    for (int i = 0; i < 5; i++) {
        cout << s[i]->area() << endl;
    }
    return 0;
}