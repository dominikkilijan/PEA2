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
	float readPathFromFile(string);
	int getN(string);
	void runAlgorithm();

private:
	fstream file;
};

