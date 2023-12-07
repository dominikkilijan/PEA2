#include "NearestNeighbour.h"
#include <iostream>
#include <vector>

using namespace std;

//------------------------------------------------------------------------------------------------------------------------------------
NearestNeighbour::NearestNeighbour(int n, int** m, vector<int>& path)
{
	matrix = m;
	N = n;
	currentPath = path;
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
	currentPath.emplace_back(start);
	visited[start] = true;

	for (int i = 0; i < N-1; i++)
	{
		int nearestNeighbour = findNearestNeighbour(start);
		currentPath.emplace_back(nearestNeighbour);
		visited[nearestNeighbour] = true;
		start = nearestNeighbour;
		printCurrentPath();
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
void NearestNeighbour::printCurrentPath()
{
	for (int city : currentPath) {
		std::cout << city << " ";
	}
	std::cout << "\n";
}