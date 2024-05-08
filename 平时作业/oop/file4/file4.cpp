#include <iostream>

using namespace std;

class Student
{
public:
    Student(int n, float s) :num(n), score(s) {}
    void change(int n, float s) { num = n; score = s; }
    void display() { cout << num << " " << score << endl; }
private:
    int num;
    float score;
};

int main()
{
    Student stud(101, 78.5);
    stud.display();
    stud.change(101, 80.5);
    stud.display();
    return 0;
}
/*
- *Result - *
output:
101 78.5
101 80.5
- *end * -
Analysis
����һ�������Զ����࣬����ѧ��ѧ�ųɼ��������޸ĵ�ʾ������
��Student���У�ѧ��num�ͳɼ�scoreΪ˽�г�Ա���޷����ⲿ���ʡ����г�Ա��ͬ�����Զ��幹�캯���ͺ�����Աchange(�����޸�ѧ����Ϣ)����display(�������ѧ����Ϣ)
���캯��Studentʹ�ú����б����ʽ��num��score���г�ʼ��
change����������n��ֵ��num��s��ֵ��score�ﵽ�޸ĵ�Ŀ��
display�����ǰ��ѧ����Ϣ
main�������½���stud���󣬲������������캯����ʼ����Ȼ�����
���ŵ���change�����޸�ѧ����Ϣ��Ȼ�������
*/