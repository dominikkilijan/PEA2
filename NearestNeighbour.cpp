#include "NearestNeighbour.h"
#include <iostream>
#include <vector>

using namespace std;

//------------------------------------------------------------------------------------------------------------------------------------
NearestNeighbour::NearestNeighbour(int n, int** m, vector<int>& path) : N(n), matrix(m), currentPathNN(path)
{
	visited.resize(N, false);
}
//------------------------------------------------------------------------------------------------------------------------------------
NearestNeighbour::~NearestNeighbour()
{
	matrix = nullptr;
}
//------------------------------------------------------------------------------------------------------------------------------------
void NearestNeighbour::findNearestNeighbourPath()
{
	int start = 0;
	currentPathNN.emplace_back(start);
	visited[start] = true;

	for (int i = 0; i < N-1; i++)
	{
		int nearestNeighbour = findNearestNeighbour(start);
		currentPathNN.emplace_back(nearestNeighbour);
		visited[nearestNeighbour] = true;
		start = nearestNeighbour;
		//printCurrentPathNN();
	}
}
//------------------------------------------------------------------------------------------------------------------------------------
int NearestNeighbour::findNearestNeighbour(int v)
{
	int nearestNeighbour = -1;
	int minDistance = INT_MAX;

	for (int i = 0; i < N; i++)
	{
		if (!visited[i] && matrix[v][i] < minDistance)
		{
			minDistance = matrix[v][i];
			nearestNeighbour = i;
		}
	}
	return nearestNeighbour;
}
//------------------------------------------------------------------------------------------------------------------------------------
void NearestNeighbour::printCurrentPathNN()
{
	for (int i = 0; i < currentPathNN.size(); i++)
	{
		cout << currentPathNN[i] << " ";
	}
	cout << "\n";
}