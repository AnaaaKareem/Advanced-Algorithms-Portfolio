#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <chrono>
using namespace std;

int bubble_sort_count(int* arr, int n) {
    // Create Comparison Counter
    int count = 0;
    // Pass Through Array Based on It's Size
    for (int i = 0; i < n; i++) { 
        // Compare The Element of The Current Array With The Next Index
        for (int j = 0; j < n - 1 - i; j++) { 
            // Increment Comparison Counter
            count++; 
            // If Current Value is bigger than the next index's Value Perform A Swap Operation
            if (arr[j] > arr[j+1]) {
                // Swap Elements
                int temp = arr[j]; 
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
    // Return Comparison Count Number
    return count; 
}

int selection_sort_count(int* arr, int n) {
    // Create Comparison Counter
    int count = 0;
    // Select all positions in the array except the last index
    for (int i = 0; i < n - 1; i++) { 
        // Assume on each iteration the current index is has the minimum value
        int minIndex = i; 
        // Iterate over elements that are left to the current index searching for lowest value to swap
        for (int j = i + 1; j < n; j++) {
            // Increment Comparison Counter
            count++;
            // Update minIndex if a smaller element is found
            if (arr[j] < arr[minIndex]) {
                // Set new minimum index
                minIndex = j;
            }
        }
        // Swap Elements between current position and with the value set in the minIndex index 
        int temp = arr[minIndex];
        arr[minIndex] = arr[i];
        arr[i] = temp;
    }
    // Return Comparison Count Number
    return count;
}

int insertion_sort_count(int* arr, int n) {
    // Create Comparison Counter
    int count = 0;
    // Iterate over elements starting from the second element
    for (int i = 1; i < n; i++) {
        // Element to insert
        int key = arr[i]; 
        // Index of previous element
        int prev = i - 1;
        // Shift elements greater than key
        while (prev >= 0) {
            // Increment Comparison Counter
            count++;
            if (arr[prev] > key) {
                // Move element one position ahead
                arr[prev + 1] = arr[prev]; 
                prev--;
            } else {
                break;
            }
        }
        // Insert key at correct position
        arr[prev + 1] = key;
    }
    // Return Comparison Count Number
    return count;
}

// Test Bubble Sort comparison count and execution time
void testBubbleSort(int* arr, int size, const string& label) {
    // Create a copy of the input array
    int* arr_copy = new int[size];
    std::copy(arr, arr + size, arr_copy);

    cout << label << " Bubble Sort" << endl;
    auto start = chrono::high_resolution_clock::now();
    int comparisons = bubble_sort_count(arr_copy, size);
    auto end = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << "Bubble Sort Comparison Count: " << comparisons << endl;
    cout << "Time taken: " << duration.count() << " ms" << endl << endl;

    // Free the copied array
    delete[] arr_copy;
    arr_copy = nullptr;
}

// Test Selection Sort comparison count and execution time
void testSelectionSort(int* arr, int size, const string& label) {
    // Create a copy of the input array
    int* arr_copy = new int[size];
    std::copy(arr, arr + size, arr_copy);

    cout << label << " Selection Sort" << endl;
    auto start = chrono::high_resolution_clock::now();
    int comparisons = selection_sort_count(arr_copy, size);
    auto end = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << "Selection Sort Comparison Count: " << comparisons << endl;
    cout << "Time taken: " << duration.count() << " ms" << endl << endl;

    // Free the copied array
    delete[] arr_copy;
    arr_copy = nullptr;
}

// Test Insertion Sort comparison count and execution time
void testInsertionSort(int* arr, int size, const string& label) {
    // Create a copy of the input array
    int* arr_copy = new int[size];
    std::copy(arr, arr + size, arr_copy);

    cout << label << " Insertion Sort" << endl;
    auto start = chrono::high_resolution_clock::now();
    int comparisons = insertion_sort_count(arr_copy, size);
    auto end = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << "Insertion Sort Comparison Count: " << comparisons << endl;
    cout << "Time taken: " << duration.count() << " ms" << endl << endl;

    // Free the copied array
    delete[] arr_copy;
    arr_copy = nullptr;
}

// Test Comparisons
void test_comparisons() {
    for (int size = 1; size <= 30; size++) {
        cout << "---------- Test " << size << " ----------" << endl << endl;

        // Initialize array, sorted array and inversely sorted array
        int* arr = new int[size];
        int* sorted = new int[size];
        int* inverse = new int[size];

        // Generate random values
        for (int j = 0; j < size; j++) {
            arr[j] = rand() % 1000;
            sorted[j] = arr[j];
            inverse[j] = arr[j];
        }

        // Sort arrays
        sort(sorted, sorted + size);
        sort(inverse, inverse + size, greater<int>());

        // Print scattered array
        cout << "Array: ";
        for (int j = 0; j < size; j++)
            cout << arr[j] << " ";
        cout << endl;

        // Print ascending-sorted array
        cout << "Sorted: ";
        for (int j = 0; j < size; j++)
            cout << sorted[j] << " ";
        cout << endl;

        // Print descending-sorted array
        cout << "Inversely Sorted: ";
        for (int j = 0; j < size; j++)
            cout << inverse[j] << " ";
        cout << endl << endl;

        // Test Bubble Sort for all three arrays
        testBubbleSort(arr, size, "scattered");
        testBubbleSort(sorted, size, "sorted");
        testBubbleSort(inverse, size, "inversely sorted");

        // Test Insertion Sort for all three arrays
        testInsertionSort(arr, size, "scattered");
        testInsertionSort(sorted, size, "sorted");
        testInsertionSort(inverse, size, "inversely sorted");

        // Test Selection Sort for all three arrays
        testSelectionSort(arr, size, "scattered");
        testSelectionSort(sorted, size, "sorted");
        testSelectionSort(inverse, size, "inversely sorted");

        // Delete array from memory
        delete[] arr;
        arr = nullptr;
        delete[] sorted;
        sorted = nullptr;
        delete[] inverse;
        inverse = nullptr;
    }
}


int main() {
    test_comparisons();

    return 0;
}