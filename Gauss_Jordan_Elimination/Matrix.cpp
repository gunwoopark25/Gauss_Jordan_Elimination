#include "Matrix.h"
#include<iostream>
#include<string>
#include<fstream>

using namespace std;

//constructor
Matrix::Matrix()
{
	cout << "input matrix" << endl;
	Matrix::fileLoad();
}

Matrix::~Matrix()
{
	Matrix::writeFile();
}

//function
void Matrix::fileLoad()
{
	ifstream fin("Guassjordan_3.txt");
	if (!fin)
	{
		cout << "You can't load this file" << endl; //when can't file loading
	}

	int n; //reading 0st element 
	fin >> n; //matrix size read in  file

	cout << n << endl; //output matrix size

	Size = n;


	matrix = new double* [Size]; //dynamic Memory Allocation
	for (int i = 0; i < Size; i++)
	{
		matrix[i] = new double[2 * Size];
	}

	for (int i = 0; i < Size; i++) //input matrix element
	{
		for (int j = 0; j < Size; j++)
		{
			fin >> matrix[i][j];
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
	fin.close();
}

void Matrix::identityMatrix()
{
	Unit = Size;

	for (int i = 0; i < Unit; i++) //Make Identity Matrix using for&if 
	{
		for (int j = Unit; j < 2 * Unit; j++)
		{
			if (i == j - Unit)
			{
				matrix[i][j] = 1;
			}
			else
			{
				matrix[i][j] = 0;
			}
			cout << matrix[i][j] << " "; //Print the identity matrix in matrix form 
		}
		cout << endl;
	}
}

void Matrix::loadFullmatrix()
{
	for (int i = 0; i < Size; i++)
	{
		for (int j = 0; j < 2 * Size; j++)
		{
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}

void Matrix::calulate()
{
	for (int i = 0; i < Unit; i++)
	{
		Set2 = matrix[i][i];
		for (int j = 0; j < 2 * Unit; j++)
		{
			matrix[i][j] /= Set2;
		}

		for (int k = 0; k < Unit; k++)
		{
			if (k != i)
			{
				factor = matrix[k][i];
				if (factor != 0) //만약에 0이라면 계산 안함
				{
					for (int j = 0; j < 2 * Unit; j++)
					{
						matrix[k][j] -= matrix[i][j] * factor;
					}
				}
			}
		}
	}
}

void Matrix::loadFinalinversematrix()
{
	for (int i = 0; i < Size; i++)
	{
		for (int j = Size; j < 2 * Size; j++)
		{
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}

void Matrix::writeFile()
{

	ofstream writeFile("Guassjordan_3_ans.txt");

	if (!writeFile)
	{
		cout << "You can't load this file" << endl; //when can't file output
	}
	else
	{
		for (int i = 0; i < Size; i++)
		{
			for (int j = Size; j < 2 * Size; j++)
			{
				writeFile << matrix[i][j] << " ";
			}
			writeFile << endl;
		}
		writeFile.close();
		cout << "File output completed" << endl;
	}
}