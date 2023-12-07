#pragma once
#include <fstream>

using namespace std;

class AdjacencyMatrix
{
public:
	~AdjacencyMatrix();

	void fillFromFile(fstream*);
	void printAdjacencyMatrix();
	void deleteAdjacencyMatrix();
	void createAdjacencyMatrix();
	int** getAdjacencyMatrix();
	void runAlgorithm(int, double);


private:
	int N;
	int** matrix;
	long double sumElapsed;


};


