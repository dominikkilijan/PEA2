#include "FileHandler.h"
#include <iostream>

using namespace std;

int choice;
int run = 1;
string filename = "nic";

int main()
{
    FileHandler fHandler;

    // menu wyswietlane ciagle
    while (run)
    {
        cout << "MENU:\n";;
        cout << "1. Wczytaj dane z pliku\n";
        cout << "2. Wygeneruj losowe dane\n";
        cout << "3. Wyswietl wczytane dane\n";
        cout << "4. Uruchom algorytm\n";
        cout << "5. Zakoncz\n";

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
            cout << "Ile wierzcholkow?\n";
            int N;
            cin >> N;
            cout << "Podaj nazwe pliku wraz z rozszerzeniem:\n";
            string newFilename;
            cin >> newFilename;

            fHandler.generate(N, newFilename);
        }
        break;
        case 3:
        {
            if (filename != "nic")
                fHandler.print(filename);
            else
                cout << "Wczytaj dane z pliku!\n";
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