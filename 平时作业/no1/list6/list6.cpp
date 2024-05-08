#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<stdlib.h>
using namespace std;

struct student {
	int no;
	char name[20];
	int score;
	struct student* next;
};
typedef struct student Student;

int read(Student* head, int* num)
{
	FILE* fpRow;
	fpRow = fopen("student.txt", "r");
	//cout << fpRow<<endl;
	if (fpRow == NULL)
		return -1;
	char line[1024];
	int row = 0;
	while (fgets(line, sizeof(line), fpRow)) {
		if (line[0] == '\n' || line[0] == '\r')
			break;
		else
			row++;
	}
	fclose(fpRow);

	int j = 0;
	FILE* fp;
	fp = fopen("student.txt", "r");
	//cout << fp << endl;
	if (fp == NULL)
		return-1;
	Student* p = head;
	if (fgetc(fp) != EOF) {
		rewind(fp);
		while (!feof(fp) && j <= row) {
			if (j == 0) {
				fscanf(fp, "%d", num);//首行读入
				j++;
				continue;
			}
			else {
				Student* q = (Student*)malloc(sizeof(Student));
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
					free(q);
				else {
					if (j == 1) {
						fscanf(fp, "%d", &head->no);
						fscanf(fp, "%s", &head->name);
						fscanf(fp, "%d", &head->score);
						p = head;
						p->next = q;
					}
					else {
						fscanf(fp, "%d", &q->no);
						fscanf(fp, "%s", &q->name);
						fscanf(fp, "%d", &q->score);
						p->next = q;
						q->next = NULL;
						p = q;
					}

				}
			}
			j++;
		}
	}

	fclose(fp);
	return 1;
}

Student* searchbyID(Student* head, int no)
{
	if (no <= 0) {
		return NULL;
	}
	else {
		Student* p = head;
		while (p != NULL) {
			if (no != p->no) {
				p = p->next;
			}
			else {
				break;
			}
		}
		if (p == NULL)
			return NULL;
		else if (p->no == no) {
			return p;
		}
		else {
			return NULL;
		}
	}
}

Student* delete_node(Student* head, int no)
{
	Student* p, * q; //p为工作指针，q为p的前驱；
	q = head;
	p = head;
	if (head == NULL||no <= 0) {//空表
		return NULL;
	}
	else {//非空表
		while (p != NULL) {
			if (p->no != no) {
				q = p;
				p = p->next;
			}
			else
				break;
		}
		if (p == NULL) {
			return NULL;
		}
		else {
			if (p == head) {
				head = p->next;
				free(p);
			}
			else {
				q->next = p->next;
				free(p);
			}
			return head;
		}
	}
}

void list_print(Student* head)
{
	if (head == NULL)
		return;
	else {
		Student* p = head;
		int i = 0;
		while (p != NULL) {
			cout << "学号:" << p->no << " ";
			cout << "姓名:" << p->name << " ";
			cout << "成绩:" << p->score << " " << endl;
			p = p->next;
		}
	}
}

void FreeAllNode(Student* head) //动态内存清空
{
	Student* p = head;
	while (head != NULL) {
		p = head;
		head = head->next;
		free(p);
	}
}

bool isContinue()
{
    //std::cout << "是否继续?(y/n): \n";
    char tmp;
    std::cin >> tmp;
    if (tmp == 'Y' || tmp == 'y')
    {
        return true;
    }
    return false;
}

int main()
{
	int STUDENT_NUM = 0;
	Student* head = (Student*)malloc(sizeof(Student));
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
	/* 在这里读取文件 */
	int condition = read(head, &STUDENT_NUM);
    // 当你读取完成
	if (condition == 0) {
		cout << "文件打开失败!" << endl;
	}
	else {
		while (1)
		{
			/* 执行查询与删除 */
			int query = 0;
			//cout << "请输入要删除的学号:" << endl;
			std::cin >> query;
			if (cin.good() == 1) {
				/*查询*/
				Student* search_result = searchbyID(head, query);
				if (search_result == NULL) {
					cout << "不存在" << endl;
				}
				else {//因为之前已经找到，所以这里返回的一定不为空
					head=delete_node(head, query);
				}
				if (!isContinue())
				{
					break; // 当接收到不需要继续，则退出循环
				}
			}
			else {
				cout << "学号为:[" << query << "]的同学 ";
				cout << "不存在" << endl;
				if (!isContinue())
				{
					break; // 当接收到不需要继续，则退出循环
				}
			}

		}
	}
    /* 退出前打印现有名单 */
	list_print(head);
	FreeAllNode(head);
    return 0;
}