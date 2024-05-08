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
	Student* p, * q; //p为工作指针，q为p的前驱；
	q = head;
	p = head;
	if (head == NULL || no <= 0) {//空表
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

void print_one_stu(Student* stu)
{
	cout << "学号:" << stu->no << " ";
	cout << "姓名:" << stu->name << " ";
	cout << "成绩:" << stu->score << " " << endl;

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
	/*冒泡排序  交换内容*/
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
	std::cout << "是否继续?(y/n): \n";
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
	cout << "优：" << tongji[1] << "人 ";
	cout << "良：" << tongji[2] << "人 ";
	cout << "中：" << tongji[3] << "人 ";
	cout << "及格：" << tongji[4] << "人 ";
	cout << "不及格：" << tongji[5] << "人 " << endl;
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
		// 程序查询循环
		int query;
		cout << "请输入要查询的学号:" << endl;
		std::cin >> query;
		if (cin.good() == 1) {
			/* 执行查询 */
			Student* search_result = searchbyID(head, query);
			if (search_result == NULL) {
				//cout << "学号为:[" << query << "]的同学 ";
				cout << "不存在" << endl;
			}
			else {
				print_one_stu(search_result);
			}
			if (!isContinue())
			{
				break; // 当接收到不需要继续，则退出循环
			}
		}
		else {
			//cout << "学号为:[" << query << "]的同学 ";
			cout << "不存在" << endl;
			if (!isContinue())
			{
				break; // 当接收到不需要继续，则退出循环
			}
		}
	}
}

void delbyID(Student* head)
{
	while (1)
	{
		/* 执行查询与删除 */
		int query = 0;
		std::cin >> query;
		if (cin.good() == 1) {
			/*查询*/
			Student* search_result = searchbyID(head, query);
			if (search_result == NULL) {
				cout << "不存在" << endl;
			}
			else {//因为之前已经找到，所以这里返回的一定不为空
				head = delete_node(head, query);
			}
			if (!isContinue())
			{
				break; // 当接收到不需要继续，则退出循环
			}
		}
		else {
			cout << "不存在" << endl;
			if (!isContinue())
			{
				break; // 当接收到不需要继续，则退出循环
			}
		}

	}
}

void modibyID(Student* head)
{
	while (1)
	{
		/* 执行查询与修改 */
		int query = 0;
		std::cin >> query;
		if (cin.good() == 1) {
			Student* search_result = searchbyID(head, query);
			if (search_result == NULL) {
				if (search_result == NULL) {
					cout << "不存在" << endl;
				}
			}
			else {
				//head = delete_node(head, query);
				modify_score(search_result);
			}
			if (!isContinue())
			{
				break; // 当接收到不需要继续，则退出循环
			}
		}
		else {
			cout << "不存在" << endl;
			if (!isContinue())
			{
				break; // 当接收到不需要继续，则退出循环
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
		if (cin.good() == 1) {/* 执行添加 */
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
			else {//因为之前已经找到，所以这里返回的一定不为空
				cout << "要插入的学号已存在" << endl;
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
    std::cout << "*\t1 显示记录\t2 统计记录\t3 排序记录\t*\n";
    std::cout << "*\t4 查找记录\t5 删除记录\t6 修改记录\t*\n";
    std::cout << "*\t7 添加记录\t0 退出系统\t\t\t*\n";
    for (i = 0; i < 57; i++)
    {
        std::cout << '*';
    }
	cout << endl;
}

int main()
{
    int choice; // 保证输入的为正整数数字
    char ch;
    // 在这里读取文件或作初始化操作，自行设计
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
		cout << "文件打开失败!" << endl;
		free(head);
		exit(EXIT_FAILURE);
	}
    menu();  // 调用菜单显示函数，为防止输出超出限度，请将此项放在循环外部

    while (true) // 注意该循环退出的条件
    {
         //system("CLS");
        // /* 清屏函数，为防止沙箱判断失误，请提交时保留此项为注释 */

        // 我们鼓励使用相关控制台美化代码美化图形界面，但是为了防止沙箱判题失误，
        // 请同样使相关语句保持注释，当人工审阅时会取消注释本地编译评阅！
        std::cout << "选择菜单项(0~7):";
        std::cin >> choice;
        if (choice == 0) // 选择退出
        {
            std::cout << "\n 确定退出吗?(y/n)" << std::endl;
            std::cin >> ch;
            if (ch == 'y' || ch == 'Y')
            {
                quit(head); // 自行设计
                break;
            }
            else
                continue;
        }
        switch (choice)
        {
            case 1:
                disp(head); // 自行设计
                break;
            case 2:
                count(head); // 自行设计
                break;
            case 3:
                sort_3(head,STUDENT_NUM); // 自行设计
                break;
            case 4:
                searchbyID_4(head); // 自行设计
                break;
            case 5:
                delbyID(head); // 自行设计
                break;
            case 6:
                modibyID(head); // 自行设计
                break;
            case 7:
                addbyID(head,&STUDENT_NUM); // 自行设计
                break;
            default:
                std::cout << "\n输入错误，请从新输入" << std::endl;
        }
    }
    return 0;
}