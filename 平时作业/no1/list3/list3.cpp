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

void FreeAllNode(Student* head) //动态内存清空
{
	Student* p = head;
	while (head!=NULL) {
		p = head;
		head = head->next;
		free(p);
	}
}

void sum(Student* head, int tongji[6])
{
	/*分数段规定如下: 优 [90, 100], 良 [80, 90), 中 [70, 80), 及格 [60, 70), 不及格 [0, 60)。*/
	Student* p = head;
	int i = 0;
	while (p != NULL) {
		if (p->score >= 90 && p->score <= 100) {
			tongji[1]++;
		}
		else if (p->score >= 80 && p->score < 90) {
			tongji[2]++;
		}
		else if (p->score >= 70 && p->score < 80) {
			tongji[3]++;
		}
		else if (p->score >= 60 && p->score < 70) {
			tongji[4]++;
		}
		else if (p->score >= 0 && p->score <= 60) {
			tongji[5]++;
		}
		else;
		p = p->next;
	}
}

int main()
{
	int tongji[6] = { 0 }; //用于记录各区间人数  0为总人数，1-5为各分数段人数
	int &STUDENT_NUM = tongji[0];
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
	int condition = read(head, &STUDENT_NUM);
	if (condition == 1) {
		/*统计信息如下：优: 15人 良: 4人 中: 6人 及格: 6人 不及格: 21人*/
		sum(head, tongji);
		cout << "统计信息如下：";
		cout << "优：" << tongji[1] << "人 ";
		cout << "良：" << tongji[2] << "人 ";
		cout << "中：" << tongji[3] << "人 ";
		cout << "及格：" << tongji[4] << "人 ";
		cout << "不及格：" << tongji[5] << "人 " << endl;
	}
	else {
		cout << "文件打开失败!" << endl;
	}
	FreeAllNode(head);
	return 0;
}