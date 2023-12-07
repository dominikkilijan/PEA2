#pragma once
#include <iostream>
#include <fstream>

using namespace std;

class FileHandler
{
public:
	int** openFile(string);
	void generate(int, string);
	void print(string);
	void writePathToFile(string, int, int*);
	double readPathFromFile(string);
	int getN(string);
	void runAlgorithm(int, double);
	void renameFile(string, string);

private:
	fstream file;
	int** matrix = nullptr;
};

