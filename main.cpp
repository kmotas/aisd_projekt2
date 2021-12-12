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

void countSort(int array[], int size); // Sortowanie przez zliczanie.

const int N = 1000; // Stała przechowująca największą możliwą wartość sortowanego elementu.

int main()
{
    cout << "Podaj liczbe elementow, ktore po wylosowaniu zostana posortowane." << endl;

    int size;
    cin >> size;

    if (size > 1)
    {
        int array[size], i = 0;
        generateRandomData(array, size, getRandomNumber(0, 50));

        int heapArray[size], countArray[size];

        copy(array, array + size, heapArray);
        copy(array, array + size, countArray);

        heapSort(heapArray, size);
        countSort(countArray, size);

        cout << endl << "Przed posortowaniem:";
        for (; i < size; i++)
        {
            cout << " " << array[i];
        }

        cout << endl << "Sortowanie przez kopcowanie:";
        for (i = 0; i < size; i++)
        {
            cout << " " << heapArray[i];
        }

        cout << endl << "Sortowanie przez zliczanie:";
        for (i = 0; i < size; i++)
        {
            cout << " " << countArray[i];
        }
    }
    else
    {
        cout << "Liczba elementow musi byc wieksza od 1!" << endl;
    }

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

void countSort(int array[], int size)
{
    int
        i,

        // Tablica, która będzie przechowywała posortowane liczby.
        *output = new int[size],

        // Tablica, która będzie przechowywała liczbę wystąpień każdego z elementów.
        count[N + 1];

    // Iniciujemy tablicę count.
    for (i = 0; i <= N; i++)
    {
        count[i] = 0;
    }

    // Liczymy liczbę wystąpień każdego z elementów.
    for (i = 0; i < size; i++)
    {
        ++count[array[i]];
    }

    // Zmieniamy count[i], tak żeby zawierało aktualną pozycję tej liczby w tablicy output.
    for (i = 1; i <= N; i++)
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

    // Usuwamy dynamiczną tablicę.
    delete [] output;
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
