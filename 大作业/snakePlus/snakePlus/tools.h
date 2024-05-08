#pragma once
#include<graphics.h>
#include <conio.h>
#include"Game.h"
#include <codecvt>
#include<string>
#include <random>
#include <Windows.h> 
#pragma comment( lib, "MSIMG32.LIB")
#include<mmsystem.h>

#pragma comment(lib,"winmm.lib")


#define WIDTH 1200//UNIT*600
#define HIGH 660//UNIT*33
#define UNIT 20
IMAGE img_bk;//设置背景图片
IMAGE img_frame, img_pause, img_manual, img_bkimg_rank, img_head;
IMAGE head_up, head_down, head_right, head_left;
IMAGE pig;

int STATUS = 0;
int choseLV = 0;


/*LPCTSTR与String互转*/
LPCTSTR StringToLPCTSTR(const std::string& str) {
	std::wstring wstr(str.begin(), str.end());
	int bufferLength = (int)(wstr.length()) + 1;
	LPWSTR buffer = new wchar_t[bufferLength];
	wcscpy_s(buffer, bufferLength, wstr.c_str());
	LPCTSTR lpctstr = buffer;

	return lpctstr;
}

std::string ConvertWCharToString(const wchar_t* wstr)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	std::wstring wstring(wstr);

	return converter.to_bytes(wstring);
}


void startUI()
{
	srand(GetTickCount());//生成随机种子
	mciSendString(L"open happy1.mp3 alias bkmusic", NULL, 0, NULL);
	mciSendString(L"play bkmusic repeat", NULL, 0, NULL);
	mciSendString(L"open eat.mp3 alias eatmusic", NULL, 0, NULL);
	mciSendString(L"open gift.mp3 alias giftmusic", NULL, 0, NULL);
	mciSendString(L"open poison.mp3 alias poisonmusic", NULL, 0, NULL);
	mciSendString(L"open poison2.mp3 alias poison2music", NULL, 0, NULL);
	mciSendString(L"open wall.mp3 alias wallmusic", NULL, 0, NULL);
	mciSendString(L"open die.mp3 alias diemusic", NULL, 0, NULL);
	mciSendString(L"open wall.mp3 alias wallmusic", NULL, 0, NULL);
	mciSendString(L"open turn.mp3 alias turnmusic", NULL, 0, NULL);
	mciSendString(L"open fun.mp3 alias funmusic", NULL, 0, NULL);
	mciSendString(L"open click.mp3 alias clickmusic", NULL, 0, NULL);
	mciSendString(L"open fuhuo.mp3 alias fuhuomusic", NULL, 0, NULL);
	initgraph(WIDTH, HIGH);

	HWND hwnd = GetHWnd();
	SetWindowText(hwnd, L"Piggy v1.0");
	loadimage(&img_bk, L"bk1.png", WIDTH, HIGH);
	loadimage(&img_frame, L"wall2.png", UNIT, UNIT);
	loadimage(&img_pause, L"bk2.png", WIDTH, HIGH);
	loadimage(&img_manual, L"manual.png", WIDTH, HIGH);
	loadimage(&img_bkimg_rank, L"bk2.png", WIDTH, HIGH);
	loadimage(&head_up, L"head_up.png", UNIT, UNIT);
	loadimage(&head_down, L"head_down.png", UNIT, UNIT);
	loadimage(&head_right, L"head_right.png", UNIT, UNIT);
	loadimage(&head_left, L"head_left.png", UNIT, UNIT);

	loadimage(&pig, L"pig.png", UNIT, UNIT);
	

}

