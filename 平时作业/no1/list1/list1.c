#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

struct student {
	int no;                // ѧ��
	char name[20];         // ����
	int score;             // �ɼ�
	struct student* next;  // ��һ���
	/*! �������޸������ṹ !*/
};
typedef struct student Student;

void FreeAllNode(Student* head) //��̬�ڴ����
{
	Student* p = head;
	while (head != NULL) {
		p = head;
		head = head->next;
		free(p);
	}
}

void list_read(Student* head,int *num)//��������
{
	FILE* fpRow;
	fpRow=fopen("student.txt","r");
	if (fpRow == NULL) {
		printf("�ļ���ʧ��!");
		exit(EXIT_FAILURE);
	}
	char line[1024];
	int row = 0;
	while (fgets(line, sizeof(line), fpRow)) {
		if (line[0] == '\n' || line[0] == '\r') {//�����ж�
			break;
		}
		else {
			row++;
		}
	}
	//cout << row;
	fclose(fpRow);

	int j;
	j = 0;
	FILE* fp;
	fp=fopen("student.txt", "r");
	if (fp == NULL) {
		printf("�ļ���ʧ��!");
		exit(EXIT_FAILURE);
	}
	Student* p = head;
	if (fgetc(fp) != EOF) {
		rewind(fp);
		while (feof(fp) != EOF && j <= row) {
			if (j == 0) {
				fscanf(fp, "%d", num);
				j++;
				continue;
			}
			else {
				Student* q = (struct student*)malloc(sizeof(Student));
				if (q != NULL) {
					q->next = NULL;
					for (int i = 0; i < 20; i++) {
						q->name[i] = 0;
					}
					q->no = 0;
					q->score = 0;
				}
				else {
					printf("no memory\n");
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
					j++;
				
			}
		}
	}
	fclose(fp);
}

void list_print(Student* head)
{
	Student* p = head;
	int i = 0;
	while (p != NULL) {
		printf("ѧ��:%d ", p->no);
		printf("����:%s ", p->name);
		printf("�ɼ�:%d ", p->score);
		printf("\n");
		p = p->next;
	}
}

int main()
{
	int STUDENT_NUM = 0;

	Student* head = (struct student*)malloc(sizeof(Student));
	if (head != NULL) {
		head->next = NULL;
		for (int i = 0; i < 20; i++) {
			head->name[i] = 0;
		}
		head->no = 0;
		head->score = 0;
	}
	else {
		printf("no memory\n");
		exit(1);
	}
	head->next = NULL;
	list_read(head, &STUDENT_NUM);
	printf("���е�ѧ����Ϣ���£�\n");
	list_print(head);
	FreeAllNode(head);//�ͷ����нڵ�
	return 0;
}
