#include "Annealing.h"
#include "AdjacencyMatrix.h"
#include "NearestNeighbour.h"
#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <time.h>
#include <fstream>
#include <vector>
#include <algorithm>
#include <random>
#include <math.h>
#include <chrono>

using namespace std;
using namespace std::chrono;


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
	finalPath.reserve(N);

	// wypelnienie wektora (przy greedy juz nie bedzie potrzebne)
	/*for (int i = 0; i < N; i++)
	{
		currentPath.emplace_back(i);
		bestPath.emplace_back(i);
		finalPath.emplace_back(i);
	}*/

	// poczatkowa sciezka
	//randomStartingPath();
	NearestNeighbour nn(N, matrix, currentPath);
	nn.findNearestNeighbourPath();
	cout << "Po wywolaniu findNearestNeighbourPath() \n";
	PrintBestPath();

	// obliczenie temperatury poczatkowej
	startingTemperature();
	cout << "Temperatura poczatkowa = " << temperature << "\n";

	// pseudolosowosc do prawdopodobienstwa
	srand(time(NULL));
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
double Annealing::countSum(vector<int> countPath)
{
	countPath.reserve(N);
	double countSum = 0;

	for (int i = 0; i < N; i++)
	{
		countSum += matrix[countPath[i]][countPath[(i + 1) % N]];
	}

	return countSum;
}
//------------------------------------------------------------------------------------------------------------------------------------
void Annealing::randomStartingPath() // tutaj trzeba zrobic greedy algorithm. moze zawsze najkrotsza sciezka, nie powinno byc bardzo trudne
{
	cout << "Poczatkowa sciezka\n";
	auto rng = default_random_engine{};
	shuffle(begin(currentPath), end(currentPath), rng);
}
//------------------------------------------------------------------------------------------------------------------------------------
void Annealing::startingTemperature()
{
	temperature = 100 + stopTime + 100*a;
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
void Annealing::neighbourPath() // sasiedztwo swap2
{
	int id1 = 0;
	int id2 = 0;

	id1 = rand() % N;
	do
	{
		id2 = rand() % N;
	} while (id1 == id2);

	iter_swap(currentPath.begin() + id1, currentPath.begin() + id2);
}
//------------------------------------------------------------------------------------------------------------------------------------
bool Annealing::probability()
{
	double randomNumber = (double)(rand()) / (RAND_MAX);
	double probabilityNumber = exp(-delta / temperature);

	if (randomNumber < probabilityNumber)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
//------------------------------------------------------------------------------------------------------------------------------------
void Annealing::nextTemperature()
{
	temperature *= a;
}
//------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------
long double Annealing::TSPAnnealing()
{

	long long int frequency, start, elapsed; // zmienne zwiazane z pomiarem czasu
	QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);

	// rozpoczecie pomiaru czasu
	start = read_QPC();

	// algorytm
	simulatedAnnealing();

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
	cout << "Prawdopodobientwo koncowe = " << exp(-delta / temperature) << endl;
	cout << "Temperatura koncowa = " << temperature << endl;
	cout << "Sciezka: ";

	for (int i = 0; i <= finalPath.size(); i++)
	{
		if (i != finalPath.size())
		{
			cout << finalPath[i] << "->";
			file << finalPath[i] << "\n";
		}
		else
		{
			cout << finalPath[0] << "\n";
			file << finalPath[0] << "\n";
		}
	}
	cout << "\n";
	file.close();

	return timeElapsed;
}
//------------------------------------------------------------------------------------------------------------------------------------
int Annealing::simulatedAnnealing()
{
	const time_point<system_clock> startTime = system_clock::now();
	seconds stopTimeSeconds = seconds(stopTime);

	bestSum = countSum(bestPath);

	while (temperature > 1 && (system_clock::now() - startTime) < stopTimeSeconds)
	{
		neighbourPath();
		currentSum = countSum(currentPath);
		delta = currentSum - bestSum;

		if (delta < 0)
		{
			bestSum = currentSum;
			finalSum = currentSum;
			bestPath = currentPath;
			finalPath = currentPath;
		}
		else if (probability() > 0)
		{
			bestSum = currentSum;
			bestPath = currentPath;
		}
		nextTemperature();
	}

	return 0;
}
//------------------------------------------------------------------------------------------------------------------------------------
