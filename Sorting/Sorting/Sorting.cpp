#include <iostream>
using namespace std;

void bubbleSort(int* a, int length)
{
    bool swapped = true;
    for (int i = 0;
        i < length && swapped;
        i++)
    {
        swapped = false;
        for (int j = 1; j < length - i; j++)
        {
            if (a[j] < a[j - 1])
            {
                swapped = true;
                int temp = a[j];
                a[j] = a[j - 1];
                a[j - 1] = temp;
            }
        }
    }
}

void selectionSort(int* a, int length)
{
    for (int i = 0; i < length - 1; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < length; j++)
        {
            if (a[j] < a[minIndex])
            {
                minIndex = j;
            }
        }
        int temp = a[minIndex];
        a[minIndex] = a[i];
        a[i] = temp;
    }
}

//void insertionSort(int* a, int length)
//{
//    for (int i = 1; i < length; i++)
//    {
//        int n = a[i];
//
//        for (int j = i - 1;
//            j >= 0 && n < a[j];
//            j--)
//        {
//            a[j + 1] = a[j];
//            a[j] = n;
//        }
//    }
//}

template <typename T>
void insertionSort(T* a, int length)
{
    for (int i = 1; i < length; i++)
    {
        T n = a[i];

        for (int j = i - 1;
            j >= 0 && n < a[j];
            j--)
        {
            a[j + 1] = a[j];
            a[j] = n;
        }
    }
}

template <typename T, typename C>
void insertionSort(T* a, int length, C comp)
{
    for (int i = 1; i < length; i++)
    {
        T n = a[i];

        for (int j = i - 1;
            j >= 0 && comp(n, a[j]);
            j--)
        {
            a[j + 1] = a[j];
            a[j] = n;
        }
    }
}

template <typename T, typename C>
void quickSort(T* a, int length, C comp)
{
    if (length > 1) // Implicit base case: 1 element or less
    {
        // Choose a pivot element
        int pivotIndex = length / 2;
        T pivot = a[pivotIndex];

        // Set the pivot aside
        a[pivotIndex] = a[0];
        a[0] = pivot;

        // Partition the list into a "big bag" and a "small bag"
        int smallBagLength = 0;

        // Scan through the list
        for (int i = 1; i < length; i++)
        {
            if (comp(a[i], pivot)) // Is a[i] smaller than the pivot?
            {
                // Element doesn't belong in th "big bag"
                // Swap with the first element in the "big bag"
                T tmp = a[smallBagLength + 1];
                a[smallBagLength + 1] = a[i];
                a[i] = tmp;

                // Update size of small bag
                smallBagLength++;
            }
        }

        // Swap the pivot with the last element in the "small bag"
        a[0] = a[smallBagLength];
        a[smallBagLength] = pivot;

        // Recursively sort the two unsorted "bags"
        quickSort(a, smallBagLength, comp);
        quickSort(&a[smallBagLength + 1], length - smallBagLength - 1, comp);
    }
}

template <typename T>
bool naturalOrder(T t1, T t2)
{
    return t1 < t2;
}

template <typename T>
bool reverseOrder(T t1, T t2)
{
    return t1 > t2;
}

int main()
{
    int numsA[20];
    int numsB[20];
    int numsC[20];

    for (int i = 0; i < 20; i++)
    {
        int r = rand() % 100;
        numsA[i] = r;
        numsB[i] = r;
        numsC[i] = r;
    }

    for (int n : numsA)
    {
        cout << n << ' ';
    }
    cout << endl;

    bubbleSort(numsA, 20);

    for (int n : numsA)
    {
        cout << n << ' ';
    }
    cout << endl;

    for (int n : numsB)
    {
        cout << n << ' ';
    }
    cout << endl;

    selectionSort(numsB, 20);

    for (int n : numsB)
    {
        cout << n << ' ';
    }
    cout << endl;

    for (int n : numsC)
    {
        cout << n << ' ';
    }
    cout << endl;

    insertionSort(numsC, 20);

    for (int n : numsC)
    {
        cout << n << ' ';
    }
    cout << endl;

    double doubleArray[20];

    for (int i = 0; i < 20; i++)
    {
        double r = 0.001 * (rand() % 1001);
        doubleArray[i] = r;
    }

    for (double n : doubleArray)
    {
        cout << n << ' ';
    }
    cout << endl;

    insertionSort(doubleArray, 20);

    for (double n : doubleArray)
    {
        cout << n << ' ';
    }
    cout << endl;

    int myInts[20];

    // initialize myInts
    for (int i = 0; i < 20; i++)
    {
        int r = rand() % 100;
        myInts[i] = r;
    }

    for (int n : myInts)
    {
        cout << n << ' ';
    }
    cout << endl;

    // sort ascending
    insertionSort(myInts, 20, &naturalOrder<int>);

    for (int n : myInts)
    {
        cout << n << ' ';
    }
    cout << endl;

    // sort descending
    insertionSort(myInts, 20, &reverseOrder<int>);

    for (int n : myInts)
    {
        cout << n << ' ';
    }
    cout << endl;

    // initialize myInts
    for (int i = 0; i < 20; i++)
    {
        int r = rand() % 100;
        myInts[i] = r;
    }

    for (int n : myInts)
    {
        cout << n << ' ';
    }
    cout << endl;

    // sort ascending
    quickSort(myInts, 20, &naturalOrder<int>);

    for (int n : myInts)
    {
        cout << n << ' ';
    }
    cout << endl;

    // sort descending
    quickSort(myInts, 20, &reverseOrder<int>);

    for (int n : myInts)
    {
        cout << n << ' ';
    }
    cout << endl;

    system("pause");
    return 0;
}