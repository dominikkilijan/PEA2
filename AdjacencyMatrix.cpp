#include "AdjacencyMatrix.h"
//#include "Dynamic.h"
#include <iostream>
#include <iomanip>

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
		int val;
		*file >> N; // pierwsza liczba w pliku oznacza liczbe wierzcholkow

		createAdjacencyMatrix();

		// uzupelnienie macietrzy
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				*file >> val;
				matrix[i][j] = val;
			}
		}
		// wyswietlenie wypelnionej macierzy
		printAdjacencyMatrix();

		// uruchomienie algorytmu. Na etapie mierzenia czasow modyfikowana byla liczba iteracji w petli for
		for (int i = 0; i < 1; i++)
		{
			//Dynamic dynamic(N, matrix);
			//sumElapsed += dynamic.TSPDynamic();
		}

		cout << "Sredni czas wykonania w ms: " << setprecision(10) << sumElapsed << endl;
	}
	else cout << "Nie udalo sie otworzyc pliku! (w AdjancencyMatrix)\n";
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

