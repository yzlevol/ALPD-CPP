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
        cout << "教师号:" << id << " ";
        cout << "教师年龄:" << age << "岁 ";
        cout << "教师性别:" << ((gender == 0) ? "女" : "男") << " ";
        cout << "教师姓名:" << name << endl;
    }
};

class Student {
public:
    Student(int no, int ag, int sex, string na) :id(no), age(ag) , gender(sex), name(na) {};
    void show_info()
    {
        cout << "学生学号:" << id << " ";
        cout << "学生年龄:" << age << "岁 ";
        cout << "学生性别:" << ((gender == 0) ? "女" : "男") << " ";
        cout << "学生姓名:" << name << endl;
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

