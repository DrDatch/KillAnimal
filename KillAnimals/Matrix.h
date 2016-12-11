#pragma once
#include "stdafx.h"
struct PWay{
	std::string start;
	std::string mid=" ";
	std::string fin;

	int id;
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
	PWay** pway;
public:
	Matrix();
	int Read(char* file);
	int Write(char* file);
	int findWay();
	int findPWay();
	bool accept(int n, int x);
	~Matrix();
};

