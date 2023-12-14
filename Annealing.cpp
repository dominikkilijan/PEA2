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

	// obliczenie temperatury poczatkowej
	startingTemperature();
	cout << "Temperatura poczatkowa = " << temperature << "\n";
	halfTemperature = temperature / 2;
	// pseudolosowosc do prawdopodobienstwa
	srand(temperature + time(NULL));
}
//------------------------------------------------------------------------------------------------------------------------------------
Annealing::~Annealing()
{
	matrix = nullptr;
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
void Annealing::randomPath() // tutaj trzeba zrobic greedy algorithm
{	
	auto rng = default_random_engine{};
	shuffle(begin(currentPath), end(currentPath), rng);
}
//------------------------------------------------------------------------------------------------------------------------------------
void Annealing::startingTemperature()
{
	temperature = 5 * (100*stopTime + 100*a);
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
void Annealing::neighbourPath() // sasiedztwo 2-opt
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
	// 2-opt
	reverse(newPath.begin() + id1, newPath.begin() + id2 + 1);

	double newDistance = countSum(newPath);
	double currentDistance = countSum(currentPath);
	/*if (newDistance < currentDistance) 
	{
		currentPath = newPath;
	}*/
	currentPath = newPath;
}
//------------------------------------------------------------------------------------------------------------------------------------
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
	//cout << "Temperature = " << temperature << "\n";
}
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
	long double finalTemp = exp(-delta / temperature);

	cout << "Waga = " << finalSum << endl;
	cout << "Prawdopodobientwo koncowe = " << finalTemp << endl;
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
	NearestNeighbour nn(N, matrix, currentPath);
	nn.findNearestNeighbourPath();
	
	const time_point<system_clock> startTime = system_clock::now();
	seconds stopTimeSeconds = seconds(stopTime);

	bestSum = countSum(currentPath);
	finalSum = bestSum;
	finalPath = currentPath;
	int epochs;
	int worse = 0;
	int greedySum = bestSum;
	cout << "wynik z greedy = " << greedySum << "\n";
	cout << "finalSum = " << finalSum << "\n";

	while (temperature > 0.000001 && (system_clock::now() - startTime) < stopTimeSeconds)
	{
		//cout << "epoki = " << epochs << "\n";
		epochs = 100;
		//epochs = floor(temperature / 100) + 1;
		//cout << "epoki = " << epochs << "\n";
		for (int i = 0; i < epochs; i++)
		{
			/*if (temperature > halfTemperature)
				randomPath();
			else*/			
				neighbourPath();


			//printCurrentPath();
			currentSum = countSum(currentPath);
			//cout << "currentSum = " << currentSum << "\n";
			delta = currentSum - bestSum;
			//cout << "delta = " << delta << "\n";

			if (delta < 0)
			{
				bestSum = currentSum;
				bestPath = currentPath;
				//cout << "bestSum = " << bestSum << "\n";

				if (finalSum > currentSum)
				{
					finalSum = currentSum;
					finalPath = currentPath;
					cout << "finalSum = " << finalSum << "\n";
				}
				else if (finalSum < currentSum)
				{
					worse++;
				}
			}
			else if (probability())
			{
				//cout << endl;
				bestSum = currentSum;
				bestPath = currentPath;
				worse++;
			}
			else
				worse++;

			if (worse > 15)
			{
				worse = 0;
				currentSum = finalSum;
				currentPath = finalPath;
				bestSum = finalSum;
				bestPath = finalPath;
				//cout << "currentSum = " << currentSum << "\n";
			}
		}
		//cout << "currnetSum:" << currentSum << " ";
		nextTemperature();
		epochs = 7;
	}

	return 0;
}
//------------------------------------------------------------------------------------------------------------------------------------
