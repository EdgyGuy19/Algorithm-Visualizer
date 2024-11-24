#include <iostream>
#include <ctime>     // For srand and time
#include <algorithm> // For std::copy
#include <SFML/Graphics.hpp>

using namespace std;

const int arrsize = 150;
int arr[arrsize];

void fill_array()
{
    for (int i = 0; i < arrsize; i++)
    {
        arr[i] = rand() % 100;
    }
}

void insertion_sort()
{
    for (int i = 1; i < arrsize; i++)
    {
        int j = i;
        while (j > 0 && arr[j] > arr[j - 1])
        {
            int temp = arr[j];
            arr[j] = arr[j - 1];
            arr[j - 1] = temp;
            j--;
        }
    }
}

void selection_sort()
{
    for (int i = 0; i < arrsize - 1; i++)
    {
        int min = i;
        for (int j = i + 1; j < arrsize; j++)
        {
            if (arr[j] < arr[min])
            {
                min = j;
            }
        }
        int temp = arr[i];
        arr[i] = arr[min];
        arr[min] = temp;
    }
}

void merge(int array[], int left, int half, int right)
{
    int temparr[right - left + 1];
    int index1 = left;
    int index2 = half + 1;
    int newindex = 0;

    while (index1 <= half && index2 <= right)
    {
        if (array[index1] < array[index2])
        {
            temparr[newindex++] = array[index1++];
        }
        else
        {
            temparr[newindex++] = array[index2++];
        }
    }
    while (index1 <= half)
    {
        temparr[newindex++] = array[index1++];
    }
    while (index2 <= right)
    {
        temparr[newindex++] = array[index2++];
    }
    for (int i = 0; i < right - left + 1; i++)
    { // maybe do left - right instead if gives an error or smth like that
        array[left + i] = temparr[i];
    }
}

void merge_sort(int array[], int left, int right)
{
    if (left >= right)
    {
        return;
    }

    int half = int((left + right) / 2);

    merge_sort(array, left, half);
    merge_sort(array, half + 1, right);
    merge(array, left, half, right);
}

void bubble_sort()
{
    for (int i = 0; i < arrsize - 1; i++)
    {
        for (int j = 0; j < arrsize - 1 - i; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int partition(int array[], int left, int right)
{
    int pivotvalue = array[right];
    int pivotindex = left;
    for (int i = left; i < right; i++)
    {
        if (array[i] <= pivotvalue)
        {
            int temp = array[i];
            array[i] = array[pivotindex];
            array[pivotindex] = temp;
            pivotindex++;
        }
    }
    int temp = array[pivotindex];
    array[pivotindex] = array[right];
    array[right] = temp;

    return pivotindex;
}

void quick_sort(int array[], int left, int right)
{
    if (left >= right)
    {
        return;
    }
    int pivot = partition(array, left, right);
    quick_sort(array, left, pivot - 1);
    quick_sort(array, pivot + 1, right);
}

void print_array()
{
    for (int i = 0; i < arrsize; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main()
{
    char input;
    cin >> input;

    srand(time(0)); // Seed the random number generator

    switch (input)
    {
    case 'i':
    {
        cout << "Original Array:\n";
        fill_array();
        print_array();

        // Test Insertion Sort

        cout << "\nTesting Insertion Sort:\n";
        insertion_sort();
        print_array();
        break;
    }
    case 's':
    {
        cout << "Original Array:\n";
        fill_array();
        print_array();

        cout << "\nTesting Selection Sort:\n";
        selection_sort();
        print_array(); // Test Selection Sort
        break;
    }

    case 'm':
    {
        cout << "Original Array:\n";
        fill_array();
        print_array();

        // Test Merge Sort
        cout << "\nTesting Merge Sort:\n";
        merge_sort(arr, 0, arrsize - 1);
        print_array();
        break;
    }

    case 'b':
    {
        cout << "Original Array:\n";
        fill_array();
        print_array();

        cout << "\nTesting Bubble Sort:\n";
        bubble_sort();
        print_array(); // Test Bubble Sort
        break;
    }
    case 'q':
    {
        cout << "Original Array:\n";
        fill_array();
        print_array();

        // Test Quick Sort
        cout << "\nTesting Quick Sort:\n";
        quick_sort(arr, 0, arrsize - 1);
        print_array();
    }
    default:
    {
        break;
    }
    }

    return 0;
}