#pragma once
#include"Wall.h"
#include"Animal.h"
#include "enum.h"
#include<fstream>
#include<iostream>
using namespace std;

class duiLie
{
private:
	int len;
	int life;
	int score;
	char lastDir;
	bool ifDie;
	int sleepChange1;
	int sleepChange2;
	//
	struct node //链表储存
	{
		int x;
		int y;
		node* next;
	};
	node* head; //头
	
public:
	duiLie(Wall& tempWall, Animal& tempAnimal): wall(tempWall),animal(tempAnimal) {
		head = new node;
		ifDie = false;
		len = 4;
		score = 0;
		life = 5;
		lastDir = UP;
		Lv = 1;
		ifGift = 0;
		ifPoison = 0;
		sleepChange1 = 0;
		sleepChange2 = 0;
	}
	Wall& wall;
	Animal& animal;
	void move(int x, int y);
	int Lv;
	bool ifGift;
	bool ifPoison;
	
	void initDuiLie();
	bool randBorn();
	bool ISDEAD();
	int getScore();
	int getLength();
	int getLife();
	int getHx();
	int getHy();
	void moveDuiLie(char Dir);
	void sleep();
	void deleteDuiLie();
	void saveData();
	void duiLieToWall();
	void duiLieToAnimal();
	void duiLieToSpace();
	void Die();
	void reduceLife(int n);
	void showDuiLie();
};

void duiLie::move(int a, int b)
{
	bool ifDrawHead = 1;
	node* p = head;
	node* last = NULL;
	p = new node;
	p->x = head->x + a;
	p->y = head->y + b;
	p->next = head;
	head = p;
	while (p->next != NULL)
	{
		last = p;
		p = p->next;
	}
	if (Lv == 4)
	{

		bool isAccelerating = false;  // 标记是否正在加速
		bool isDecelerating = false;  // 标记是否正在加速
			// 检测 Shift 键的状态
			if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
				isAccelerating = true;
			else
				isAccelerating = false;
			if (isAccelerating)
				sleepChange1 = -100; 
			else
				sleepChange1 = 0;


			if (GetAsyncKeyState(VK_CONTROL) & 0x8000)
				isDecelerating = true;
			else
				isDecelerating = false;
			if (isDecelerating)
				sleepChange2 = 100;
			else
				sleepChange2 = 0; 
	}
	if (wall.getWhat(head->x, head->y) == SPACE || (head->x == p->x && head->y == p->y))
	{
		wall.change(p->x, p->y, SPACE);
		delete p;
		last->next = NULL;
	}
	if (wall.getWhat(head->x, head->y) == ANIMAL)
	{
		mciSendString(TEXT("play eatmusic from 0"), NULL, 0, NULL);
		animal.writeEat(head->x, head->y);
		len++;
		score += 10;
	}
	if (wall.getWhat(head->x, head->y) == GIFT)
	{
		mciSendString(TEXT("setaudio giftmusic volume to 1000"), NULL, 0, NULL);
		mciSendString(TEXT("play giftmusic from 800"), NULL, 0, NULL);
		ifGift = 0;
		len+=3;
		wall.change(head->x, head->y, SPACE);
		score += 100;
	}
	if (wall.getWhat(head->x, head->y) == POISON)
	{
		mciSendString(TEXT("play poisonmusic from 20"), NULL, 0, NULL);
		score -= 150;
		PoisonNote();//中毒
		wall.change(head->x, head->y, SPACE);
	}

	if (wall.getWhat(head->x, head->y) == WALL)
	{
		mciSendString(TEXT("play wallmusic from 20"), NULL, 0, NULL);
		ifDie = TRUE;
		life--;
		return;
	}

	//身体
	if (wall.getWhat(head->x, head->y) == BODY)
	{
		mciSendString(TEXT("play wallmusic from 20"), NULL, 0, NULL);
		ifDie = TRUE;
		life--;
		return;
	}

	//剩余身体的绘制
	p = head;
	while (p != NULL)
	{
		wall.change(p->x, p->y, BODY);
		p = p->next;
	}

}

void duiLie::initDuiLie()
{
	ifDie = false;
	lastDir = UP;
}
bool duiLie::randBorn()
{
	bool ifBorn = 0;
	int bornX[500] = { 0 };
	int sum = 0;

	for (int i = 0; i <= wall.COL; ++i)
	{
		for (int j = 1; j <= wall.ROW - 3; ++j)
		{
			if (wall.getWhat(i, j) == SPACE && wall.getWhat(i, j + 1) == SPACE && wall.getWhat(i, j + 2) == SPACE && wall.getWhat(i, j + 3) == SPACE)
			{
				ifBorn = 1;
				bornX[sum++] = i;
				break;
			}
		}
	}
	if (ifBorn)
	{
		ifDie = false;
		lastDir = UP;

		srand((unsigned int)time(NULL));
		int x = bornX[rand() % sum];
		int y = rand() % (wall.ROW - 3) + 1;
		while (1)
		{
			if (wall.getWhat(x, y) == SPACE && wall.getWhat(x, y + 1) == SPACE && wall.getWhat(x, y + 2) == SPACE && wall.getWhat(x, y + 3) == SPACE)
			{
				break;
			}
			y = rand() % (wall.ROW - 3) + 1;
		}
		len = 4;

		//
		head = new node;
		head->x = x;
		head->y = y;
		head->next = NULL;
		wall.change(head->x, head->y, BODY);
		node* now = NULL;
		node* last = head;
		for (int i = 1; i < 4; ++i)
		{
			wall.change(x, y + i, BODY);
			now = new node;
			now->x = x;
			now->y = y + i;
			last->next = now;
			last = now;

		}
		now->next = NULL;
		return 1;
	}
	else
		return 0;
}
bool duiLie::ISDEAD()
{
	return ifDie;
}
int duiLie::getScore()
{
	return score;
}
int duiLie::getLength()
{
	return len;
}

