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
				q->next = NULL;
				if (j == row)
					free(q);
				else {
					fscanf(fp, "%d", &q->no);
					fscanf(fp, "%s", &q->name);
					fscanf(fp, "%d", &q->score);
					p->next = q;
					q->next = NULL;
					p = q;
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
		Student* p = head->next;
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

void delete_node(Student* head, int no)
{
	Student* p, * q; //pΪ����ָ�룬qΪp��ǰ����
	q = head->next;
	p = head->next;
	if (head == NULL || no <= 0 || head->next==NULL) {//�ձ�
		return;
	}
	else {//�ǿձ�
		while (p != NULL) {
			if (p->no != no) {
				q = p;
				p = p->next;
			}
			else
				break;
		}
		if (p == NULL) {
			return;
		}
		else {
			if (p == head->next)
				head->next = p->next;
			q->next = p->next;
			free(p);
			return;
		}
	}
}

void list_print(Student* head)
{
	if (head->next == NULL)
		return;
	else {
		Student* p = head->next;
		int i = 0;
		while (p != NULL) {
			cout << "ѧ��:" << p->no << " ";
			cout << "����:" << p->name << " ";
			cout << "�ɼ�:" << p->score << " " << endl;
			p = p->next;
		}
	}
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
    std::cout << "�Ƿ����?(y/n): \n";
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
    /* �������ȡ�ļ� */
	int STUDENT_NUM = 0;
	Student* head = (Student*)malloc(sizeof(Student));
	if (head != NULL) {
		head->next = NULL;
		head->no = 0;
		head->score = 0;
		for (int i = 0; i < 20; i++) {
			head->name[i] = 0;
		}
	}
	int condition = read(head, &STUDENT_NUM);
    // �����ȡ���
	if (condition != 1) {
		cout << "�ļ���ʧ��!" << endl;
		exit(EXIT_FAILURE);
	}
	else {
		while (1)
		{
			int query = 0;
			std::cin >> query;
			if (cin.good() == 1) {
				Student* search_result = searchbyID(head, query);
				/* ִ�в�ѯ��ɾ�� */
				if (search_result == NULL) {
					cout << "������" << endl;
				}
				else {
					delete_node(head, query);
				}
				if (!isContinue())
				{
					break; // �����յ�����Ҫ���������˳�ѭ��
				}
			}
			else {
				cout << "�������" << endl;
				if (!isContinue())
				{
					break; // �����յ�����Ҫ���������˳�ѭ��
				}
			}
		}
	}
    /* �˳�ǰ��ӡ�������� */
	list_print(head);
	FreeAllNode(head);
    return 0;
}