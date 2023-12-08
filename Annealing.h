#pragma once
#include <vector>

using namespace std;


class Annealing
{
public:
	Annealing(int, int, double, int**); // wierzcholki, stopTime, alfa, macierz 
	~Annealing();
	long long int read_QPC();
	double countSum(vector<int>);
	void startingPath();
	void randomStartingPath();
	void startingTemperature();
	long double TSPAnnealing();
	int simulatedAnnealing();
	void printCurrentPath();
	void PrintBestPath();
	void neighbourPath();
	bool probability();
	void nextTemperature();


private:
	vector<int> currentPath;
	vector<int> bestPath;
	vector<int> finalPath;

	int N;
	int** matrix;
	long double temperature;
	double a;
	int stopTime;
	double bestSum, currentSum, finalSum;
	long double delta;
};

