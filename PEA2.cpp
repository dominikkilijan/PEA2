﻿#include "FileHandler.h"
#include "AdjacencyMatrix.h"
#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

int choice;
int run = 1;
string filename = "nic";
string filename2;
int stopTime = 15;
double alpha = 0.999;
int** adMatrix;
int N;


int main()
{
    FileHandler fHandler;

    // menu wyswietlane ciagle
    while (run)
    {
        cout << "MENU:\n";;
        cout << "1. Wczytaj dane z pliku\n";
        cout << "2. Wprowadz kryterium stopu\n";
        cout << "3. Ustaw wspolczynnik zmiany temperatury\n";
        cout << "4. Uruchom algorytm\n";
        cout << "5. Zapisz sciezke do pliku\n";
        cout << "6. Oblicz sciezke z zapisanego pliku\n";
        cout << "7. Zakoncz\n";

        cin >> choice;
        //choice = 1;
        system("CLS"); // czyszczenie ekranu
        switch (choice)
        {
        case 1:
        {
            cout << "Podaj nazwe pliku:\n";
            //cin >> filename;
            filename = "br17.atsp";
            N = fHandler.getN(filename);

            if (filename != "nic")
                adMatrix = fHandler.openFile(filename);
            else
                cout << "Wczytaj dane z pliku!\n";
            choice = 4;
        }
        break;
        case 2:
        {
            cout << "Po ilu sekundach zakonczyc dzialanie?\n";
            cin >> stopTime;
        }
        break;
        case 3:
        {
            cout << "Wspolczynnik zmiany temperatury:\n";
            cin >> alpha;
        }
        break;
        case 4:
        {
            if (filename != "nic")
                fHandler.runAlgorithm(stopTime, alpha);
            else
                cout << "Wczytaj dane z pliku!\n";

        }
        break;
        case 5:
        {
            if (filename != "nic")
            {
                cout << "Podaj nazwe pliku:\n";
                cin >> filename2;
                fHandler.renameFile("temp.txt", filename2);
            }
            else
                cout << "Wczytaj dane z pliku!\n";
        }
        break;
        case 6:
        {
            

            if (filename != "nic")
            {
                cout << "Podaj nazwe pliku:\n";
                //cin >> filename2;
                filename2 = "temp.txt";
                double fileSum = fHandler.readPathFromFile(filename2);
                cout << "Waga = " << fileSum << "\n";
            }
            else
                cout << "Wczytaj dane z pliku!\n";
            
        }
        break;
        case 7:
        {
            cout << "Koniec programu\n";
            run = 0;
        }
        break;
        case 8:
        {
            for (int i = 0; i < N; i++)
            {
                for (int j = 0; j < N; j++)
                {
                    cout << adMatrix[i][j] << "\t";
                }
                cout << "\n";
            }
        }
        default:
            cout << "Nieprawidlowy numer!\n";
            break;
        }
    }
}