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
					cout << "no memory"<<endl;
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
	if (head == NULL || no <= 0) {//�ձ�
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

void sum(Student* head, int tongji[6])
{
	/*�����ι涨����: �� [90, 100], �� [80, 90), �� [70, 80), ���� [60, 70), ������ [0, 60)��*/
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

void modify_score(Student* query)
{
	int score2;
	cin >> score2;
	if (score2 >= 0 && score2 <= 100) {
		query->score = score2;
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

					strncpy(tmp_name, move->name, 20);
					strncpy(move->name, move->next->name, 20);
					strncpy(move->next->name, tmp_name, 20);
				}
				else if (move->score == move->next->score) {
					if (move->no > move->next->no) {
						tmp_no = move->no;
						move->no = move->next->no;
						move->next->no = tmp_no;

						tmp_score = move->score;
						move->score = move->next->score;
						move->next->score = tmp_score;

						strncpy(tmp_name, move->name, 20);
						strncpy(move->name, move->next->name, 20);
						strncpy(move->next->name, tmp_name, 20);
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

void quit(Student* head)
{
	FreeAllNode(head);
	exit(0);
}

void disp(Student* head)
{
	list_print(head);
}

void count(Student* head)
{
	int tongji[6] = { 0 };
	sum(head, tongji);
	cout << "�ţ�" << tongji[1] << "�� ";
	cout << "����" << tongji[2] << "�� ";
	cout << "�У�" << tongji[3] << "�� ";
	cout << "����" << tongji[4] << "�� ";
	cout << "������" << tongji[5] << "�� " << endl;
}

void sort_3(Student* head,int LIST_LEN)
{
	sort(head,LIST_LEN);
	list_print(head);
}

void searchbyID_4(Student* head)
{
	while (1)
	{
		// �����ѯѭ��
		int query;
		cout << "������Ҫ��ѯ��ѧ��:" << endl;
		std::cin >> query;
		if (cin.good() == 1) {
			/* ִ�в�ѯ */
			Student* search_result = searchbyID(head, query);
			if (search_result == NULL) {
				//cout << "ѧ��Ϊ:[" << query << "]��ͬѧ ";
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
			//cout << "ѧ��Ϊ:[" << query << "]��ͬѧ ";
			cout << "������" << endl;
			if (!isContinue())
			{
				break; // �����յ�����Ҫ���������˳�ѭ��
			}
		}
	}
}

void delbyID(Student* head)
{
	while (1)
	{
		/* ִ�в�ѯ��ɾ�� */
		int query = 0;
		std::cin >> query;
		if (cin.good() == 1) {
			/*��ѯ*/
			Student* search_result = searchbyID(head, query);
			if (search_result == NULL) {
				cout << "������" << endl;
			}
			else {//��Ϊ֮ǰ�Ѿ��ҵ����������ﷵ�ص�һ����Ϊ��
				head = delete_node(head, query);
			}
			if (!isContinue())
			{
				break; // �����յ�����Ҫ���������˳�ѭ��
			}
		}
		else {
			cout << "������" << endl;
			if (!isContinue())
			{
				break; // �����յ�����Ҫ���������˳�ѭ��
			}
		}

	}
}

void modibyID(Student* head)
{
	while (1)
	{
		/* ִ�в�ѯ���޸� */
		int query = 0;
		std::cin >> query;
		if (cin.good() == 1) {
			Student* search_result = searchbyID(head, query);
			if (search_result == NULL) {
				if (search_result == NULL) {
					cout << "������" << endl;
				}
			}
			else {
				//head = delete_node(head, query);
				modify_score(search_result);
			}
			if (!isContinue())
			{
				break; // �����յ�����Ҫ���������˳�ѭ��
			}
		}
		else {
			cout << "������" << endl;
			if (!isContinue())
			{
				break; // �����յ�����Ҫ���������˳�ѭ��
			}
		}
	}
}

void addbyID(Student* head,int *STUDENT_NUM)
{
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
				//scanf("%d", &q->no);
				q->no = query;
				scanf("%s", &q->name);
				scanf("%d", &q->score);
				q->next = NULL;
				*STUDENT_NUM++;
			}
			else {//��Ϊ֮ǰ�Ѿ��ҵ����������ﷵ�ص�һ����Ϊ��
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
	sort(head, *STUDENT_NUM);
}

void menu()
{
    int i;
    std::cout << std::endl;
    for (i = 0; i < 57; i++)
    {
        std::cout << '*';
    }
    std::cout << std::endl;
    std::cout << "*\t1 ��ʾ��¼\t2 ͳ�Ƽ�¼\t3 �����¼\t*\n";
    std::cout << "*\t4 ���Ҽ�¼\t5 ɾ����¼\t6 �޸ļ�¼\t*\n";
    std::cout << "*\t7 ��Ӽ�¼\t0 �˳�ϵͳ\t\t\t*\n";
    for (i = 0; i < 57; i++)
    {
        std::cout << '*';
    }
	cout << endl;
}

int main()
{
    int choice; // ��֤�����Ϊ����������
    char ch;
    // �������ȡ�ļ�������ʼ���������������
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
	int condition = read(head, &STUDENT_NUM);
	if (condition != 1) {
		cout << "�ļ���ʧ��!" << endl;
		free(head);
		exit(EXIT_FAILURE);
	}
    menu();  // ���ò˵���ʾ������Ϊ��ֹ��������޶ȣ��뽫�������ѭ���ⲿ

    while (true) // ע���ѭ���˳�������
    {
         //system("CLS");
        // /* ����������Ϊ��ֹɳ���ж�ʧ�����ύʱ��������Ϊע�� */

        // ���ǹ���ʹ����ؿ���̨������������ͼ�ν��棬����Ϊ�˷�ֹɳ������ʧ��
        // ��ͬ��ʹ�����䱣��ע�ͣ����˹�����ʱ��ȡ��ע�ͱ��ر������ģ�
        std::cout << "ѡ��˵���(0~7):";
        std::cin >> choice;
        if (choice == 0) // ѡ���˳�
        {
            std::cout << "\n ȷ���˳���?(y/n)" << std::endl;
            std::cin >> ch;
            if (ch == 'y' || ch == 'Y')
            {
                quit(head); // �������
                break;
            }
            else
                continue;
        }
        switch (choice)
        {
            case 1:
                disp(head); // �������
                break;
            case 2:
                count(head); // �������
                break;
            case 3:
                sort_3(head,STUDENT_NUM); // �������
                break;
            case 4:
                searchbyID_4(head); // �������
                break;
            case 5:
                delbyID(head); // �������
                break;
            case 6:
                modibyID(head); // �������
                break;
            case 7:
                addbyID(head,&STUDENT_NUM); // �������
                break;
            default:
                std::cout << "\n����������������" << std::endl;
        }
    }
    return 0;
}