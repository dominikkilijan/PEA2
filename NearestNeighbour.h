#pragma once
#include <vector>

using namespace std;

class NearestNeighbour
{
public:
	NearestNeighbour(int, int**, vector<int>&);
	~NearestNeighbour();
	void findNearestNeighbourPath();
	int findNearestNeighbour(int);
	void printCurrentPath();

private:
	int** matrix;
	int N;
	vector<bool> visited;
	vector<int> currentPath;
};

