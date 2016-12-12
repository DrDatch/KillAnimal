// KillAnimals.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"


int main(int argc, char* argv[])
{
	Matrix mat;
	int err = mat.Read("input.txt");
	if (err){
		cout << "Wrong input!\nCode: " << err << "\n";
		mat.Write("output.txt");
		return 0;
	}
	mat.findWay();
	if (!mat.Write("output.txt")){
		cout << "Uncorrect output!\n";
	}

	return 0;
}

