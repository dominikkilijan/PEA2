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
	N = n;
	stopTime = sTime;
	a = alpha;
	matrix = m;
	// zarezerwowanie odpowiedniej ilosci miejsca
	currentPath.reserve(N);
	bestPath.reserve(N);

	// wypelnienie wektora (przy greedy juz nie bedzie potrzebne)
	cout << "Wypelnienie wektorow\n";
	for (int i = 0; i < N; i++)
	{
		currentPath.emplace_back(i);
	}

	// poczatkowa sciezka
	startingPath();
	printCurrentPath();

	// obliczenie temperatury poczatkowej
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
	currentSum = 0;

	for (int i = 0; i < N; i++)
	{
		currentSum += matrix[currentPath[i]][currentPath[(i + 1) % N]];
	}

	return currentSum;
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
	countSum();
	bestSum = currentSum;
	// koniec algorytmu


	// koniec pomiaru czasu
	elapsed = read_QPC() - start;
	long double timeElapsed;
	timeElapsed = ((1000.0 * elapsed) / frequency);

	// wyswietlenie wyniku i zapisanie do pliku
	fstream file;
	file.open("temp.txt", ios::out);
	file << N << endl;

	cout << "Waga = " << bestSum << endl;
	cout << "Sciezka: ";

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
	cout << "\n";
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
void Annealing::neighbourPath() // sasiedztwo
{

}
//------------------------------------------------------------------------------------------------------------------------------------
double Annealing::probability()
{
	return 0.0;
}
//------------------------------------------------------------------------------------------------------------------------------------