int duiLie::getLife()
{
	return life;
}

int duiLie::getHx()
{
	return head->x;
}

int duiLie::getHy()
{
	return head->y;
}

void duiLie::moveDuiLie(char Dir)
{
	if ((lastDir == UP && Dir == DOWN) || (lastDir == DOWN && Dir == UP) || (lastDir == LEFT && Dir == RIGHT) || (lastDir == RIGHT && Dir == LEFT))
	{
		Dir = lastDir;
	}
	switch (Dir)
	{
		case UP:
			move(0, -1);
			break;
		case DOWN:
			move(0, 1);
			break;
		case RIGHT:
			move(1, 0);
			break;
		case LEFT:
			move(-1, 0);
			break;
	}
	lastDir = Dir;
}

void duiLie::sleep()
{
	switch (Lv)
	{
		case 1:
			Sleep(60);
			break;
		case 2:
			Sleep(50);
			break;
		case 3:
			Sleep(3);
			break;
		case 4:
		{
			int s = 100 + sleepChange1 + sleepChange2;
			if (s < 3)
				s = 2;
			Sleep(s);
			break;
		}
	}
}

void duiLie::deleteDuiLie()
{
	node* p = head;
	node* k = NULL;
	while (p != NULL)
	{
		k = p;
		p = p->next;
		delete k;
	}
}

void duiLie::saveData()
{
	//open file
	fstream frec("rec.txt");
	if (!frec.is_open())
	{
		HWND hwnd = GetHWnd();//获取窗口句柄
		MessageBox(hwnd, L"Fail to open the Record File!", L"Error", MB_OK);//设置模态对话框
		return;
	}
	fstream fhis("his.txt");
	if (!fhis.is_open())
	{
		HWND hwnd = GetHWnd();
		MessageBox(hwnd, L"Fail to open the History File!", L"Error", MB_OK);
		return;
	}
	string name[6] = { " ","---","---","---" ,"---","---" };
	int userScore[6] = { 0 };
	for (int i = 0; i < 5; ++i)
	{
		frec >> name[i] >> userScore[i];
	}
	
	if (userScore[Lv] < score)
	{
		wchar_t USERNAME[10];
		InputBox(USERNAME, 10, L"恭喜你打破了本模式记录！\n请输入昵称", L"记录玩家昵称", L"Default");
		name[Lv] = ConvertWCharToString(USERNAME);
		userScore[Lv] = score;
		frec.clear();
		frec.seekp(0, ios::beg);
		for (int i = 1; i <= 5; ++i)
		{
			frec << name[i] << " " << userScore[i] << " ";
		}
		fhis.seekp(0, ios::end);
		fhis << " " << Lv << " " << name[Lv] << " " << score;
		
	}
	else {
		wchar_t USERNAME[10];
		InputBox(USERNAME, 10, L"很遗憾没有打破纪录，但是你也很厉害了！\n请输入昵称", L"起个名字", L"Default");
		//name[Lv] = USERNAME.str();
		name[Lv] = ConvertWCharToString(USERNAME);
		fhis.seekp(0, ios::end);
		fhis << " " << Lv << " " << name[Lv] << " " << score;
		//system("pause");
	}
	

	frec.close();
	fhis.close();

}

void duiLie::duiLieToWall()
{
	node* p = head->next;
	int x, y;
	while (p != NULL) {
		x = p->x;
		y = p->y;
		wall.change(x, y, WALL);
		wall.addWALL(x, y);
		p = p->next;
	}
}

void duiLie::duiLieToAnimal()
{
	node* p = head->next;
	int x, y;
	while (p != NULL)
	{
		x = p->x;
		y = p->y;
		animal.addAnimal(x, y);
		p = p->next;
	}
}

void duiLie::duiLieToSpace()
{
	node* p = head->next;
	int x, y;
	while (p != NULL)
	{
		x = p->x;
		y = p->y;
		wall.change(x, y, SPACE);
		p = p->next;
	}
}

void duiLie::Die()
{
	mciSendString(TEXT("play diemusic from 0"), NULL, 0, NULL);
	IMAGE over(WIDTH, HIGH);
	loadimage(&over, L"over.jpg", WIDTH, HIGH);//加载背景图片
	putimage(0, 0, &over);
	setbkmode(TRANSPARENT);
	settextstyle(30, 0, _T("幼圆"), 0, 0, 800, 0, 0, 0);
	settextcolor(HSLtoRGB(157, 0.20f, 0.26f));
	outtextxy(410, 500, _T("Press Any Key To Continue."));
}

void duiLie::reduceLife(int n)
{
	life -= n;
}

void duiLie::showDuiLie()
{
	node* p = head;
	while (p != NULL)
	{
		if (p == head)
		{
			IMAGE sn(13, 13);
			loadimage(&sn, _T("sn.png"), 13, 13);
			putimage(10 * p->x, 10 * p->y, &sn);
		}
		else {
			IMAGE pig(10, 10);
			loadimage(&pig, _T("pig.png"), 10, 10);
			putimage(10 * p->x, 10 * p->y, &pig);
		}
		p = p->next;
	}
}
