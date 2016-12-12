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
					if (i < n){//"if" for to be in matrix of n*n
						if (i != j)	arr[i][j] = (int)cur;
						else arr[i][j] = inf;
					}
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
	sn = n;//Start n
	sarr = new int*[n];
	snames = new int[n];

	for (int i = 0; i < n; i++){
		pway[i] = new PWay[n];
		sarr[i] = new int[n];
		for (int j = 0; j < n; j++){
			sarr[i][j] = arr[i][j];
			cout << arr[i][j] << "\t";
			pway[i][j].start = to_string(i);
			pway[i][j].fin = to_string(j);
		}
		cout << "\n";
	}
	for (int i = 0; i < n; i++){
		snames[i] = names[i];
		cout << names[i] << " ";
	}
	cout << "\n";
	cout << "\n";
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			cout << pway[i][j].start << pway[i][j].mid << pway[i][j].fin << "\t";
		}
		cout << "\n";
	}
	cout << "\n";
	infile.close();
	return 0;
}

int Matrix::Write(char* filename)
{
	ofstream outfile(filename, ios_base::trunc);
	int* test;

	if (waylen > 0 && way != 0){//If n==0 then out file will be just cleared
		test = new int[annum];
		for (int i = 0; i < annum; i++){
			test[i] = 0;
		}
		for (int i = 0; i < waylen; i++){
			way[i];
			test[way[i]]++;
			if (test[way[i]]>1){
				outfile.close();
				return 0;// Uncorrect way
			}
		}
		if (outfile.is_open()){
			outfile << way[0];
			for (int i = 1; i < waylen; i++){
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
	findPWay();
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

	int last;
	int k = n;
	int ans = inf;
	int minh;//Minimum Hamilton cicle

	for (int i = 1; i < n; ++i){
		if (arr[i][0]>0){
			if (ans > t[m - 1][i] + arr[i][0]){
				ans = t[m - 1][i] + arr[i][0];
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
	//cout << "0 ";
	string out = pway[0][0].start;
	for (int i = 1; i < n; i++){
		out += pway[way[i-1]][way[i]].mid + pway[way[i-1]][way[i]].fin;
	}
	cout << out;

	std::vector<int> tmp;
	int n;
	stringstream stream(out);
	while (stream >> n){
		tmp.push_back(n);
	}
	waylen = tmp.size();
	for (int i = 0; i < waylen; i++)
		way[i] = tmp[i];

	if (ans == inf) return 0;
	else{
		tryCatch();
		return 1;//Way found
	}
	
}

int Matrix::findPWay(){
	for (int i = 0; i < n && n > 1; i++){
		if (animals[names[i]].getHave()){
			if (rebuild(i)) i--;
		}
	}
	return 1;
}
int Matrix::rebuild(int del){
	int reb = 1;
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			int l = pway[i][j].lastel;
			int f = stoi(pway[i][j].fin);
			if ((double)(arr[i][del] + arr[del][j]) <= 1.1 * (double)arr[i][j] && i != j && pway[i][j].mid == " " ||
				pway[i][j].mid != " " && (double)(arr[i][j] - sarr[l][f] + sarr[l][del] + sarr[del][f]) <= 1.1 * (double)arr[i][j] && i != j){
				arr[i][j] = arr[i][del] + arr[del][j];
				pway[i][j].mid += pway[i][del].fin + " ";
				pway[i][j].points += animals[del].getPoints();
				pway[i][j].lastel = stoi(pway[i][del].fin);
			}
		}
	}

	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			cout << arr[i][j] << "\t";
		}
		cout << "\n";
	}
	cout << "\n";
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			cout << pway[i][j].start << pway[i][j].mid << pway[i][j].fin << "\t";
		}
		cout << "\n";
	}
	cout << "\n";

	for (int i = 0; i < n - 1; i++){
		for (int j = 0; j < n - 1; j++){
			if (i >= del && j < del){
				arr[i][j] = arr[i+1][j];
				pway[i][j] = pway[i + 1][j];
			}
			if (i < del && j >= del){
				arr[i][j] = arr[i][j+1];
				pway[i][j] = pway[i][j + 1];
			}
			if (i >= del && j >= del){
				arr[i][j] = arr[i+1][j+1];
				pway[i][j] = pway[i + 1][j+1];
			}
		}
		if (i >= del){
			names[i] = names[i + 1];
		}
	}
	n--;
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			cout << arr[i][j] << "\t";
		}
		cout << "\n";
	}
	cout << "\n";
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			cout << pway[i][j].start << pway[i][j].mid << pway[i][j].fin << "\t";
		}
		cout << "\n";
	}
	cout << "\n";
	return 1;
}
int Matrix::tryCatch(){
	srand(time(0));
	vector<int> tmp;



	for (int i = 0; i < waylen; i++){
		int p = rand() * 100 / RAND_MAX;
		if (animals[names[way[i]]].getHave()){
			if (i > 0 && i < waylen - 1){
				if ((double)(sarr[way[i - 1]][way[i]] + sarr[way[i]][way[i + 1]]) <= 1.1 * (double)sarr[way[i - 1]][way[i + 1]]){
					tmp.push_back(way[i]);
					if (p < animals[names[way[i]]].getChance() * 100){
						points += animals[names[way[i]]].getPoints();
					}
				}
			}
			else{
				if (i == 0){
					tmp.push_back(way[i]);
					points += animals[names[way[i]]].getPoints();
				}
				else{
					if ((double)(sarr[way[i - 1]][way[i]] + sarr[way[i]][way[0]]) <= 1.1 * (double)sarr[way[i - 1]][way[0]]){
						tmp.push_back(way[i]);
						if (p < animals[names[way[i]]].getChance() * 100){
							points += animals[names[way[i]]].getPoints();
						}
					}
				}
			}
		}
		else{
			tmp.push_back(way[i]);
			if (p < animals[names[way[i]]].getChance() * 100){
				animals[names[way[i]]].setHave(true);
			}
		}
	}

	way = new int[waylen];
	waylen = tmp.size();
	for (int i = 0; i < waylen; i++)
		way[i] = tmp[i];

	return 1;
}
bool Matrix::accept(int n, int x){
	return (x & (1 << n)) != 0;
}

Matrix::~Matrix()
{
}
