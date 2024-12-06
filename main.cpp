#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>


/*
Each function takes a pointer to the array containing numbers read from file
the functions will be called in main and a timer will be set to measure how
long it takes to sort or search the given array.
They will only output the first and last elements to verify that they sorted
the array properly.
The output will be removed in the final code.
*/


// Selection Sort
void selectionSort(std::vector<int> &arr) {
    int n = arr.size();

    for (int i = 0; i < n - 1; ++i) {

        // Assume the current position holds
        // the minimum element
        int min_idx = i;

        // Iterate through the unsorted portion
        // to find the actual minimum
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[min_idx]) {

                // Update min_idx if a smaller
                // element is found
                min_idx = j;
            }
        }

        // Move minimum element to its
        // correct position
        std::swap(arr[i], arr[min_idx]);
    }
}
// Bubble Sort
void bubbleSort(std::vector<int>& arr) {
    int n = arr.size();
    bool swapped;

    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }

        // If no two elements were swapped, then break
        if (!swapped)
            break;
    }
}

// Quick Sort algorithm and partition function needed for it.
int partition(std::vector<int>& arr, int low, int high) {

    // Choose the pivot
    int pivot = arr[high];

    // Index of smaller element and indicates
    // the right position of pivot found so far
    int i = low - 1;

    // Traverse arr[;ow..high] and move all smaller
    // elements on left side. Elements from low to
    // i are smaller after every iteration
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }

    // Move pivot after smaller elements and
    // return its position
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

// The QuickSort function implementation
void quickSort(std::vector<int>& arr, int low, int high) {

    if (low < high) {

        // pi is the partition return index of pivot
        int pi = partition(arr, low, high);

        // Recursion calls for smaller elements
        // and greater or equals elements
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Merge Sort
// Merges two subarrays of arr[].
// First subarray is arr[left..mid]
// Second subarray is arr[mid+1..right]
void merge(std::vector<int>& arr, int left,
                     int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temp vectors
    std::vector<int> L(n1), R(n2);

    // Copy data to temp vectors L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0;
    int k = left;

    // Merge the temp vectors back
    // into arr[left..right]
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[],
    // if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[],
    // if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// begin is for left index and end is right index
// of the sub-array of arr to be sorted
void mergeSort(std::vector<int>& arr, int left, int right)
{
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

// Linear Search
// Binary Search

// print array
void printArray(std::vector<int> &arr) {
    for (int &val : arr) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

int main() {
    int n = 1000000;

    std::vector<int>numbers;
    int num;

    std::ifstream file("random_numbers.txt");

    while (file >> num) {
        numbers.push_back(num);
    }

    file.close();

    std::cout << numbers.size() << std::endl;

    // start selection sort timer
    auto selectionStart = std::chrono::high_resolution_clock::now();

    // create new array for selection sort and pass into sort function
    std::vector<int> selectionSortVector = numbers;
    selectionSort(selectionSortVector);

    // stop selection sort timer and calculate time
    auto selectionStop = std::chrono::high_resolution_clock::now();
    auto selectionDuration = std::chrono::duration_cast<std::chrono::milliseconds>(
        selectionStop - selectionStart);

    // start bubble sort timer
    auto bubbleStart = std::chrono::high_resolution_clock::now();

    std::vector<int> bubbleSortVector = numbers;
    bubbleSort(bubbleSortVector);

    // stop bubble sort timer and calculate time
    auto bubbleStop = std::chrono::high_resolution_clock::now();
    auto bubbleDuration = std::chrono::duration_cast<std::chrono::milliseconds>(
        bubbleStop - bubbleStart);

    // start quick sort timer
    auto quickStart = std::chrono::high_resolution_clock::now();

    std::vector<int> quickSortVector = numbers;
    int quickSortSize = quickSortVector.size();
    quickSort(quickSortVector, 0, quickSortSize - 1);

    // stop bubble sort timer and calculate time
    auto quickStop = std::chrono::high_resolution_clock::now();
    auto quickDuration = std::chrono::duration_cast<std::chrono::milliseconds>(
        quickStop - quickStart);

    // start merge sort timer
    auto mergeStart = std::chrono::high_resolution_clock::now();

    // copy vector and run merge sort
    std::vector<int> mergeSortVector = numbers;
    mergeSort(mergeSortVector, 0, (mergeSortVector.size() - 1));

    // stop merge sort timer
    auto mergeStop = std::chrono::high_resolution_clock::now();
    auto mergeDuration = std::chrono::duration_cast<std::chrono::milliseconds>(
        mergeStop - mergeStart);

    std::cout << selectionDuration.count() << " milliseconds" << std::endl;
    std::cout << bubbleDuration.count() << " milliseconds" << std::endl;
    std::cout << quickDuration.count() << " milliseconds" << std::endl;
    std:: cout << mergeDuration.count() << " milliseconds" << std::endl;



    return 0;
}
