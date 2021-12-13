// Zaimplementuj sortowanie przez zliczanie oraz sortowanie przez kopcowanie.

#include <iostream> // cout
#include <fstream> // Funkcje do obsługi plików tekstowych.
#include <chrono> // Funkcje do pomiaru czasu wykonania funkcji.

#define TIME_TESTS true // true - jeśli chcemy wykonać porównanie algorytmów dla ich czasu wykonania, false - jeśli nie.

using namespace std;

void loadDataFromFile(string fileName, int array[], int size); // Wczytywanie danych z pliku tekstowego.
void saveDataToFile(string fileName, int array[], int size); // Zapisywanie danych do pliku tekstowego.

int getRandomNumber(int min, int max); // Generowanie liczby całkowitej z danego przedziału.
void generateRandomData(int array[], int size, int max); // Uzupełnianie tablicy array losowymi liczbami całkowitymi z przedziału 0-max.

void heapify(int array[], int size, int i); // Budowanie kopca.
void heapSort(int array[], int size); // Sortowanie przez kopcowanie.

void countSort(int array[], int size); // Sortowanie przez zliczanie.

#if TIME_TESTS == true
    void timeTests();
#endif // TIME_TESTS

const int N = 5000; // Stała przechowująca największą możliwą wartość sortowanego elementu.

int main()
{
    #if TIME_TESTS == true
        timeTests();
    #endif // TIME_TESTS

    cout << "Podaj liczbe elementow, ktore po wylosowaniu zostana posortowane." << endl;

    int size;
    cin >> size;

    if (size > 1)
    {
        int array[size], heapArray[size], countArray[size], i = 0;

        // Uzupełniamy tablicę array losowymi liczbami.
        generateRandomData(array, size, getRandomNumber(0, 50));

        // Kopiujemy zawartość tablicy array do tablic heapArray oraz countArray.
        copy(array, array + size, heapArray);
        copy(array, array + size, countArray);

        // Sortujemy wartości dwoma algorytmami.
        heapSort(heapArray, size);
        countSort(countArray, size);

        // Wypisujemy wartości przed posortowaniem oraz po posortowaniu.
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

#if TIME_TESTS == true
    void timeTests()
    {
        fstream file;
        file.open("results/tests.txt", ios::out);

        for (int i = 0, c, size, max; i < 3; i++)
        {
            // i: 0 - przypadek oczekiwany, 1 - przypadek optymistyczny, 2 - przypadek pesymistyczny

            file << "Przypadek " << (i == 2 ? "pesymistyczny" : i ? "optymistyczny" : "oczekiwany") << endl;
            max = (i == 2 ? N : i ? 1 : 100);

            for (c = 0, size = 1000; c < 9; c++)
            {
                int heapArray[size], countArray[size];

                generateRandomData(heapArray, size, max);
                copy(heapArray, heapArray + size, countArray);

                // Dla sortowania przez kopcowanie
                auto start = chrono::steady_clock::now();

                heapSort(heapArray, size);
                file << "heapSort: " << size << " liczb, " << chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - start).count() << endl;

                // Dla sortowania przez zliczanie
                start = chrono::steady_clock::now();

                countSort(countArray, size);
                file << "countSort: " << size << " liczb, " << chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - start).count() << endl << endl;

                size *= 2;
            }
            file << endl;
        }

        file.close();
        cout << "Wykonano testy zlozonosci obliczeniowej algorytmow sortowania. Wyniki znajdziesz w results/tests.txt." << endl;
    }
#endif // TIME_TESTS