void homeMenu()
{

	putimage(0, 0, &img_bk);
	setbkmode(TRANSPARENT);
	//settextstyle(80, 0, _T("幼圆"));
	settextstyle(30, 0, _T("幼圆"), 0, 0, 800, 0, 0, 0);
	settextcolor(HSLtoRGB(157, 0.20f, 0.26f));
	//
	LOGFONT f;//字体变量
	gettextstyle(&f);
	f.lfQuality = ANTIALIASED_QUALITY;

	setfillcolor(HSLtoRGB(147, 0.50f, 0.47f));
	fillrectangle(WIDTH / 2 - 120, HIGH / 2 - 60, WIDTH / 2 + 60, HIGH / 2 - 30);
	setfillcolor(HSLtoRGB(147, 0.50f, 0.47f));
	fillrectangle(WIDTH / 2 - 120, HIGH / 2 - 15, WIDTH / 2 + 60, HIGH / 2 + 15);
	setfillcolor(HSLtoRGB(147, 0.50f, 0.47f));
	fillrectangle(WIDTH / 2 - 120, HIGH / 2 + 30, WIDTH / 2 + 60, HIGH / 2 + 60);
	setfillcolor(HSLtoRGB(147, 0.50f, 0.47f));
	fillrectangle(WIDTH / 2 - 120, HIGH / 2 + 75, WIDTH / 2 + 60, HIGH / 2 + 105);
	settextstyle(&f);

	outtextxy(WIDTH / 2 - 140, HIGH / 6, _T("-*- Lovely Piggy -*-"));
	outtextxy(WIDTH / 2 - 120, HIGH / 2 - 60, _T("1：开始游戏"));
	outtextxy(WIDTH / 2 - 120, HIGH / 2 - 15, _T("2：游戏说明"));
	outtextxy(WIDTH / 2 - 120, HIGH / 2 + 30, _T("3：排行榜"));
	outtextxy(WIDTH / 2 - 120, HIGH / 2 + 75, _T("4：退出游戏"));
	outtextxy(WIDTH / 2 - 200, HIGH / 2 + 125, L"鼠标左键单击选择，稍后进入");
}

void showStartLv()
{
	IMAGE img_bk3(WIDTH, HIGH);
	loadimage(&img_bk3, L"Lv.jpg", WIDTH, HIGH);
	putimage(0, 0, &img_bk3);

	setbkmode(TRANSPARENT);
	//settextstyle(80, 0, _T("幼圆"));
	settextstyle(30, 0, _T("幼圆"), 0, 0, 800, 0, 0, 0);
	settextcolor(HSLtoRGB(157, 0.20f, 0.26f));
	//
	LOGFONT f;//字体变量
	gettextstyle(&f);
	f.lfQuality = ANTIALIASED_QUALITY;

	setfillcolor(HSLtoRGB(147, 0.50f, 0.47f));
	fillrectangle(WIDTH / 2 - 120, HIGH / 2 - 60, WIDTH / 2 + 60, HIGH / 2 - 30);
	setfillcolor(HSLtoRGB(147, 0.50f, 0.47f));
	fillrectangle(WIDTH / 2 - 120, HIGH / 2 - 15, WIDTH / 2 + 60, HIGH / 2 + 15);
	setfillcolor(HSLtoRGB(147, 0.50f, 0.47f));
	fillrectangle(WIDTH / 2 - 120, HIGH / 2 + 30, WIDTH / 2 + 60, HIGH / 2 + 60);
	setfillcolor(HSLtoRGB(147, 0.50f, 0.47f));
	fillrectangle(WIDTH / 2 - 120, HIGH / 2 + 75, WIDTH / 2 + 60, HIGH / 2 + 105);
	settextstyle(&f);

	outtextxy(WIDTH / 2 - 140, HIGH / 6, _T("-*-游戏模式选择-*-"));
	outtextxy(WIDTH / 2 - 120, HIGH / 2 - 60, _T("1：入门版本"));
	outtextxy(WIDTH / 2 - 120, HIGH / 2 - 15, _T("2：进阶版本"));
	outtextxy(WIDTH / 2 - 120, HIGH / 2 + 30, _T("3：高级版本"));
	outtextxy(WIDTH / 2 - 120, HIGH / 2 + 75, _T("4：最终版本"));
	outtextxy(WIDTH / 2 - 300, HIGH / 2 + 125, L"鼠标左键单击选择");
}

void showTIPS()
{
	IMAGE img_bk3(WIDTH, HIGH);
	loadimage(&img_bk3, L"introduce.png", WIDTH, HIGH);
	putimage(0, 0, &img_bk3);

}

