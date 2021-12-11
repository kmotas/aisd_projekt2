// Zaimplementuj sortowanie przez zliczanie oraz sortowanie przez kopcowanie.

#include <iostream> // cout
#include <fstream> // Funkcje do obsługi plików tekstowych.
#include <cstdlib> // rand, srand
#include <time.h> // clock

using namespace std;

void loadDataFromFile(string fileName, int array[], int size); // Wczytywanie danych z pliku tekstowego.
void saveDataToFile(string fileName, int array[], int size); // Zapisywanie danych do pliku tekstowego.

int getRandomNumber(int min, int max); // Generowanie liczby całkowitej z danego przedziału.
void generateRandomData(int array[], int size, int max); // Uzupełnianie tablicy array losowymi liczbami całkowitymi z przedziału 0-max.

int main()
{
    return 0;
}

void loadDataFromFile(string fileName, int array[], int size)
{
    ifstream file(fileName, fstream::in);

    if (file.good()) // W przypadku, gdy plik nie istnieje, program może przestać się wykonywać.
    {
        int i = 0;
        while (!file.eof())
        {
            file >> array[i];

            if (++i >= size)
            {
                // Przeciwdziałamy ewentualnemu przeciążeniu array.
                break;
            }
        }
        file.close();
    }
    else
    {
        cout << "Plik " << fileName << " nie istnieje!" << endl;
    }
}

void saveDataToFile(string fileName, int array[], int size)
{
    fstream file;
    file.open(fileName, ios::out);

    for (int i = 0; i < size; i++)
    {
        file << array[i] << " ";
    }

    file.close();
}

int getRandomNumber(int min, int max)
{
    static bool firstExecution = true;

    if (firstExecution) // Punkt startowy dla mechanizmu generującego liczby pseudolosowe ustawiamy tylko raz.
    {
        srand((unsigned int)time(NULL));
        firstExecution = false;
    }

    return min + rand() % (max + 1 - min);
}

void generateRandomData(int array[], int size, int max)
{
    for (int i = 0; i < size; i++)
    {
        array[i] = getRandomNumber(0, max);
    }
}
