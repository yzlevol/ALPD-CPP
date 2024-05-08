#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

using namespace std;

/**********************************************
*
*    TO-DO:
*        �벹ȫ������Ĵ��룬��ֻ�ύ���������Ĵ��롣
*
***********************************************/
class Student;
class Teacher {
private:
    int id;
    int age;
    string name;
    int gender;
public:
    Teacher() {};
    Teacher(int no, int ag, int sex, string na) { id = no; age = ag;  gender = sex; name = na; }
    Teacher(Student& stu);
    void show_info()
    {
        cout << "��ʦ��:" << id << " ";
        cout << "��ʦ����:" << age << "�� ";
        cout << "��ʦ�Ա�:" << ((gender == 0) ? "Ů" : "��") << " ";
        cout << "��ʦ����:" << name << endl;
    }
};

class Student {
public:
    Student(int no, int ag, int sex, string na) :id(no), age(ag) , gender(sex), name(na) {};
    void show_info()
    {
        cout << "ѧ��ѧ��:" << id << " ";
        cout << "ѧ������:" << age << "�� ";
        cout << "ѧ���Ա�:" << ((gender == 0) ? "Ů" : "��") << " ";
        cout << "ѧ������:" << name << endl;
    }
    int id;
    int age;
    string name;
    int gender;

};
Teacher::Teacher(Student& stu)
{
    id = stu.id;
    age = stu.age;
    name = stu.name;
    gender = stu.gender;
}

/**********************************************
*
*    TO-DO END
*
***********************************************/

int main() {
    int id, age, gender;
    char name[16];

    cin >> id >> age >> gender >> name;
    Student stu(id, age, gender, name);
    stu.show_info();

    Teacher teac;
    teac = (Teacher)stu;
    teac.show_info();
    return 0;
}