#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
using namespace std;

struct student {
    int no;                // 学号
    char name[20];         // 姓名
    int score;             // 成绩
    struct student* next;  // 下一结点
    /*! 不允许修改上述结构 !*/
};
typedef struct student Student;

void DeleteAllNode(Student* head) //动态内存清空
{
    Student* p = head;
    while (head != NULL) {
        p = head;
        head = head->next;
        delete(p);
    }
}

void list_read(Student* head, int* num)//数据读入
{
    fstream fpRow;
    fpRow.open("student.txt", ios::in);
    if (!fpRow.is_open()) {
        cout << "文件打开失败!";
        exit(EXIT_FAILURE);
    }
    char line[1024];
    int row = 0;
    while (fpRow.getline(line, sizeof(Student))) {
        if (line[0] == '\n' || line[0] == '\r') {
            break;
        }
        else {
            row++;
        }
    }
    if (row == 0) {
        cout << "文件为空!";
        exit(0);
    }
    fpRow.close();
    int j = 0;
    fstream fp;
    fp.open("student.txt", ios::in);
    if (!fp.is_open()) {
        cout << "文件打开失败!";
        exit(EXIT_FAILURE);
    }
    Student* p = head;
    char ch;
    if (ch = fp.get() != EOF) {
        //将文件指针移动到文件开头
        fp.clear(std::ios::goodbit);
        fp.seekg(std::ios::beg);
        while (!fp.eof() && j <= row) {
            if (j == 0) {
                fp >> *num;
                j++;
                continue;
            }
            else {
                Student* q = new(std::nothrow) Student;
                while (q == NULL) {
                    Student* q = new(std::nothrow) Student;
                }
                if (q != NULL) {
                    q->next = NULL;
                    for (int i = 0; i < 20; i++) {
                        q->name[i] = 0;
                    }
                    q->no = 0;
                    q->score = 0;
                }
                else {
                    cout << "no memory" << endl;
                    exit(1);
                }
                q->next = NULL;
                if (j == row)
                    delete q;
                else {
                    if (j == 1) {
                        fp >> (head->no) >> (head->name) >> (head->score);
                        p = head;
                        p->next = q;
                    }
                    else {
                        fp >> (q->no) >> (q->name) >> (q->score);
                        p->next = q;
                        q->next = NULL;
                        p = q;
                    }
                }
                j++;
            }
        }
    }
    fp.close();
}

void list_print(Student* head)
{
    Student* p = head;
    int i = 0;
    while (p != NULL) {
        cout << "学号: " << p->no;
        cout << "姓名: " << p->name;
        cout << "成绩: " << p->score << endl;
        p = p->next;
    }
}

int main()
{
    int STUDENT_NUM = 0;
    Student* head = new(std::nothrow) Student;
    if (head != NULL) {
        head->next = NULL;
        for (int i = 0; i < 20; i++) {
            head->name[i] = 0;
        }
        head->no = 0;
        head->score = 0;
    }
    else {
        cout << "no memory" << endl;
        exit(1);
    }
    head->next = NULL;
    list_read(head, &STUDENT_NUM);
    cout << "所有的学生信息如下：" << endl;
    list_print(head);
    DeleteAllNode(head);
    //delete(head);
    return 0;
}