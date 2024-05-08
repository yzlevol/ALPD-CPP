#include "Game.h"
#include "enum.h"
#include<graphics.h>
#include <locale>
#include<sstream>
#include <codecvt>

int Menu::getScore(int Lv)
{
	return record[Lv].score;
}

std::wstring intToWString(int value) {
	std::wstringstream ss;
	ss << value;
	return ss.str();
}

int Menu::search()
{
	int times = 1;
	HWND hwnd = GetHWnd();
	wchar_t USERNAME[10];
	InputBox(USERNAME, 10, L"请输入要搜索的用户名\n", L"搜索", L"Default");
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	std::string fname = converter.to_bytes(USERNAME);
	hisDate* p = head->next;
	T1:while (p != NULL && p->name != fname)
	{
		times++;
		p = p->next;
	}
		if (p != NULL)
		{
			std::wstring message;
			std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

			message = L"找到了！\nVersion :  " + converter.from_bytes(Level[p->hisLv]) + L"\nUserName :  " + converter.from_bytes(p->name) + L"\nScore :  " + std::to_wstring(p->hisScore) + L"\n是否为该玩家？是则点击确认，否则取消";
			
			int chose = MessageBoxW(hwnd, message.c_str(), L"Result", MB_OKCANCEL);

			if (chose == IDOK)
			{
				return times;
			}
			else
			{
				p = p->next;
				goto T1;
			}
		}
		else
		{
			MessageBox(hwnd, L"没找到！\n", L"Result", MB_OK);
			return 0;
		}
}


Menu::Menu(Wall& tempwall) :wall(tempwall)
{
	CONSOLE_CURSOR_INFO cursor;    
	cursor.dwSize = 10;

	HANDLE outsys = GetStdHandle(STD_OUTPUT_HANDLE);
	cursor.bVisible = 0;                
	SetConsoleCursorInfo(outsys, &cursor);
	choseNum = 1;
	isFinish = 0;
	isChoose = 0;
	choseLevel = 1;
	sumHis = 0;
	head = NULL;
	Level[1] = "Beginner edition";
	Level[2] = "Advanced edition";
	Level[3] = "Premium  edition";
	Level[4] = "Limited edition";
}
