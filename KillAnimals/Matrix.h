#pragma once

class Matrix
{
private:
	int** arr;
	int* names;
	int n;
	Animal* animals;
	int annum;
	int* way = 0;
public:
	Matrix();
	int Read(char* file);
	int Write(char* file);
	int findWay();
	~Matrix();
};

