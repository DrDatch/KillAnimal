#include "stdafx.h"
#include "Animal.h"


Animal::Animal(int num, double chance, bool have, int points)
{
	Animal::num = num;
	Animal::chance = chance;
	Animal::have = have;
	Animal::points = points;
}

Animal::Animal()
{
	Animal::num = 0;
	Animal::chance = 0;
	Animal::have = 0;
	Animal::points = 0;
}

int Animal::setNum(int num){
	if (num >= 0){
		Animal::num = num;
	return 0;
	}
	else return 1;//Not right
}

int Animal::getNum(){
	return num;
}

int Animal::setChance(double chance){
	if (chance > 0 && chance <= 1){
		Animal::chance = chance;
	return 0;
	}
	else return 1;//Not right
}

double Animal::getChance(){
	return chance;
}

int Animal::setHave(bool have){
	if (have == 0 || have == 1){
		Animal::have = have;
		return 0;
	}
	else return 1;//Not right
}

bool Animal::getHave(){
	return have;
}

int Animal::setPoints(int points){
	if (points > 0){
		Animal::points = points;
		return 0;
	}
	else return 1;//Not right
}

int Animal::getPoints(){
	return points;
}
Animal::~Animal()
{
}
