#pragma once
#include "stdafx.h"

class Animal
{
private:
	int num;
	double chance;
	bool have;
	int points;
public:
	Animal();
	Animal(int num, double chance, bool have, int points);
	int setNum(int num);
	int getNum();
	int setChance(double chance);
	double getChance();
	int setHave(bool have);
	bool getHave();
	int setPoints(int points);
	int getPoints();
	~Animal();
};

