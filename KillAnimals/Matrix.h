#pragma once
#include "stdafx.h"
struct PWay{
	std::string start;
	std::string mid=" ";
	std::string fin;
	int points=0;
	int weight=0;
};

class Matrix
{
private:
	int** arr;
	int* names;
	int n;
	Animal* animals;
	int annum;
	int* way = 0;
	int waylen;
	PWay** pway;
	const int inf = 1000;
public:
	Matrix();
	int Read(char* file);
	int Write(char* file);
	int findWay();
	int findPWay();
	bool accept(int n, int x);
	int rebuild(int del);
	~Matrix();
};

