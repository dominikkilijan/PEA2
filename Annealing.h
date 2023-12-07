#pragma once
#include <vector>

using namespace std;


class Annealing
{
public:
	Annealing(int, int, double, int**); // wierzcholki, stopTime, alfa, macierz 
	~Annealing();
	long long int read_QPC();
	double countSum();
	void startingPath();
	void startingTemperature();
	long double TSPAnnealing();
	int tsp(int, int);
	void printCurrentPath();
	void PrintBestPath();
	void neighbourPath();
	bool probability();
	void nextTemperature();


private:
	vector<int> currentPath;
	vector<int> bestPath;

	int N;
	int** matrix;
	double temperature;
	double a;
	int stopTime;
	double bestSum, currentSum;
	double delta;
};

