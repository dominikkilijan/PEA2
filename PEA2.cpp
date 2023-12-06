#include "FileHandler.h"
#include <iostream>

using namespace std;

int choice;
int run = 1;
string filename = "nic";
int stopTime = 100;
float aTemp = 0.95;


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
        //choice = 4;
        system("CLS"); // czyszczenie ekranu
        switch (choice)
        {
        case 1:
        {
            cout << "Podaj nazwe pliku do wyswietlenia:\n";
            cin >> filename;
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
                fHandler.openFile(filename);
            else
                cout << "Wczytaj dane z pliku!\n";

        }
        break;
        case 5:
            cout << "Koniec programu\n";
            run = 0;
            break;

        default:
            cout << "Nieprawidlowy numer!\n";
            break;
        }
    }
}