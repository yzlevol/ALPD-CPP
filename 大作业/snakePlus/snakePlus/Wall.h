#pragma once
#include "enum.h"
#include<graphics.h>
#include<iostream>
#include <conio.h>
#include<cstring>
using namespace std;

class Wall
{
private:
	char map[150][150];
	int addWallNum;
	COORD addWall[100];
	clock_t startTIME;
public:
	enum
	{
		COL = 80,
		ROW = 60, 
	};
	Wall();
	void coutXY(int x, int y);
	void initMAP();
	void showWALL();
	void showUI(int len, int score, int lev, int life, int record);
	void change(int x, int y, char c);
	char getWhat(int x, int y);
	void addWALL(int x, int y);
	int getTime();
};


