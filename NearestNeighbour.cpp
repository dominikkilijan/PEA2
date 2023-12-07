#include "NearestNeighbour.h"
#include <iostream>
#include <vector>

using namespace std;

//------------------------------------------------------------------------------------------------------------------------------------
NearestNeighbour::NearestNeighbour(int n, int** m)
{
	matrix = m;
	N = n;

	visited.reserve(N);
}
//------------------------------------------------------------------------------------------------------------------------------------
NearestNeighbour::~NearestNeighbour()
{
	matrix = nullptr;
}
//------------------------------------------------------------------------------------------------------------------------------------
void NearestNeighbour::findNearestNeighbourPath(vector<int>& currentPath)
{
	currentPath.clear();
	int start = 0;
	currentPath.push_back(start);
	visited[start] = true;

	for (int i = 0; i < N; i++)
	{
		int nearestNeighbour = findNearestNeighbour(start);
		currentPath.push_back(nearestNeighbour);
		visited[nearestNeighbour] = true;
		start = nearestNeighbour;
	}
	currentPath.push_back(currentPath.front());
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