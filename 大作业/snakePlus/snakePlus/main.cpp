#include"Animal.h"
#include"DuiLie.h"
#include"Wall.h"
#include"Game.h"
#include "enum.h"
#include"tools.h"

using namespace std;

IMAGE img(1120, 620);
IMAGE red(30, 30);
IMAGE grey(30, 30);
int lastTime;

void loadPhoto(int n)
{
	switch (n)
	{
		case 1:
		{
			loadimage(&img, _T("1.png"), 1120, 620);
			//putimage(0, 0, &img);
			break;
		}
		case 2:
		{
			loadimage(&img, _T("2.png"), 1120, 620);
			break;
		}
		case 3:
		{
			loadimage(&img, _T("3.png"), 1120, 620);
			break;
		}
		case 4:
		{
			loadimage(&img, _T("4.png"), 1120, 620);
			break;
		}
	}
	// 设置绘图目标为 img 对象
	SetWorkingImage(&img);
}

void showPhoto()
{
	// 设置绘图目标为绘图窗口
	SetWorkingImage();
	// 将 img 对象显示在绘图窗口中
	putimage(0, 0, &img);
	SetWorkingImage(&img);
}

void rePhoto(int n)
{
	switch (n)
	{
		case 1:
		{
			loadimage(&img, _T("1.png"), 1120, 620);
			break;
		}
		case 2:
		{
			loadimage(&img, _T("2.png"), 1120, 620);

			break;
		}
		case 3:
		{
			loadimage(&img, _T("3.png"), 1120, 620);
			break;
		}
		case 4:
		{
			loadimage(&img, _T("4.png"), 1120, 620);
			break;
		}
	}

	putimage(0, 0, &img);
}

void showVB(Wall& wall)
{
	int time_now = wall.getTime();

	for (int i = 2; i < wall.COL; ++i)
	{
		for (int j = 2; j < wall.ROW; ++j)
		{
			if (wall.getWhat(i, j) == POISON)
			{
				
				IMAGE B(13, 13);
				loadimage(&B, _T("poison.png"), 13, 13);
				putimage(10 * i, 10 * j, &B);
			}

			if (wall.getWhat(i, j) == GIFT)
			{
				if (lastTime + 5 <= time_now) {
					wall.change(i, j, SPACE);
				}
				else {
					IMAGE V(13, 13);
					loadimage(&V, _T("gift.png"), 13, 13);
					putimage(10 * i, 10 * j, &V);
				}
			}

		}
	}
	lastTime = time_now;
}

void putVB(duiLie& s, Wall& w)
{
	int x = 0, y = 0, x2 = 0, y2 = 0;
	int sec = w.getTime();
	s.ifGift = 0;
	s.ifPoison = 0;
	if (sec % 15 == 0) {
		x = rand() % (w.COL - 10) + 5;
		y = rand() % (w.ROW - 10) + 5;
		if (w.getWhat(x, y) == SPACE)
		{
			w.change(x, y, GIFT);
		}
		s.ifGift = 1;
		return;
	}
	if (sec % 4 == 0)
	{
		x2 = rand() % (w.COL - 10) + 5;
		y2 = rand() % (w.ROW - 10) + 5;
		if (w.getWhat(x2, y2) == SPACE)
		{
			w.change(x2, y2, POISON);
		}
		s.ifPoison = 1;
		return;
	}

}

void showALL(duiLie& s, Wall& w, Animal& f, Menu& m)
{

	rePhoto(s.Lv);
	s.showDuiLie();
	w.showWALL();
	w.showUI(s.getLength(), s.getScore(), m.getScore(s.Lv), s.Lv, s.getLife());
	f.showAnimal();
	showVB(w);
	showPhoto();
}

void easyPlay()
{
	system("cls");
	loadPhoto(1);
	Wall wall;
	wall.initMAP();
	wall.showWALL();
	Animal animal(wall);
	animal.randAnimal();
	duiLie duiLie(wall, animal);
	duiLie.Lv = 1;
	duiLie.randBorn();
	Menu menu(wall);

	char dir = NULL, d = NULL;
	bool CHOSEEND = 0;

	while (!duiLie.ISDEAD())
	{
		showALL(duiLie, wall, animal, menu);
		dir = _getch();
		if (dir == UP || dir == DOWN || dir == LEFT || dir == RIGHT)
		{
			mciSendString(TEXT("play turnmusic from 0"), NULL, 0, NULL);
			d = dir;
		}
		else {
			if (dir == IFPAUSE)
			{
				HWND hwnd = GetHWnd();//获取窗口句柄
				int result = MessageBox(hwnd, L"是否继续？", L"PAUSE", MB_OKCANCEL);//设置模态对话框
				if (result == IDOK)
				{
					MessageBox(hwnd, L"你选择了继续.\n2秒后游戏继续.", L"继续", MB_OK);
					Sleep(3000);
				}
				else {
					MessageBox(hwnd, L"你选择了结束.\n", L"结束", MB_OK);
					CHOSEEND = 1;
					break;
				}
			}
		}
		do
		{
			duiLie.moveDuiLie(d);
			duiLie.sleep();
			if (animal.num == 0)
				animal.randAnimal();
			showALL(duiLie, wall, animal, menu);
		} while (!_kbhit() && !duiLie.ISDEAD());
	}

	if (duiLie.ISDEAD() || CHOSEEND)
	{
		duiLie.Die();
		showPhoto();
		_getch();
		closegraph();
		duiLie.deleteDuiLie();
		duiLie.saveData();
	}
}

