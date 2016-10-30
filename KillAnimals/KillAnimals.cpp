// KillAnimals.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	Matrix mat;
	int err = mat.Read("input.txt");
	if (err){
		cout << "Wrong input!\nCode: " << err << "\n";
		mat.Write("output.txt");
		return 0;
	}
	mat.Write("output.txt");

	return 0;
}

