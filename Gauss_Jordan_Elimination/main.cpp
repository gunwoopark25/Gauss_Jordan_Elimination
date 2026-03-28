#include "Matrix.h"
#include<iostream>
#include<string>
#include<fstream>

using namespace std;

void main()
{
	Matrix matrix3;

	cout << "identity Matrix" << endl;
	matrix3.identityMatrix();

	cout << "3*6 matrix" << endl;
	matrix3.loadFullmatrix();

	matrix3.calulate();

	cout << "transform 3*6 matrix" << endl;
	matrix3.loadFullmatrix();

	cout << "Final Inverse Matrix" << endl;
	matrix3.loadFinalinversematrix();
}
