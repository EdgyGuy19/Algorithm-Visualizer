#include <iostream>
#include <ctime>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <thread>

using namespace std;

const int WINDOW_HEIGHT = 800;
const int WINDW_WIDTH = 600;

const int arrsize = 50;
int arr[arrsize];

void fill_array()
{
    for (int i = 0; i < arrsize; i++)
    {
        arr[i] = rand() % 100;
    }
}

void insertion_sort(sf::RenderWindow& window)
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

            window.clear();
            for (int k = 0; k < arrsize; k++)
            {
                sf::RectangleShape rect(sf::Vector2f(5, arr[k]));
                rect.setPosition(k * 8, WINDOW_HEIGHT - arr[k]);
                rect.setFillColor(sf::Color::Green);
                window.draw(rect);
            }
            window.display();
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Slow down for visualization
        }
    }
}

void selection_sort(sf::RenderWindow& window)
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

        window.clear();
        for (int k = 0; k < arrsize; k++)
        {
            sf::RectangleShape rect(sf::Vector2f(5, arr[k]));
            rect.setPosition(k * 8, WINDOW_HEIGHT - arr[k]);
            rect.setFillColor(sf::Color::Green);
            window.draw(rect);
        }
        window.display();
        std::this_thread::sleep_for(std::chrono::milliseconds(10)); // Slow down for visualization
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

void bubble_sort(sf::RenderWindow window)
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

            window.clear();
            for (int k = 0; k < arrsize; k++)
            {
                sf::RectangleShape rect(sf::Vector2f(5, arr[k]));
                rect.setPosition(k * 8, WINDOW_HEIGHT - arr[k]);
                rect.setFillColor(sf::Color::Green);
                window.draw(rect);
            }
            window.display();
            std::this_thread::sleep_for(std::chrono::milliseconds(10)); // Slow down for visualization
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

        fill_array();

        sf::RenderWindow window(sf::VideoMode(WINDOW_HEIGHT, WINDW_WIDTH), "My window");
        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            insertion_sort(window);
            break;
        }
        break;
    }
    case 's':
    {
        cout << "Original Array:\n";
        fill_array();
        print_array();

        cout << "\nTesting Selection Sort:\n";
        // selection_sort();
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
        // bubble_sort();
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