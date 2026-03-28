#pragma once
#include<fstream>
using namespace std;

class Matrix
{
public:

	Matrix();
	~Matrix();

	int n;
	int Size;
	int Unit;

	double Set1;
	double Set2;

	double factor;

	double** matrix;

	void fileLoad(); //loading for reading matrix + matirx size I/O + I/O matrix element
	void identityMatrix(); //making Identity Matrix
	void loadFullmatrix(); //Print input matrix + identity matrix
	void calulate();
	void loadFinalinversematrix();
	void writeFile();
};

