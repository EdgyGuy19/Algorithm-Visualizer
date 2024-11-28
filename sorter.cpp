#include <iostream>
#include <ctime>
#include <algorithm>
#include <unistd.h>
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
        arr[i] = rand() % 200 + 50;
    }
}

void visualize(sf::RenderWindow &window, int pivotIndex = -1, int currentIndex = -1)
{
    window.clear();
    for (int i = 0; i < arrsize; i++)
    {
        sf::RectangleShape rect(sf::Vector2f(10, arr[i]));
        rect.setPosition(i * 12, WINDOW_HEIGHT - arr[i]);
        if (i == pivotIndex)
            rect.setFillColor(sf::Color::Blue); 
        else if (i == currentIndex)
            rect.setFillColor(sf::Color::Yellow);  
        else
            rect.setFillColor(sf::Color::Green);
        window.draw(rect);
    }
    window.display();
    std::this_thread::sleep_for(std::chrono::milliseconds(50));  // Adjust as necessary

}  


void insertion_sort(sf::RenderWindow &window)
{
    for (int i = 1; i < arrsize; i++)
    {
        int key = arr[i];
        int j = i - 1;

        
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
            visualize(window, j + 1); 
        }

        arr[j + 1] = key;
        visualize(window, i); 
    }
}

void selection_sort(sf::RenderWindow &window)
{
    for (int i = 0; i < arrsize; i++)
    {
        for (int j = i; j < arrsize; j++)
        {
            if (arr[j] < arr[i])
            {
                swap(arr[j], arr[i]);
                visualize(window, j);
            }
        }
        visualize(window, i);
    }
}

void merge(int array[], int left, int half, int right, sf::RenderWindow &window)
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
            visualize(window,newindex);
        }
        else
        {
            temparr[newindex++] = array[index2++];
            visualize(window,newindex);
        }
    }
    while (index1 <= half)
    {
        temparr[newindex++] = array[index1++];
        visualize(window, newindex);
    }
    while (index2 <= right)
    {
        temparr[newindex++] = array[index2++];
        visualize(window, newindex);
    }
    for (int i = 0; i < right - left + 1; i++)
    { 
        array[left + i] = temparr[i];
        visualize(window, left + i);
    }
}

void merge_sort(int array[], int left, int right, sf::RenderWindow &window)
{
    if (left >= right)
    {
        return;
    }

    int half = int((left + right) / 2);

    merge_sort(array, left, half,window);
    merge_sort(array, half + 1, right,window);
    merge(array, left, half, right, window);
}

void bubble_sort(sf::RenderWindow &window)
{
    for (int i = 0; i < arrsize - 1; i++)
    {
        for (int j = 0; j < arrsize - 1 - i; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j+1]);
                visualize(window, j + 1);
            }
        }
        visualize(window, i);
    }
}

int partition(int array[], int left, int right, sf::RenderWindow &window)
{
    int pivotvalue = array[right];
    int pivotindex = left;
    

    visualize(window, right); 
    
    for (int i = left; i < right; i++)
    {
        if (array[i] <= pivotvalue)
        {
            swap(array[i], array[pivotindex]);
            pivotindex++;
            visualize(window, pivotindex, i); 
        }
    }

 
    swap(array[pivotindex], array[right]);
    visualize(window, pivotindex);  

    return pivotindex;
}



void quick_sort(int array[], int left, int right, sf::RenderWindow &window)
{
    if (left >= right)
    {
        return;
    }
    int pivot = partition(array, left, right, window);
    quick_sort(array, left, pivot - 1, window);
    quick_sort(array, pivot + 1, right, window);
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
    sf::RenderWindow window(sf::VideoMode(WINDW_WIDTH, WINDOW_HEIGHT), "Sorting Visualizer");

    srand(time(0));
    fill_array();

    char input;

    cout << "Choose a sorting algorithm: \n";
    cout << "1. Insertion Sort\n";
    cout << "2. Selection Sort\n";
    cout << "3. Buble Sort\n";
    cout << "4. Merge Sort\n";
    cout << "5. Quick Sort\n";

    cin >> input;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        switch (input)
        {
        case '1':
            insertion_sort(window);
            break;

        case '2':
            selection_sort(window);
            break;

        case '3':
            bubble_sort(window);
            break;

        case '4':
            merge_sort(arr, 0, arrsize - 1, window);
            break;

        case '5':
            quick_sort(arr, 0, arrsize - 1, window);
            break;    
        
        default:
            break;
        }
        break;
    }
    return 0;
}