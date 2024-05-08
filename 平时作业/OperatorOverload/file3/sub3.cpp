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

