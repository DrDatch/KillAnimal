#include "stdafx.h"
#include "Matrix.h"


Matrix::Matrix()
{
	cout << "Const OK\n";
}


int Matrix::Read(char* filename)
{
	n = 0;// For out file clearance if something goes wrong
	ifstream anfile("animals");
	if (anfile.is_open()){
		queue<double> tmp;
		double i;
		int count = 0;

		anfile.seekg(0, std::ios::end);
		int size = anfile.tellg();

		anfile.seekg(0, 0);
		while (!anfile.eof() && count <= size){
			anfile >> i;
			tmp.push(i);
			++count;
		}
		if (count > size) return 1;//Animals is really wrong

		double dannum;
		annum = dannum = (double)count / 3;
		if (dannum != (double)annum){
			return 2;//Animals is not 3 params for each
		}
		animals = new Animal[annum];
		double a=-1, b=-1, c=-1;
		for (int i = 0; i < annum; i++){
			a = tmp.front();
			tmp.pop();
			b = tmp.front();
			tmp.pop();
			c = tmp.front();
			tmp.pop();
			if (animals[i].setNum(i) || animals[i].setChance(a) || animals[i].setHave(b) || animals[i].setPoints(c)){
				return 3;//Animals specs is wrong
			}
			a = b = c = -1;
		}
		for (int i = 0; i < annum; i++){
			cout << animals[i].getNum() << " " << animals[i].getChance() << " " << animals[i].getHave() << " " << animals[i].getPoints() << "\n";
		}
	}
	anfile.close();
	ifstream infile(filename);
	if (infile.is_open()){
		cout << "File name:" << filename << "\n";
		int count = 0;
		int size = 0;

		infile.seekg(0, std::ios::end);
		size = infile.tellg();
		cout << "Size of file = " << size << "\n";
		
		queue<double> tmp;
		double i;
		infile.clear();
		infile.seekg(0, 0);
		while (!infile.eof() && count <= size){
			infile >> i;
			tmp.push(i);
			//cout << i << "\n";
			++count;
			i = -1;
		}
		if (count > size) return 4;//Input is really wrong
		int strings = 1;//Strings after matrix
		double nd = (sqrt((double)strings*(double)strings+4*(double)count) - (double)strings) / 2.0;
		n = (int)nd;


		if (nd != (double)n){
			n = 0;// For out file clearance if something goes wrong
			return 5;//Uncorect num of numbers
		}

		cout << "n=" << n << "\n";
		arr = new int*[n];
		names = new int[n];
		double cur;
		for (int i = 0; i < n; i++) arr[i] = new int[n];
		for (int i = 0; i < n + strings; i++){
			for (int j = 0; j < n; j++){
				cur = 0;
				cur = tmp.front();
				if (cur < 0){
					n = 0;// For out file clearance if something goes wrong
					return 6;//Something is less then 0 or there is space in the end
				}

				if (cur == 0 && i < n && i != j){
					n = 0;// For out file clearance if something goes wrong
					return 7;//The way length is 0 between two animals
				}

				if (i == j && cur != 0){
					n = 0;// For out file clearance if something goes wrong
					return 8;//The way length is not 0 on diagonal
				}
				else{
					if(i < n) arr[i][j] = (int)cur;
				}

				if (i == n && (cur < 0 || cur >= annum)){
					n = 0;// For out file clearance if something goes wrong
					return 9;//Number of animal in namelist is less then 0 or bigger then animals in "animals" file
				}
				else{
					if(i == n) names[j] = (int)cur;
				}
				
				//cout << cur << " ";
				tmp.pop();
			}
			//cout << "\n";
		}
	}
	pway = new PWay*[n];

	for (int i = 0; i < n; i++){
		pway[i] = new PWay[n];
		for (int j = 0; j < n; j++){
			cout << arr[i][j] << " ";
			pway[i][j].start = to_string(j);
			pway[i][j].fin = to_string(i);
		}
		cout << "\n";
	}
	for (int i = 0; i < n; i++){
		cout << names[i] << " ";
	}
	cout << "\n";
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			cout << pway[i][j].start << pway[i][j].mid << pway[i][j].fin << "\t";
		}
		cout << "\n";
	}
	infile.close();
	return 0;
}

int Matrix::Write(char* filename)
{
	ofstream outfile(filename, ios_base::trunc);
	int* test;
	if (n > 0 && way != 0){//If n==0 then out file will be just cleared
		test = new int[n];
		for (int i = 0; i < n; i++){
			test[i] = 0;
		}
		for (int i = 0; i < n; i++){
			way[1];
			test[1];
			test[way[i]]++;
			if (test[way[i]]>1){
				outfile.close();
				return 0;// Uncorrect way
			}
		}
		if (outfile.is_open()){
			outfile << way[0];
			for (int i = 1; i < n; i++){
				outfile << " " << way[i];
			}
		}
		outfile.close();
		return 1;// Correct
	}
	outfile.close();
	return 0;// Uncorrect
}

int Matrix::findWay(){
	const int inf = 1000;
	//int n = 5;
	int m = 1 << n;//m=2^n
	int temp;
	int** t;

	way = new int[n];
	way[0] = 0; //Start with 0
	t = new int*[m];
	for (int i = 0; i < m; i++){
		t[i] = new int[n];
	}


	t[1][0] = 0;
	for (int i = 1; i < m; i += 2){
		for (int j = (i == 1) ? 1 : 0; j<n; j++){
			t[i][j] = inf;
			if (j > 0 && accept(j, i)){
				temp = i ^ (1 << j);
				for (int k = 0; k < n; k++){
					if (accept(k, i) && arr[k][j]>0){
						t[i][j] = min(t[i][j], t[temp][k] + arr[k][j]);
					}
				}
			}
		}
	}

	/*for (int i = 1; i < m; i += 2){
		cout << i << "\t";
		for (int j = 0; j < n; j++){
			if (t[i][j] == 100) cout << "inf\t";
			else cout << t[i][j] << "\t";
		}
		cout << "\n";
	}*/

	int last;
	int k = n;
	int ans = inf;
	int minh;//Minimum Hamilton cicle

	for (int i = 1; i < n; ++i){
		if (arr[i][0]>0){
			if (ans > t[m - 1][i] + arr[i][0]){
				ans = t[m - 1][i] + arr[i][0];
				cout << arr[i][0] << " " << t[m - 1][i] << "\n";
				last = i; way[k] = i; minh = t[m - 1][i];
			}
		}
	}

	int line;
	int i = m;
	while (i > 1){
		line = i - pow(2, last);
		minh = t[line - 1][last];
		for (int j = 0; j < n; j++){
			if (t[i - 1][last] == t[line - 1][j] + arr[j][last] && t[i - 1][last] < minh) {
				minh = t[i - 1][last];
				way[k - 1] = last;
				last = j;
			}

		}
		i = line;
		k--;

	}
	for (int i = 0; i < n; i++){
		cout << way[i] << " ";
	}
	if (ans == inf) return 0;
	else return 1;//Way found
	
}

int Matrix::findPWay(){

	return 1;
}

bool Matrix::accept(int n, int x)
{
	return (x & (1 << n)) != 0;
}

Matrix::~Matrix()
{
}
