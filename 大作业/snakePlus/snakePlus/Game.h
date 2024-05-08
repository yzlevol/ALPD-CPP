#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<time.h>
#include<iomanip>
#include<fstream>
#include<Windows.h>
#include"Wall.h"
#include "enum.h"

class Menu
{
private:
	string Level[6];
	int choseNum;
	int choseLevel;
	int sumHis;
	struct Record
	{
		string name;
		int score;
	}record[10];
	struct hisDate
	{
		int hisLv;
		string name;
		int hisScore;
		struct hisDate* next;
	}h[10];
	hisDate* head;
public:
	bool isChoose;
	bool isFinish;
	int choseLv();
	int search();
	int getScore(int Lv);
	void displayHistory();
	Menu(Wall& tempwall);
	Wall& wall;
};