void Menu::displayHistory()
{
	IMAGE img_bk3(WIDTH, HIGH);
	loadimage(&img_bk3, L"rank.png", WIDTH, HIGH);//加载背景图片
	putimage(0, 0, &img_bk3);

	setbkmode(TRANSPARENT);
	//settextstyle(80, 0, _T("幼圆"));
	settextstyle(20, 0, _T("幼圆"), 0, 0, 800, 0, 0, 0);
	settextcolor(HSLtoRGB(157, 0.20f, 0.26f));
	//
	LOGFONT f;//字体变量
	gettextstyle(&f);
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);

	fstream fhistory("his.txt");
	if (!fhistory.is_open())
	{
		HWND hwnd = GetHWnd();
		MessageBox(hwnd, L"Fail to open the History File!", L"Error", MB_OK);
		return;
	}

	head = new hisDate;
	hisDate* p = head, * q = NULL;
	sumHis = 0;
	while (fhistory.peek() != EOF)
	{
		q = new hisDate;
		p->next = q;
		p = q;
		fhistory >> p->hisLv >> p->name >> p->hisScore;
		sumHis++;
	}
	p->next = NULL;
	fhistory.close();

	{
		hisDate* p = head->next, * q = NULL;
		int n = 1;
		settextstyle(30, 0, _T("幼圆"), 0, 0, 800, 0, 0, 0);
		outtextxy(WIDTH / 3+30, 20, L"游戏玩家排行榜");
		settextstyle(20, 0, _T("幼圆"), 0, 0, 800, 0, 0, 0);
		while (p != NULL)
		{
			if (n<=30)
			{
				outtextxy(WIDTH / 20, 60+20*n, StringToLPCTSTR("Version: " + Level[p->hisLv]));
				outtextxy(WIDTH / 3, 60+20*n, StringToLPCTSTR("UserName: " + p->name));
				outtextxy(WIDTH / 2+200, 60+20*n, StringToLPCTSTR("Score: " + to_string(p->hisScore)));
				outtextxy(WIDTH / 2 + 340, 60 + 20 * n, L"分");
			}
			p = p->next;
			n++;
		}
		outtextxy(WIDTH / 2 - 300, HIGH / 2 + 220, L"Press F/f Key To Search.");
		outtextxy(WIDTH / 2 - 300, HIGH / 2 + 250, L"Press ESC Key To Continue.");

		while (true) {
			string nameTosearch;
			int ch = _getch();
			if (ch == 70 || ch == 102) {  // 检查"F"键
				int times = search();
				cout << times;
				if (times) {
					wchar_t inputs0[10];
					InputBox(inputs0, 10, L"输入“delete/Delete/Del/del删除本用户”\n", L"删除", L"Del");
					std::wstring inputs(inputs0);
					if (inputs == L"delete"|| inputs == L"Delete" || inputs == L"del" || inputs == L"Del")
					{
						hisDate* p = head->next, * last = head;
						for (int i = 0; i < times-1; ++i)
						{
							last = p;
							p = p->next;
						}
						last->next = p->next;
						delete p;
						sumHis--;


						// 清空文件内容
						std::ofstream file2("his.txt", std::ios::out | std::ios::trunc);
						file2.clear();
						file2.close();

						// 重新写入文件
						std::ofstream file("his.txt", std::ios::out | std::ios::app);
						hisDate* currentNode = head->next;
						while (currentNode != nullptr) {
							file << currentNode->hisLv << " " << currentNode->name << " " << currentNode->hisScore;
							if (currentNode->next != nullptr) {
								file << " ";
							}
							currentNode = currentNode->next;
						}
						currentNode = NULL;
						file.close();


						HWND hwnd = GetHWnd();
						MessageBox(hwnd, L"已删除", L"Delete", MB_OK);
						displayHistory();
					}
				}
			}

			if (ch == 27) {  // 检查"ESC"
				return;
			}
		}

	}

}

void homeChose()
{
	mciSendString(L"open click.mp3 alias clickmusic", NULL, 0, NULL);
	ExMessage m;		
	int condition = 1;
	while (condition == 1)
	{
		// 获取一条鼠标或按键消息
		m = getmessage(EX_MOUSE | EX_KEY);

		switch (m.message)
		{
			case WM_MOUSEMOVE:
				break;
			case WM_LBUTTONDOWN:
				if (m.ctrl) {
				}
				else {
					if (m.x >= WIDTH / 2 - 120 && m.x <= WIDTH / 2 + 60)
					{
						if (m.y >= HIGH / 2 - 60 && m.y <= HIGH / 2 - 30)
						{
							
							homeMenu();
							outtextxy(WIDTH / 2 - 150, HIGH / 2 - 60, L"=>");
							mciSendString(TEXT("play clickmusic from 0"), NULL, 0, NULL);
							STATUS = 1;
							Sleep(500);
							return;
						}
						if (m.y >= HIGH / 2 - 15 && m.y <= HIGH / 2 + 15)
						{
							homeMenu();
							outtextxy(WIDTH / 2 - 150, HIGH / 2 - 15, L"=>");
							mciSendString(TEXT("play clickmusic from 0"), NULL, 0, NULL);
							STATUS = 2;
							Sleep(500);
							return;
						}
						if (m.y >= HIGH / 2 + 30 && m.y <= HIGH / 2 + 60)
						{
							homeMenu();
							outtextxy(WIDTH / 2 - 150, HIGH / 2 + 30, L"=>");
							mciSendString(TEXT("play clickmusic from 0"), NULL, 0, NULL);
							STATUS = 3;
							Sleep(500);
							return;
						}
						if (m.y >= HIGH / 2 + 75 && m.y <= HIGH / 2 + 175)
						{
							homeMenu();
							outtextxy(WIDTH / 2 - 150, HIGH / 2 + 75, L"=>");
							mciSendString(TEXT("play clickmusic from 0"), NULL, 0, NULL);
							STATUS = 4;
							Sleep(500);
							return;
						}
					}
				}
				break;
			case WM_KEYDOWN:
				if (m.vkcode == VK_ESCAPE)
					return;	// 按 ESC 键退出程序
		}
	}
}