void hardPlay()
{
	system("cls");
	loadPhoto(2);

	Wall wall;
	wall.initMAP();
	wall.showWALL();

	Animal animal(wall);
	animal.randAnimal();

	duiLie duiLie(wall, animal);
	duiLie.Lv = 2;
	duiLie.randBorn();

	Menu menu(wall);
	char dir = NULL, d = NULL;
	bool CHOSEEND = 0;
	bool isGameOver = 0;
	while (!isGameOver)
	{
		showALL(duiLie, wall, animal, menu);
		dir = _getch();
		if (dir == UP || dir == DOWN || dir == LEFT || dir == RIGHT)
		{
			mciSendString(TEXT("play turnmusic from 0"), NULL, 0, NULL);
			d = dir;
		}
		else {
			if (dir == IFPAUSE)
			{
				HWND hwnd = GetHWnd();//获取窗口句柄
				int result = MessageBox(hwnd, L"是否继续？", L"PAUSE", MB_OKCANCEL);//设置模态对话框
				if (result == IDOK)
				{
					MessageBox(hwnd, L"你选择了继续.\n2秒后游戏继续.", L"继续", MB_OK);
					Sleep(3000);
				}
				else {
					MessageBox(hwnd, L"你选择了结束.\n", L"结束", MB_OK);
					CHOSEEND = 1;
					break;
				}
			}
		}
		do
		{
			duiLie.moveDuiLie(d);
			duiLie.sleep();
			if (animal.num == 0)
			{
				animal.randAnimal();
			}
			showALL(duiLie, wall, animal, menu);
			showPhoto();
		} while (!_kbhit() && !duiLie.ISDEAD());

		if (duiLie.ISDEAD())
		{
			duiLie.duiLieToWall();
			animal.clearAnimal(duiLie.Lv);
			if (!animal.randAnimal())
				isGameOver = 1;

			duiLie.deleteDuiLie();
			duiLie.initDuiLie();
			if (!duiLie.randBorn())
				isGameOver = 1;
		}
	}
	duiLie.Die();
	showPhoto();
	_getch();
	closegraph();
	duiLie.saveData();
}

void veryHardPlay()
{
	system("cls");
	loadPhoto(3);

	Wall wall;
	wall.initMAP();
	wall.showWALL();

	Animal animal(wall);
	animal.randAnimal();

	duiLie duiLie(wall, animal);
	duiLie.Lv = 3;
	duiLie.randBorn();

	Menu menu(wall);
	wall.showUI(duiLie.getLength(), duiLie.getScore(), menu.getScore(duiLie.Lv), duiLie.Lv, duiLie.getLife());
	char dir = NULL, d = NULL;
	bool isGameOver = 0;
	bool CHOSEEND = 0;
	while (!isGameOver && duiLie.getLife())
	{
		showALL(duiLie, wall, animal, menu);
		dir = _getch();
		if (dir == UP || dir == DOWN || dir == LEFT || dir == RIGHT)
		{
			mciSendString(TEXT("play turnmusic from 0"), NULL, 0, NULL);
			d = dir;
		}
		else {
			if (dir == IFPAUSE)
			{
				HWND hwnd = GetHWnd();//获取窗口句柄
				int result = MessageBox(hwnd, L"是否继续？", L"PAUSE", MB_OKCANCEL);//设置模态对话框
				if (result == IDOK)
				{
					MessageBox(hwnd, L"你选择了继续.\n2秒后游戏继续.", L"继续", MB_OK);
					Sleep(3000);
				}
				else {
					MessageBox(hwnd, L"你选择了结束.\n", L"结束", MB_OK);
					CHOSEEND = 1;
					break;
				}
			}
		}
		do
		{
			duiLie.moveDuiLie(d);
			duiLie.sleep();
			if (animal.num == 0)
			{
				animal.randAnimal();
			}
			showALL(duiLie, wall, animal, menu);
		} while (!_kbhit() && !duiLie.ISDEAD());

		if (duiLie.ISDEAD())
		{
			animal.clearAnimal(duiLie.Lv);
			if (!animal.randAnimal())
				isGameOver = 1;
			duiLie.duiLieToAnimal();
			duiLie.deleteDuiLie();
			duiLie.initDuiLie();
			if (!duiLie.randBorn())
				isGameOver = 1;
		}
	}
	duiLie.Die();
	showPhoto();
	_getch();
	closegraph();
	duiLie.saveData();
}

