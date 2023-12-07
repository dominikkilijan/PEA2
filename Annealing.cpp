#include "Annealing.h"
#include "AdjacencyMatrix.h"
#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <time.h>
#include <fstream>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;


//------------------------------------------------------------------------------------------------------------------------------------
Annealing::Annealing(int n, int sTime, double alpha, int** m)
{
	cout << "Poczatek konstruktora\n";
	N = n;
	stopTime = sTime;
	a = alpha;
	matrix = m;

	cout << "Rezerwacja miejsca na wektory\n";
	currentPath.reserve(N);
	bestPath.reserve(N);

	cout << "Wypelnienie wektorow\n";
	for (int i = 0; i < N; i++)
	{
		currentPath.emplace_back(i);
		bestPath.emplace_back(i);
	}

	startingPath();
	printCurrentPath();

	startingTemperature();
	cout << "Starting temperature = " << temperature << "\n";
}
//------------------------------------------------------------------------------------------------------------------------------------
Annealing::~Annealing()
{
	matrix = nullptr;
}
//------------------------------------------------------------------------------------------------------------------------------------
long long int Annealing::read_QPC()
{
	LARGE_INTEGER count;
	QueryPerformanceCounter(&count);
	return((long long int)count.QuadPart);
}
//------------------------------------------------------------------------------------------------------------------------------------
double Annealing::countSum()
{
	
	return 0.0;
}
//------------------------------------------------------------------------------------------------------------------------------------
void Annealing::startingPath() // tutaj trzeba zrobic greedy algorithm. moze zawsze najkrotsza sciezka, nie powinno byc bardzo trudne
{
	cout << "Poczatkowa sciezka\n";
	auto rng = default_random_engine{};
	shuffle(begin(currentPath), end(currentPath), rng);
}
//------------------------------------------------------------------------------------------------------------------------------------
void Annealing::startingTemperature()
{
	cout << "Temperatura poczatkowa\n";
	temperature = 100 + 0.1*stopTime + 1.5*a;
}
//------------------------------------------------------------------------------------------------------------------------------------
long double Annealing::TSPAnnealing()
{

	long long int frequency, start, elapsed; // zmienne zwiazane z pomiarem czasu
	QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);

	// rozpoczecie pomiaru czasu
	start = read_QPC();

	// algorytm
	cout << "Miejsce na algorytm\n";
	Sleep(1000);
	bestPath = currentPath;
	// koniec algorytmu


	// koniec pomiaru czasu
	elapsed = read_QPC() - start;
	long double timeElapsed;
	timeElapsed = ((1000.0 * elapsed) / frequency);

	// wyswietlenie wyniku i zapisanie do pliku
	fstream file;
	file.open("temp.txt", ios::out);
	file << N << endl;

	for (int i = 0; i <= bestPath.size(); i++)
	{
		if (i != bestPath.size())
		{
			cout << bestPath[i] << "->";
			file << bestPath[i] << "\n";
		}
		else
		{
			cout << bestPath[0] << "\n";
			file << bestPath[0] << "\n";
		}
	}

	file.close();

	return timeElapsed;
}
//------------------------------------------------------------------------------------------------------------------------------------
int Annealing::tsp(int, int)
{
	
	return 0;
}
//------------------------------------------------------------------------------------------------------------------------------------
void Annealing::printCurrentPath()
{
	for (int i = 0; i < N; i++)
	{
		cout << currentPath[i] << " ";
	}
	cout << "\n";
}
//------------------------------------------------------------------------------------------------------------------------------------
void Annealing::PrintBestPath()
{
	for (int i = 0; i < N; i++)
	{
		cout << bestPath[i] << " ";
	}
	cout << "\n";
}
//------------------------------------------------------------------------------------------------------------------------------------
