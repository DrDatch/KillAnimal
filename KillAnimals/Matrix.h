#pragma once

class Matrix
{
private:
	int** arr;
	int* names;
	double* chances;
	int* exist;
	int* points;
	int n;
	Animal* animals;
	int annum;
public:
	Matrix();
	int Read(char* file);
	int Write(char* file);
	~Matrix();
};

