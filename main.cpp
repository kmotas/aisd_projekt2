// Zaimplementuj sortowanie przez zliczanie oraz sortowanie przez kopcowanie.

#include <iostream> // cout
#include <fstream> // Funkcje do obsługi plików tekstowych.
#include <time.h> // clock

using namespace std;

void loadDataFromFile(string fileName, int array[], int size); // Wczytywanie danych z pliku tekstowego.
void saveDataToFile(string fileName, int array[], int size); // Zapisywanie danych do pliku tekstowego.

int getRandomNumber(int min, int max); // Generowanie liczby całkowitej z danego przedziału.
void generateRandomData(int array[], int size, int max); // Uzupełnianie tablicy array losowymi liczbami całkowitymi z przedziału 0-max.

void heapify(int array[], int size, int i); // Budowanie kopca.
void heapSort(int array[], int size); // Sortowanie przez kopcowanie.

int getMax(int array[], int size); // Zwraca największą wartość w tablicy.
void countSort(int array[], int size); // Sortowanie przez zliczanie.

int main()
{
    return 0;
}

void heapify(int array[], int size, int i)
{
    int
        largest = i,
        l = 2 * i + 1,
        r = l + 1;

    if (l < size && array[l] > array[largest])
    {
        largest = l;
    }

    if (r < size && array[r] > array[largest])
    {
        largest = r;
    }

    if (largest != i)
    {
        swap(array[i], array[largest]);
        heapify(array, size, largest);
    }
}

void heapSort(int array[], int size)
{
    for (int i = size / 2 - 1; i >= 0; i--)
    {
        heapify(array, size, i);
    }

    for (int i = size - 1; i > 0; i--)
    {
        swap(array[0], array[i]);
        heapify(array, i, 0);
    }
}

int getMax(int array[], int size)
{
    int max = array[0];

    for (int i = 1; i < size; i++)
    {
        if (array[i] > max)
        {
            max = array[i];
        }
    }

    return max;
}

void countSort(int array[], int size)
{
    int
        i,

        // Tablica, która będzie przechowywała posortowane liczby.
        *output = new int[size],

        // Zmienna przechowująca największą wartość w array.
        max = getMax(array, size),

        // Tablica, która będzie przechowywała liczbę wystąpień każdego z elementów.
        *count = new int[max + 1];

    // Iniciujemy tablicę count.
    for (i = 0; i <= max; i++)
    {
        count[i] = 0;
    }

    // Liczymy liczbę wystąpień każdego z elementów.
    for (i = 0; i < size; i++)
    {
        ++count[array[i]];
    }

    // Zmieniamy count[i], tak żeby zawierało aktualną pozycję tej liczby w tablicy output.
    for (i = 1; i <= max; i++)
    {
        count[i] += count[i - 1];
    }

    // Uzupełniamy tablicę output.
    for (i = 0; i < size; i++)
    {
        output[count[array[i]] - 1] = array[i];
        --count[array[i]];
    }

    // Kopiujemy posortowane wartości z tablicy output do array.
    for (i = 0; i < size; i++)
    {
        array[i] = output[i];
    }

    // Usuwamy dynamiczne tablice.
    delete [] output;
    delete [] count;
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
