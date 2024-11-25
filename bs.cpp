#include <iostream>
#include <SFML/Graphics.hpp>
#include <thread>
#include <chrono>

const int WINDOW_HEIGHT = 800;
const int WINDOW_WIDTH = 600;
const int ARR_SIZE = 50;

int arr[ARR_SIZE]; // Array to sort

// Fill the array with random values
void fill_array() {
    for (int i = 0; i < ARR_SIZE; i++) {
        arr[i] = rand() % 200 + 50; // Random heights for bars
    }
}

// Visualize the array in the window
void visualize(sf::RenderWindow& window, int currentIndex = -1) {
    window.clear();

    for (int i = 0; i < ARR_SIZE; i++) {
        sf::RectangleShape rect(sf::Vector2f(10, arr[i]));
        rect.setPosition(i * 12, WINDOW_HEIGHT - arr[i]);
        rect.setFillColor(i == currentIndex ? sf::Color::Red : sf::Color::Green);
        window.draw(rect);
    }

    window.display();
    std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Delay for visualization
}

// Insertion Sort Algorithm with Visualization
void insertion_sort(sf::RenderWindow& window) {
    std::cout << "Starting Insertion Sort...\n";
    for (int i = 1; i < ARR_SIZE; i++) {
        int key = arr[i];
        int j = i - 1;

        // Move elements greater than key to one position ahead
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
            visualize(window, j + 1); // Visualize each step
        }

        arr[j + 1] = key;
        visualize(window, i); // Visualize after placing the key
    }
    std::cout << "Insertion Sort Complete.\n";
}

// Main Function
int main() {
    std::cout << "Initializing SFML Window...\n";
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Insertion Sort Visualizer");
    std::cout << "Window Created Successfully.\n";

    srand(time(0)); // Seed for random numbers
    fill_array();   // Fill array with random values

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                std::cout << "Window Closed.\n";
            }
        }

        std::cout << "Running Sorting Visualization...\n";
        insertion_sort(window); // Run the sorting visualization
        break; // Exit after sorting
    }

    std::cout << "Program Finished.\n";
    return 0;
}