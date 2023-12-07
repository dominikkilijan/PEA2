#include "FileHandler.h"
#include "AdjacencyMatrix.h"
#include <iostream>
#include <vector>

using namespace std;

int choice;
int run = 1;
string filename = "nic";
int stopTime = 100;
float aTemp = 0.95;
int** adMatrix;
int N;


int main()
{
    FileHandler fHandler;

    // menu wyswietlane ciagle
    while (run)
    {
        cout << "MENU:\n";;
        cout << "1. Wybierz plik\n";
        cout << "2. Wprowadz kryterium stopu\n";
        cout << "3. Ustaw wspolczynnik zmiany temperatury\n";
        cout << "4. Uruchom algorytm\n";
        cout << "5. Zapisz sciezke do pliku\n";
        cout << "6. Oblicz sciezke z zapisanego pliku\n";
        cout << "7. Zakoncz\n";

        cin >> choice;
        //choice = 4;
        system("CLS"); // czyszczenie ekranu
        switch (choice)
        {
        case 1:
        {
            cout << "Podaj nazwe pliku:\n";
            //cin >> filename;
            filename = "tsp_5.txt";
            N = fHandler.getN(filename);
            cout << "N = fHandler.getN(filename) = " << N << endl;

            if (filename != "nic")
                adMatrix = fHandler.openFile(filename);
            else
                cout << "Wczytaj dane z pliku!\n";
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
            cin >> aTemp;
        }
        break;
        case 4:
        {
            if (filename != "nic")
                fHandler.runAlgorithm();
            else
                cout << "Wczytaj dane z pliku!\n";

        }
        break;
        case 5:
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
        break;
        case 6:
        {
            cout << "adMatrix = " << adMatrix << endl;
        }
        break;
        case 7:
        {
            cout << "Koniec programu\n";
            run = 0;
            // czyszczenie adMatrix
            if (adMatrix != nullptr)
            {
                for (int i = 0; i < N; i++)
                {
                    delete[] adMatrix[i];
                }
                delete[] adMatrix;
                adMatrix = nullptr;
            }
        }
        break;
        default:
            cout << "Nieprawidlowy numer!\n";
            break;
        }
    }
}