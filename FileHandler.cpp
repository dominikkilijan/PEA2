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
	cout << "adMat w FileHandler:\n";
	int** matrix = adMat.getAdjacencyMatrix();
	return matrix;
}
//------------------------------------------------------------------------------------------------------------------------------------
void FileHandler::writePathToFile(string filename, int N, int* path)
{
	file.open(filename, ios::out);
	file << N << "\n";
	if (file.is_open())
	{

		for (int i = 0; i < N; i++)
		{
			file << path[i] << "\n";
		}
	}
	else cout << "Nie udalo sie otworzyc pliku!\n";
	file.close();
}
//------------------------------------------------------------------------------------------------------------------------------------
float FileHandler::readPathFromFile(string filename)
{
	
	
	return 0.0f;
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


