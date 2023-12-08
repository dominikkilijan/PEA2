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

// wypelnienie macierzy z podstawowego formatu
void AdjacencyMatrix::fillFromFile(fstream* file)
{
	if (file->is_open()) 
	{
		string line;
		while (getline(*file, line)) 
		{
			if (line.find("DIMENSION") != string::npos) 
			{
				// odczytanie znakow w linii z DIMENSION
				std::string dimensionStr;
				for (char c : line) {
					if (std::isdigit(c)) {
						dimensionStr += c;
					}
				}
				// do N wpisane zostaja cyfry czyli liczba wierzcholkow 
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
		int linesCount = 0;
		
		// liczenie N
		while (getline(*file, line))
		{
			if (line.find("<vertex>") != string::npos) 
			{
				while (getline(*file, line) && line.find("</vertex>") == string::npos)
				{
					if (line.find("<edge cost=\"") != string::npos)
					{
						// Increment linesCount for each line between <vertex> and </vertex>
						linesCount++;
					}
				}
				// Break the outer loop after processing the first <vertex> and </vertex>
				break;
			}
		}

		N = linesCount;

		// powrot kursora na szczyt pliku
		file->clear();
		file->seekg(0, std::ios::beg);

		createAdjacencyMatrix();

		while (getline(*file, line))
		{
			if (line.find("<vertex>") != string::npos) {
				i++;
				j = 0;
				while (getline(*file, line) && line.find("</vertex>") == string::npos) 
				{
					if (line.find("<edge cost=\"") != string::npos) 
					{
						// mantysa miedzy <edge cost=" i e+
						size_t costStartPos = line.find("<edge cost=\"") + 12;
						size_t costEndPos = line.find("e+", costStartPos);

						std::string costDoubleStr = line.substr(costStartPos, costEndPos - costStartPos);
						double costDouble = std::stod(costDoubleStr);

						// exponent miedzy e+ i "
						size_t exponentPos = costEndPos + 2;
						size_t exponentEndPos = line.find("\"", exponentPos);
						std::string exponentStr = line.substr(exponentPos, exponentEndPos - exponentPos);
						int exponent = std::stoi(exponentStr);

						// mantysa * exponent zeby dostac wartosc krawedzi
						int cost = static_cast<int>(costDouble * pow(10, exponent));
						cout << "ij = " << i << j << endl;
						matrix[i][j] = cost;
						j++;
					}
				}
			}
		}
	}
	else 
	{
		cout << "Nie udalo sie otworzyc pliku! (w AdjacencyMatrix)\n";
	}
}
//------------------------------------------------------------------------------------------------------------------------------------
void AdjacencyMatrix::runAlgorithm(int stopTime, double alpha)
{
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