int startLV()
{
	mciSendString(L"open click.mp3 alias clickmusic", NULL, 0, NULL);
	choseLV = 0;
	ExMessage m;		// 定义消息变量
	int condition = 1;
	showStartLv();
	while (condition == 1)
	{
		// 获取一条鼠标或按键消息
		m = getmessage(EX_MOUSE | EX_KEY);

		switch (m.message)
		{
			case WM_MOUSEMOVE:
				break;
			case WM_LBUTTONDOWN:
				if (m.ctrl) {
				}
				else {
					if (m.x >= WIDTH / 2 - 120 && m.x <= WIDTH / 2 + 60)
					{
						if (m.y >= HIGH / 2 - 60 && m.y <= HIGH / 2 - 30)
						{
							showStartLv();
							outtextxy(WIDTH / 2 - 150, HIGH / 2 - 60, L"=>");
							mciSendString(TEXT("play clickmusic from 0"), NULL, 0, NULL);
							Sleep(400);
							choseLV = 1;
							return choseLV;
						}
						if (m.y >= HIGH / 2 - 15 && m.y <= HIGH / 2 + 15)
						{
							showStartLv();
							outtextxy(WIDTH / 2 - 150, HIGH / 2 - 15, L"=>");
							mciSendString(TEXT("play clickmusic from 0"), NULL, 0, NULL);
							Sleep(400);
							choseLV = 2;
							return choseLV;
						}
						if (m.y >= HIGH / 2 + 30 && m.y <= HIGH / 2 + 60)
						{
							showStartLv();
							outtextxy(WIDTH / 2 - 150, HIGH / 2 + 30, L"=>");
							mciSendString(TEXT("play clickmusic from 0"), NULL, 0, NULL);
							Sleep(400);
							choseLV = 3;
							return choseLV;
						}
						if (m.y >= HIGH / 2 + 75 && m.y <= HIGH / 2 + 175)
						{
							showStartLv();
							outtextxy(WIDTH / 2 - 150, HIGH / 2 + 75, L"=>");
							mciSendString(TEXT("play clickmusic from 0"), NULL, 0, NULL);
							Sleep(400);
							choseLV = 4;
							return choseLV;
						}
					}
				}
				break;
			case WM_KEYDOWN:
				if (m.vkcode == VK_ESCAPE)
					return choseLV;	
		}
	}
	return choseLV;
}

long long RandomNumber() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(0, 9);

	long long number = 0;
	for (int i = 0; i < 8; ++i) {
		number = number * 10 + dist(gen);
	}
	return number;
}

int checkInput(long long number) {
	long long input = 0;
	for (int i = 0; i < 8; ++i) {
		char ch = _getch();
		if (ch >= '0' && ch <= '9') {
			input = input * 10 + (ch - '0');
		}
		else {
			i--;  
		}
	}
	if (input == number) {
		return 1;
	}
	else {
		return 0;
	}
}

void PoisonNote()
{
	long long number = RandomNumber();
	HWND hwnd = GetHWnd();
	wchar_t message[100];
	swprintf_s(message, L"中毒了!\n按照顺序敲击8位数字串解毒！\n%I64d", number);
	MessageBox(hwnd, message, L"中毒", MB_OK);
	
	if (checkInput(number)) {
		mciSendString(TEXT("play fuhuomusic from 20"), NULL, 0, NULL);
		return;  
	}
	else {
		mciSendString(TEXT("play poison2music from 0"), NULL, 0, NULL);
		MessageBox(hwnd, L"解毒失败，暂停两秒！", L"中毒", MB_OK);
		Sleep(2000);
	}
	Sleep(1000);
}