#pragma once
#include"Wall.h"
#include "enum.h"
#include<graphics.h>
#include"tools.h"
class Animal
{
public:
	Animal(Wall& tempWall) : wall(tempWall)
	{
		memset(cuteX, 0, sizeof(cuteX));
		memset(cuteY, 0, sizeof(cuteY));
		memset(isEat, 0, sizeof(isEat));
	};
	bool randAnimal();
	void addAnimal(int x, int y);
	void clearAnimal(int level);
	void writeEat(int x, int y);
	void showAnimal();
	COORD getAnimal();
	bool checkIfEat(COORD& a);
	int num;
protected:
	Wall& wall;
	int cuteX[50];
	int cuteY[50];
	int sum;
	int isEat[150][150];
};

COORD Animal::getAnimal()
{
	while (1)
	{
		int i = rand() % sum;
		if (wall.getWhat(cuteX[i], cuteY[i]) == ANIMAL && !isEat[cuteX[i]][cuteY[i]])
		{
			COORD a;
			a.X = cuteX[i];
			a.Y = cuteY[i];
			return a;
		}
	}
}

bool Animal::checkIfEat(COORD& a)
{
	if (isEat[a.X][a.Y])
		return 1;
	else
		return 0;
}



bool Animal::randAnimal()
{
	bool good = 0;
	bool break0 = 0;
	num = 0;
	for (int x = 1; x <= wall.COL; x++)
	{
		for (int y = 1; y <= wall.ROW; ++y)
		{
			if (wall.getWhat(x, y) == SPACE)
			{
				good = 1;
				num++;
			}
			if (num >= 5)
			{
				break0 = 1;
				break;
			}
		}
		if (break0)
			break;
	}
	if (!good)
		return 0;
	srand((unsigned int)time(NULL));
	int num2 = 0;
	int n = rand() % num + 1;
	num = n;
	for (int i = 0; i < n; ++i)
	{
		while (1)
		{
			int x = rand() % (wall.COL - 50) + 20;
			int y = rand() % (wall.ROW - 50) + 20;
			if (wall.getWhat(x, y) == SPACE)
			{
				wall.change(x, y, ANIMAL);
				isEat[x][y] = 0;
				cuteX[num2] = x;
				cuteY[num2] = y;
				num2++;
				break;
			}
		}
	}
	sum = num;
	return 1;

}


void Animal::addAnimal(int x, int y)
{
	cuteX[sum] = x;
	cuteY[sum] = y;
	wall.change(x, y, ANIMAL);
	isEat[x][y] = 0;
	num++;
	sum++;
}

void Animal::clearAnimal(int lev)
{

	for (int i = 0; i < sum; i++)
	{
		if (!isEat[cuteX[i]][cuteY[i]])
		{
			wall.change(cuteX[i], cuteY[i], SPACE);
			isEat[cuteX[i]][cuteY[i]] = 1;
		}
	}
	sum = 0;
	num = 0;
}

void Animal::writeEat(int x, int y)
{
	num--;
	isEat[x][y] = 1;
}

void Animal::showAnimal()
{
	IMAGE pig(10,10);
	loadimage(&pig, _T("pig.png"), 10, 10);
	for (int i = 0; i < sum; ++i)
	{
		if (!isEat[cuteX[i]][cuteY[i]])
		{
			putimage(10*cuteX[i], 10*cuteY[i], &pig);
		}
	}
}