void funPlay(int n)
{
	mciSendString(L"close bkmusic", NULL, 0, NULL);
	mciSendString(L"play funmusic repeat", NULL, 0, NULL);
	system("cls");
	loadPhoto(4);

	Wall wall;
	wall.initMAP();
	wall.showWALL();

	Animal animal(wall);
	animal.randAnimal();

	duiLie duiLie(wall, animal);
	duiLie.Lv = n;
	duiLie.randBorn();

	Menu menu(wall);
	char dir = NULL, d = NULL;
	bool CHOSEEND = 0;
	while (!duiLie.ISDEAD())
	{
		if (wall.getTime() >= 10) {
			CHOSEEND = 1;
			goto T2;
		}
		else {
			showALL(duiLie, wall, animal, menu);
			dir = _getch();
			if (dir == UP || dir == DOWN || dir == LEFT || dir == RIGHT)
			{
				mciSendString(TEXT("play turnmusic from 0"), NULL, 0, NULL);
				d = dir;
			}
			else {
				if (dir == IFPAUSE)
				{
					HWND hwnd = GetHWnd();//获取窗口句柄
					int result = MessageBox(hwnd, L"是否继续？", L"PAUSE", MB_OKCANCEL);//设置模态对话框
					if (result == IDOK)
					{
						MessageBox(hwnd, L"你选择了继续.\n2秒后游戏继续.", L"继续", MB_OK);
						Sleep(3000);
					}
					else {
						MessageBox(hwnd, L"你选择了结束.\n", L"结束", MB_OK);
						CHOSEEND = 1;
						//break;
						goto T2;
					}
				}
			}
			do
			{
				duiLie.moveDuiLie(d);
				duiLie.sleep();
				putVB(duiLie, wall);
				if (animal.num <= 3)
				{
					animal.randAnimal();
				}
				showALL(duiLie, wall, animal, menu);
			} while (!_kbhit() && !duiLie.ISDEAD());
		}
		T2:if (duiLie.ISDEAD() || CHOSEEND)
		{
			duiLie.Die();
			showPhoto();
			HWND hwnd = GetHWnd();//获取窗口句柄
			wchar_t message[100];
			swprintf_s(message, L" 游戏结束！\n 你的成绩为 %d 分", duiLie.getScore());
			MessageBox(hwnd, message, L"GameOver", MB_OK);
			_getch();
			closegraph();
			duiLie.deleteDuiLie();
			duiLie.saveData();
			break;
		}

	}
	mciSendString(L"close funmusic", NULL, 0, NULL);
	mciSendString(L"play bkmusic repeat", NULL, 0, NULL);
}

void play(int Lv)
{
	initgraph(1120, 620);
	switch (Lv)
	{
		case 1:
		{
			easyPlay();
			break;
		}
		case 2:
		{
			hardPlay();
			break;
		}
		case 3:
		{
			veryHardPlay();
			break;
		}
		case 4:
		{
			funPlay(4);
			break;
		}
	}
	closegraph();
}



int main()
{
	loadimage(&red, L"red.png", 30, 30);
	loadimage(&grey, L"grey.png", 30, 30);
	ofstream orec("rec.txt", ios::app);
	if (!orec.is_open())
	{
		cout << "record文件创建失败!";
		return -1;
	}
	ofstream ohis("his.txt", ios::app);
	if (!ohis.is_open())
	{
		cout << "history文件创建失败!";
		return -1;
	}

	orec.close();
	ohis.close();


	Wall wall;
	Menu menu(wall);
	int Lv = 1;
	
	while (TRUE)
	{
		startUI();
		homeMenu();
		homeChose();
		switch (STATUS)
		{
			case 1:
			{
				Lv = startLV();
				play(Lv);
				break;
			}
			case 2:
			{
				showTIPS();
				_getch();
				homeChose();
				break;
			}
			case 3:
			{
				menu.displayHistory();
				//_getch();
				homeChose();
				break;
			}
			case 4:
			{
				exit(1);
				break;
			}
		}
			

	}
	return 0;
}