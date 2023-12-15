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
	stopTemperature = 0.000001;
	
	a = alpha;
	matrix = m;
	// zarezerwowanie odpowiedniej ilosci miejsca
	currentPath.reserve(N);
	bestPath.reserve(N);
	finalPath.reserve(N);

	// obliczenie temperatury poczatkowej
	startingTemperature();
	cout << "Temperatura poczatkowa = " << temperature << "\n";
	halfTemperature = temperature / 2;

	// pseudolosowosc do prawdopodobienstwa
	srand(temperature + time(NULL));

	// zmienne zwiazane z pomiarem czasu
	long long int frequency = 0;
	long long int start = 0;
	long long int elapsed = 0; 
	QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
}
//------------------------------------------------------------------------------------------------------------------------------------
Annealing::~Annealing()
{
	matrix = nullptr;
}
//------------------------------------------------------------------------------------------------------------------------------------
void Annealing::startingTemperature()
{
	temperature = 50000000 *  pow(-log10(a),2.0) * stopTime * 4/stopTemperature;
	cout << "a = " << a << "\n";
}
//------------------------------------------------------------------------------------------------------------------------------------
// funkcja do liczenia czasu
long long int Annealing::read_QPC()
{
	LARGE_INTEGER count;
	QueryPerformanceCounter(&count);
	return((long long int)count.QuadPart);
}
//------------------------------------------------------------------------------------------------------------------------------------
// wyliczanie wagi aktualnej sciezki sciezki
double Annealing::countSum(vector<int> countPath)
{
	countPath.reserve(N);
	double countSum = 0;

	for (int i = 0; i < N; i++)
	{
		countSum += matrix[countPath[i]][countPath[(i + 1) % N]]; // dzieki modulo na koncu zapetli sie do wierzcholka poczatkowego
	}

	return countSum;
}
//------------------------------------------------------------------------------------------------------------------------------------
void Annealing::randomPath()
{	
	auto rng = default_random_engine{};
	shuffle(begin(currentPath), end(currentPath), rng);
}
//------------------------------------------------------------------------------------------------------------------------------------
void Annealing::printCurrentPath()
{
	for (int i = 0; i < currentPath.size(); i++)
	{
		cout << currentPath[i] << " ";
	}
	cout << "\n";
}
//------------------------------------------------------------------------------------------------------------------------------------
void Annealing::PrintBestPath()
{
	for (int i = 0; i < bestPath.size(); i++)
	{
		cout << bestPath[i] << " ";
	}
	cout << "\n";
}
//------------------------------------------------------------------------------------------------------------------------------------
// wyliczanie sasiedztwa metoda 2-opt
void Annealing::neighbourPath()
{
	int id1 = rand() % N;
	int id2 = rand() % N;

	while (id1 == id2) {
		id2 = rand() % N;
	}

	if (id1 > id2) {
		swap(id1, id2);
	}
	vector<int> newPath = currentPath;
	
	reverse(newPath.begin() + id1, newPath.begin() + id2 + 1);

	double newDistance = countSum(newPath);
	double currentDistance = countSum(currentPath);

	currentPath = newPath;
}
//------------------------------------------------------------------------------------------------------------------------------------
// czy zaakceptowany zostanie gorszy wynik
bool Annealing::probability()
{
	long double randomNumber = (double)(rand()) / (RAND_MAX);
	long double probabilityNumber = exp(-delta / temperature);

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
long double Annealing::TSPAnnealing()
{
	// rozpoczecie pomiaru czasu
	start = read_QPC();

	// algorytm
	simulatedAnnealing();

	// koniec algorytmu


	// koniec pomiaru czasu
	//elapsed = read_QPC() - start;
	long double timeElapsed = 0;
	//timeElapsed = ((1000.0 * elapsed) / frequency);

	// wyswietlenie wyniku i zapisanie do pliku
	fstream file;
	file.open("temp.txt", ios::out);
	file << N << endl;
	long double finalTemp = exp(-delta / temperature);

	cout << "\n\nWaga = " << finalSum << endl;
	cout << "Prawdopodobienstwo koncowe = " << finalTemp << endl;
	cout << "Temperatura koncowa = " << temperature << endl;
	cout << "Czas znaleznienia najlepszego rozwiazania w ms: " << setprecision(10) << finalElapsed << endl;
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
	// poczatkowa sciezka
	NearestNeighbour nn(N, matrix, currentPath);
	nn.findNearestNeighbourPath();
	
	// przygotowanie do minutnika algorytmu
	const time_point<system_clock> startTime = system_clock::now();
	seconds stopTimeSeconds = seconds(stopTime);
	seconds finalTime;

	// poczatkowe wyniki
	bestSum = countSum(currentPath);
	finalSum = bestSum;
	finalPath = currentPath;
	int epochs = 100; // ile razy algorytm dla danej temperatury
	int worse = 0; // licznik czy wrocic do najlepszego rozwiazania
	int greedySum = bestSum;
	cout << "wynik z greedy = " << greedySum << "\n";

	// jesli odpowiednia temperatura i nie skonczyl sie czas
	while (temperature > stopTemperature && (system_clock::now() - startTime) < stopTimeSeconds)
	{
		for (int i = 0; i < epochs; i++)
		{		
			// nowe sasiedztwo
			neighbourPath();

			// czy lepsze rozwiazanie
			currentSum = countSum(currentPath);
			delta = currentSum - bestSum;

			if (delta < 0)
			{
				// jesli rozwiazanie jest lepsze niz poprzednie
				bestSum = currentSum;
				bestPath = currentPath;

				if (finalSum > currentSum)
				{
					// jesli rozwiazanie jest najlepsze do tej pory
					finalSum = currentSum;
					finalPath = currentPath;

					// zapisanie czasu znalezienia rozwiazania
					QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
					finalElapsed = ((1000.0 * (read_QPC() - start)) / frequency);
				}
				else if (finalSum < currentSum)
					worse++;
			}
			else if (probability())
			{
				bestSum = currentSum;
				bestPath = currentPath;

			}
			else if (!probability() && worse > 15)
			{
				worse = 0;
				currentSum = finalSum;
				currentPath = finalPath;
				bestSum = finalSum;
				bestPath = finalPath;
			}
			else
				worse++;
		}
		nextTemperature();
	}

	return 0;
}
//------------------------------------------------------------------------------------------------------------------------------------
