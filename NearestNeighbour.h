#pragma once
#include <vector>

using namespace std;

class NearestNeighbour
{
public:
	NearestNeighbour(int, int**);
	~NearestNeighbour();
	void findNearestNeighbourPath(vector<int>&);
	int findNearestNeighbour(int);

private:
	int** matrix;
	int N;
	vector<bool> visited;
};

