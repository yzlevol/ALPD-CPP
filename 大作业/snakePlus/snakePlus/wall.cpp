#include"Wall.h"

Wall::Wall()
{
	startTIME = clock();
	addWallNum = 0;
	memset(addWall, 0, sizeof(addWall));
}
void Wall::coutXY(int x, int y)
{
	HANDLE outsys = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO cursor;         
	cursor.dwSize = 10;
	cursor.bVisible = 0;                 
	SetConsoleCursorInfo(outsys, &cursor);
	COORD pos;
	pos.X = x; 
	pos.Y = y;
	SetConsoleCursorPosition(outsys, pos);
}

void Wall::initMAP()
{
	for (int i = 0; i <= COL + 1; i++)
	{
		map[i][ROW + 1] = WALL;
		map[i][0] = WALL;
	}
	for (int i = 0; i <= ROW + 1; i++)
	{
		map[0][i] = WALL;
		map[COL + 1][i] = WALL;
	}

	for (int i = 1; i <= COL + 1; ++i)
	{
		map[i][1] = WALL;
		map[i][ROW] = WALL;
	}

	for (int i = 1; i <= ROW; ++i)
	{
		map[1][i] = WALL;
	}

	for (int i = 2; i <= COL; ++i)
	{
		for (int j = 2; j < ROW; ++j)
		{
			map[i][j] = SPACE;
		}
	}


}
void Wall::showWALL()
{
	IMAGE img_wall(20, 20);
	loadimage(&img_wall,L"wall.png", 20, 20);
	for (int i = 0; i < 820 / 20; ++i)
	{
		putimage(i * 20 + 1, 0, &img_wall);
		putimage(i * 20 + 1, 600, &img_wall);
	}
	for (int j = 0; j < 620 / 20; ++j)
	{
		putimage(0, 20 * j + 1, &img_wall);
		putimage(810, 20 * j + 1, &img_wall);
	}

	int n = addWallNum;
	IMAGE wall2(13, 13);
	loadimage(&wall2, L"wall2.png", 13, 13);
	while (n)
	{
		putimage(10 * addWall[n].X, 10 * addWall[n].Y, &wall2);
		n--;
	}

}
void Wall::change(int x, int y, char ch)
{
	map[x][y] = ch;
}
char Wall::getWhat(int x, int y)
{
	return map[x][y];
}

void Wall::showUI(int len, int score, int record, int lev, int life = 0)
{
	IMAGE head_img(100, 100);
	loadimage(&head_img, L"head-img.png", 100, 100);
	putimage(860, 50, &head_img);
	//transparentimage3(NULL, 220, 100, &head_img);

	setbkmode(TRANSPARENT);
	settextstyle(25, 0, _T("Gill Sans Ultra Bold"), 0, 0, 800, 0, 0, 0);
	settextcolor(HSLtoRGB(0, 0.43f, 0.48f));

	TCHAR str1[15];
	outtextxy(850, 170, _T("Numbers："));
	_stprintf_s(str1, _T("%d"), len);
	outtextxy(950, 195, str1);
	TCHAR str2[10];
	outtextxy(850, 240, _T("Scores ："));
	_stprintf_s(str2, _T("%d"), score);
	outtextxy(950, 265, str2);
	TCHAR str3[15];
	outtextxy(850, 300, _T("History Record："));
	int hisrec;
	if (score < record)
		hisrec = record;
	else
		hisrec = score;
	_stprintf_s(str3, _T("%d"), hisrec);
	outtextxy(950, 325, str3);

	int time = (int)(clock() - startTIME) / 1000;
	TCHAR t[10];
	_stprintf_s(t, _T("%d"), time);
	if (lev != 4)
	{
		outtextxy(850, 360, _T("游戏时间："));
		outtextxy(950, 385, t);
		outtextxy(990, 385, L"sec");
	}

	switch (lev)
	{
		case 1:
			break;
		case 2:
			break;
		case 3:
		{
			
			TCHAR lives[10];
			_stprintf_s(lives, _T("%d"), life);
			outtextxy(850, 410, _T("血量："));
			outtextxy(950, 410, lives);
			
			IMAGE red(30, 30);
			IMAGE grey(30, 30);
			loadimage(&red, L"red.png", 30, 30);
			loadimage(&grey, L"grey.png", 30, 30);

			for (int i = 0; i < life; ++i)
			{
				putimage(850 + 30 * i, 440, &red);
			}
			for (int j = life; j < 5; ++j)
			{
				putimage(850 + 30 * j, 440, &grey);
			}
			break;
		}
		case 4:
		{
			outtextxy(850, 360, _T("剩余时间："));
			setbkmode(TRANSPARENT);
			settextstyle(40, 0, _T("Gill Sans Ultra Bold"), 0, 0, 800, 0, 0, 0);

			settextcolor(HSLtoRGB((float)(time/100.0*360), 0.70f, 0.50f));
			

			_stprintf_s(t, _T("%d"), 100-time);
			outtextxy(900, 385, t);
			settextstyle(30, 0, _T("consolas"), 0, 0, 800, 0, 0, 0);

			outtextxy(990, 385, L"sec");

			setbkmode(TRANSPARENT);
			settextstyle(25, 0, _T("幼圆"), 0, 0, 800, 0, 0, 0);
			settextcolor(HSLtoRGB(157, 0.20f, 0.26f));

			break;
		}
	}

}
void Wall::addWALL(int x, int y)
{
	addWallNum++;
	addWall[addWallNum].X = x;
	addWall[addWallNum].Y = y;
}

int Wall::getTime()
{
	int sec = 0;
	sec = (int)(clock() - startTIME) / 1000;
	return sec;
}

