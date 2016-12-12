#pragma once
#include "stdafx.h"
struct PWay{
	std::string start;
	std::string mid=" ";
	std::string fin;
	int points = 0;
	int weight = 0;
	int lastel = 0;
};

class Matrix
{
private:
	int** arr;
	int* names;
	int n;
	int** sarr;
	int* snames;
	int sn;
	Animal* animals;
	int annum;
	int* way = 0;
	int* fway = 0;
	int waylen;
	PWay** pway;
	const int inf = 99999;
	int points = 0;
public:
	Matrix();
	int Read(std::string file);
	int Write(std::string file);
	int findWay();
	int findPWay();
	int tryCatch();
	bool accept(int n, int x);
	int rebuild(int del);
	~Matrix();
};

