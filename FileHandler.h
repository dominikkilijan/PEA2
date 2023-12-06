#pragma once
#include <iostream>
#include <fstream>

using namespace std;

class FileHandler
{
public:
	void openFile(string);
	void generate(int, string);
	void print(string);

private:
	fstream file;
};

