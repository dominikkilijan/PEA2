#include "AdjacencyMatrix.h"
#include "Dynamic.h"
#include "Annealing.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>
#include <sstream>
#include <cmath>

using namespace std;


//------------------------------------------------------------------------------------------------------------------------------------
AdjacencyMatrix::~AdjacencyMatrix()
{
	deleteAdjacencyMatrix();
}
//------------------------------------------------------------------------------------------------------------------------------------
// utworzenie macierzy o wymiarach n na n. Macierz wypelniona jest wartosciami -1
void AdjacencyMatrix::createAdjacencyMatrix()
{
	matrix = new int* [N];
	for (int i = 0; i < N; i++)
	{
		matrix[i] = new int[N];
		for (int j = 0; j < N; j++)
		{
			matrix[i][j] = -1;
		}
	}
}

//------------------------------------------------------------------------------------------------------------------------------------

void AdjacencyMatrix::deleteAdjacencyMatrix()
{
	if (matrix != nullptr)
	{
		for (int i = 0; i < N; i++)
		{
			delete[] matrix[i];
		}
		delete[] matrix;
		matrix = nullptr;
	}
}
//------------------------------------------------------------------------------------------------------------------------------------

void AdjacencyMatrix::fillFromFile(fstream* file) // do zmiany jesli zdaze
{
	if (file->is_open()) 
	{
		string line;
		while (getline(*file, line)) 
		{
			if (line.find("DIMENSION") != string::npos) 
			{
				std::string dimensionStr;
				for (char c : line) {
					if (std::isdigit(c)) {
						dimensionStr += c;
					}
				}
				N = std::stoi(dimensionStr);

				createAdjacencyMatrix();
			}
			else if (line.find("EDGE_WEIGHT_SECTION") != std::string::npos)
				break;
		}
		// uzupelnienie macietrzy
		int val;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				*file >> val;
				matrix[i][j] = val;
			}
		}
		//printAdjacencyMatrix();
	}
	else cout << "Nie udalo sie otworzyc pliku! (w AdjancencyMatrix)\n";
}
//------------------------------------------------------------------------------------------------------------------------------------
void AdjacencyMatrix::fillFromFileXML(fstream* file)
{
	if (file->is_open())
	{
		string line;
		int i = -1;
		int j = 0;
		while (getline(*file, line))
		{
			if (line.find("<description>") != string::npos)
			{
				std::string dimensionStr;
				for (char c : line) {
					if (std::isdigit(c)) {
						dimensionStr += c;
					}
				}
				N = std::stoi(dimensionStr);
				createAdjacencyMatrix();
			}
			else if (line.find("<vertex>") != string::npos) {
				i++;
				j = 0;
				while (getline(*file, line) && line.find("</vertex>") == string::npos) 
				{
					if (line.find("<edge cost=\"") != string::npos) 
					{
						// mantysa
						size_t costStartPos = line.find("<edge cost=\"") + 12;
						size_t costEndPos = line.find("e+", costStartPos);

						std::string costDoubleStr = line.substr(costStartPos, costEndPos - costStartPos);
						double costDouble = std::stod(costDoubleStr);

						// exponent
						size_t exponentPos = costEndPos + 2;
						size_t exponentEndPos = line.find("\"", exponentPos);
						std::string exponentStr = line.substr(exponentPos, exponentEndPos - exponentPos);
						int exponent = std::stoi(exponentStr);

						// mantysa * exponent zeby dostac wartosc krawedzi
						int cost = static_cast<int>(costDouble * pow(10, exponent));

						matrix[i][j] = cost;
						j++;
					}
				}
			}
		}
	}
	else {
		cout << "Nie udalo sie otworzyc pliku! (w AdjacencyMatrix)\n";
	}
}
//------------------------------------------------------------------------------------------------------------------------------------
void AdjacencyMatrix::runAlgorithm(int stopTime, double alpha)
{
	// wyswietlenie wypelnionej macierzy
	//printAdjacencyMatrix();
	sumElapsed = 0;
		
	// uruchomienie algorytmu. Na etapie mierzenia czasow modyfikowana byla liczba iteracji w petli for
	for (int i = 0; i < 1; i++)
	{
		Annealing sa(N, stopTime, alpha, matrix);
		sumElapsed += sa.TSPAnnealing();
	}
	cout << "Sredni czas wykonania w ms: " << setprecision(10) << sumElapsed << endl;
	
}
//------------------------------------------------------------------------------------------------------------------------------------

void AdjacencyMatrix::printAdjacencyMatrix()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cout << matrix[i][j] << "\t";
		}
		cout << "\n";
	}
}
//------------------------------------------------------------------------------------------------------------------------------------
int** AdjacencyMatrix::getAdjacencyMatrix()
{
	return matrix;
}