#include "FileHandler.h"
#include "AdjacencyMatrix.h"
#include <iostream>
#include "AdjacencyMatrix.h"
#include <fstream>
#include <string>
#include <time.h>
#include <cstdlib>
#include <vector>

using namespace std;

AdjacencyMatrix adMat;

//------------------------------------------------------------------------------------------------------------------------------------
int** FileHandler::openFile(string filename)
{
	cout << "Otwieranie pliku tekstowego \"" << filename << "\"\n";
	file.open(filename, ios::in);
	if (file.is_open())
		adMat.fillFromFile(&file); // wypelnianie macierzy sasiedztwa
	else cout << "Nie udalo sie otworzyc pliku!\n";
	file.close();
	matrix = adMat.getAdjacencyMatrix();
	return matrix;
}
//------------------------------------------------------------------------------------------------------------------------------------
double FileHandler::readPathFromFile(string filename)
{
	int N, var1, var2;
	double sum = 0;
	file.open(filename, ios::in);
	if (file.is_open())
	{
		file >> N;
		file >> var1;
		cout << var1;
		for (int i = 0; i < N; i++)
		{
			file >> var2;
			cout << "->" << var2;
			sum += matrix[var1][var2];
			var1 = var2;
		}
		cout << "\n";
	}
	
	return sum;
}
//------------------------------------------------------------------------------------------------------------------------------------
int FileHandler::getN(string filename)
{
	int N = 0;
	file.open(filename, ios::in);
	if (file.is_open())
	{
		file >> N;
	}
	else cout << "Nie udalo sie otworzyc pliku!\n";
	file.close();
	
	return N;
}
//------------------------------------------------------------------------------------------------------------------------------------
void FileHandler::runAlgorithm()
{
	adMat.runAlgorithm();
}
//------------------------------------------------------------------------------------------------------------------------------------
void FileHandler::renameFile(string a, string b) 
{
	rename(a.c_str(), b.c_str());
}
//------------------------------------------------------------------------------------------------------------------------------------



