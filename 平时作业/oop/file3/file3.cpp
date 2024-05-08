#include<iostream>
using namespace std;

class Student
{
public:
	Student() {};
	Student(int n, int s) :no(n), score(s) {}
	void display_no();
	void display_score();
	void set(int no1, int score1) {
		no = no1;
		score = score1;
	}
private:
	int no;
	int score;
};
void Student::display_no()
{
	cout << no;
}
void Student::display_score()
{
	cout << score;
}
int main()
{
	Student stu[5];
	for (int i = 0; i < 5; ++i) {
		cout << "请输入第" << i+1 << "个学生的学号和成绩:" << endl;
		int no;
		int score;
		cin >> no >> score;
		stu[i].set(no, score);
	}
	for (int i = 0; i < 5; i += 2) {
		cout << "第" << i + 1 << "个学生的学号是";
		stu[i].display_no();
		cout << ", 成绩为 ";
		stu[i].display_score();
		cout << endl;
	}
	cout << "-*程序结束*-" << endl;
	return 0;
}