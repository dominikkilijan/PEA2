#include "Dynamic.h"
#include "AdjacencyMatrix.h"
#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <time.h>
#include <vector>
#include <bitset>
#include <fstream>

using namespace std;

//------------------------------------------------------------------------------------------------------------------------------------
Dynamic::Dynamic(int n, int** m)
{
	N = n;
	matrix = m;
	visitedAll = (1 << N) - 1;

	N2 = (1 << N);
	dp = new int* [N2];
	path = new int* [N];
	bestPath.reserve(N);

	for (int i = 0; i < N2; i++)
	{
		dp[i] = new int[N];
		for (int j = 0; j < N; j++)
		{
			dp[i][j] = -1;
		}
	}
	for (int i = 0; i < N; i++)
	{
		path[i] = new int[N2];
		for (int j = 0; j < N2; j++)
		{
			path[i][j] = -1;
		}
	}

}
Dynamic::~Dynamic()
{
	for (int i = 0; i < N2; i++)
	{
		delete[] dp[i];
	}
	delete[] dp;
	dp = nullptr;

	for (int i = 0; i < N; i++)
	{
		delete[] path[i];
	}
	delete[] path;
	path = nullptr;

	matrix = nullptr;
}
//------------------------------------------------------------------------------------------------------------------------------------
int Dynamic::tsp(int mask, int pos)
{
	if (mask == visitedAll) // jesli odwiedzono wszystkie wierzcholki
		return matrix[pos][0];

	if (dp[mask][pos] != -1) // sprawdzenie czy przypadek juz byl liczony
		return dp[mask][pos];

	int bestSum = INT_MAX;
	for (int i = 0; i < N; i++)
	{
		if ((mask & (1 << i)) == 0) // sprawdzenie czy wierzochlek byl juz odwiedzony
		{
			int currentSum = matrix[pos][i] + tsp(mask | (1 << i), i); // odleglosc z obecnego punktu do nastepnego + kolejne odcinki
			if (bestSum > currentSum)
			{
				bestSum = currentSum;
				path[pos][mask] = i; // tablica do odczytania sciezki koncowej
			}

		}
	}
	return dp[mask][pos] = bestSum;
}
//------------------------------------------------------------------------------------------------------------------------------------
long double Dynamic::TSPDynamic()
{

	long long int frequency, start, elapsed; // zmienne zwiazane z pomiarem czasu
	QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);

	// rozpoczecie pomiaru czasu
	start = read_QPC();

	// algorytm
	int finalSum = tsp(1, 0);
	decodePath(1, 0);
	// koniec algorytmu


	// koniec pomiaru czasu
	elapsed = read_QPC() - start;
	long double timeElapsed;
	timeElapsed = ((1000.0 * elapsed) / frequency);

	// wyswietlenie wyniku i zapisanie do pliku
	fstream file;
	file.open("temp.txt", ios::out);
	file << N << endl;
	cout << "Waga = " << finalSum << endl;
	cout << "Sciezka: 0->";
	file << 0 << endl;
	for (int i = 0; i <= bestPath.size() - 1; i++)
	{
		cout << bestPath[i] << "->";
		file << bestPath[i] << endl;
	}
	cout << "0" << endl;
	file << 0 << endl;
	file.close();

	return timeElapsed;
}
//------------------------------------------------------------------------------------------------------------------------------------
// metoda do precyzyjnego pomiaru czasu
long long int Dynamic::read_QPC()
{
	LARGE_INTEGER count;
	QueryPerformanceCounter(&count);
	return((long long int)count.QuadPart);
}
//------------------------------------------------------------------------------------------------------------------------------------
void Dynamic::printdp()
{

	for (int i = 0; i < N2; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cout << dp[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}
//------------------------------------------------------------------------------------------------------------------------------------
void Dynamic::printpath()
{

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N2; j++)
		{
			cout << path[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}
//------------------------------------------------------------------------------------------------------------------------------------
void Dynamic::decodePath(int mask, int pos)
{
	if (path[pos][mask] != -1)
	{
		int i = path[pos][mask]; // odczytywanie nastepnego wierzcholka do odwiedzenia
		bestPath.emplace_back(i);
		int newMask = mask | (1 << i); // uaktualnienie maski o nastepny wierzcholek
		decodePath(newMask, i);
	}
}