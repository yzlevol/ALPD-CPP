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
	Student* p, * q; //pΪ����ָ�룬qΪp��ǰ����
	q = head;
	p = head;
	if (head == NULL) {//�ձ�
		return NULL;
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
			cout << "ѧ��:" << p->no << " ";
			cout << "����:" << p->name << " ";
			cout << "�ɼ�:" << p->score << " " << endl;
			p = p->next;
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

void sort(Student* head, int list_len)
{
	/*ð������  ��������*/
	if (head == NULL || list_len == 1) {
		return;
	}
	else {
		int tmp_no = 0;
		char tmp_name[20];
		int tmp_score = 0;
		Student* move = head;
		for (int i = 0; i < list_len - 1; i++) {
			while (move->next != NULL) {
				if (move->score < move->next->score) {
					tmp_no = move->no;
					move->no = move->next->no;
					move->next->no = tmp_no;

					tmp_score = move->score;
					move->score = move->next->score;
					move->next->score = tmp_score;

					strncpy(tmp_name, move->name,20);
					strncpy(move->name, move->next->name,20);
					strncpy(move->next->name, tmp_name,20);
				}
				else if (move->score == move->next->score) {
					if (move->no > move->next->no) {
						tmp_no = move->no;
						move->no = move->next->no;
						move->next->no = tmp_no;

						tmp_score = move->score;
						move->score = move->next->score;
						move->next->score = tmp_score;

						strncpy(tmp_name, move->name,20);
						strncpy(move->name, move->next->name,20);
						strncpy(move->next->name, tmp_name,20);
					}
				}
				move = move->next;
			}
			move = head;
		}
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
    // �����ȡ���
	if (condition == 0) {
		cout << "�ļ���ʧ��!" << endl;
	}
	else {
		while (1)
		{
			int query = 0;
			std::cin >> query;
			if (cin.good() == 1) {/* ִ����� */
				Student* search_result = searchbyID(head, query);
				if (search_result == NULL) {
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
					Student* p = head;
					while (p->next != NULL) {
						p = p->next;
					}
					p->next = q;
					
					char tname[1000] = { 0 };
					std::cin >> tname >> q->score;
					q->no = query;
					tname[20] = '\0';
					for (int i = 0; i < 20; i++) {
						q->name[i] = tname[i];
					}
					q->next = NULL;
					STUDENT_NUM++;
				}
				else {
					cout << "Ҫ�����ѧ���Ѵ���" << endl;
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
    /* �˳�ǰ���򲢴�ӡ�������� */
	sort(head, STUDENT_NUM);
	list_print(head);
	FreeAllNode(head);
    return 0;
}