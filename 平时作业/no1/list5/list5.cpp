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
				fscanf(fp, "%d", num);//���ж���
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

Student* search_no(Student* head, int no)
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

void print_one_stu(Student* stu)
{
	cout << "ѧ��:" << stu->no << " ";
	cout << "����:" << stu->name << " ";
	cout << "�ɼ�:" << stu->score << " " << endl;

}

void FreeAllNode(Student* head) //��̬�ڴ����
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
    std::cout << "�Ƿ������(y/n): \n";
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
    /* �������ȡ�ļ� */
	int condition = read(head, &STUDENT_NUM);
	if (condition == 0) {
		cout << "�ļ���ʧ��!" << endl;
	}
	else {
		// �����ȡ���
		while (1)
		{
			// �����ѯѭ��
			int query;
			cout << "������Ҫ��ѯ��ѧ��:"<<endl;
			std::cin >> query;
			if (cin.good() == 1) {
				/* ִ�в�ѯ */
				Student* search_result = search_no(head, query);
				if (search_result == NULL) {
					cout << "ѧ��Ϊ:[" << query << "]��ͬѧ ";
					cout << "������" << endl;
				}
				else {
					print_one_stu(search_result);
				}
				if (!isContinue())
				{
					break; // �����յ�����Ҫ���������˳�ѭ��
				}
			}
			else {
				cout << "ѧ��Ϊ:[" << query << "]��ͬѧ ";
				cout << "������" << endl;
				if (!isContinue())
				{
					break; // �����յ�����Ҫ���������˳�ѭ��
				}
			}
		}
	}
	FreeAllNode(head);
    return 0;
}