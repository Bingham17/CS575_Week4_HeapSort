#include <stdio.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
using namespace std;

/*
Name: Christopher Bingham
Email: cbingha2@binghamton.edu
Assignment: Week 4 - Heap Sort
*/


int parentNode(int index) {
    /*
    Returns the index of the parent node of the node at the given index.
    Parameters:
       - index <int>: The index of the node for which to find the parent.
    Returns:
        - <int>: The index of the parent node.
    */
    return (index - 1) / 2;
}

int leftChildNode(int index) {
    /*
    Returns the index of the left child node of the node at the given index.
    Parameters:
       - index <int>: The index of the node for which to find the left child.
    Returns:
        - <int>: The index of the left child node.
    */
    return (2 * index) + 1;
}

int rightChildNode(int index) {
    /*
    Returns the index of the right child node of the node at the given index.
    Parameters:
       - index <int>: The index of the node for which to find the right child.
    Returns:
        - <int>: The index of the right child node.
    */
    return (2 * index) + 2;
}

void maxHeapify(vector<int> &heapArray, int index, int heapSize) {
    /*
    Maintains the max heap property for the subtree rooted at the given index.
    Parameters:
       - heapArray <vector<int>>: The vector representing the heap.
       - index <int>: The index of the root of the subtree to be heapified.
       - heapSize <int>: The number of elements in the heap.
    Returns:
        - None
            - The vector is modified in place to maintain the max heap property.
    */
    int largestIndex = index;
    if( (leftChildNode(index) < heapSize) && (heapArray[leftChildNode(index)] > heapArray[largestIndex]) ) {
        largestIndex = leftChildNode(index);
    }
    if( (rightChildNode(index) < heapSize) && (heapArray[rightChildNode(index)] > heapArray[largestIndex]) ) {
        largestIndex = rightChildNode(index);
    }
    if (largestIndex != index){
        // swap(heapArray[index], heapArray[largestIndex]);
        int tempIndex = heapArray[index];
        heapArray[index] = heapArray[largestIndex];
        heapArray[largestIndex] = tempIndex;
        maxHeapify(heapArray, largestIndex, heapSize);
    } 
}

void buildMaxHeap(vector<int> &heapArray, int heapSize) {
    /*
    Builds a max heap from the given array.
    Parameters:
       - heapArray <vector<int>>: The vector representing the array to be converted into a max heap.
       - heapSize <int>: The number of elements in the heap.
    Returns:
        - None
            - Array is modified in place to represent a max heap.
    */
    for (int i = heapSize / 2; i >= 0; i--){
        maxHeapify(heapArray, i, heapSize);
    }
}

void heapSort(vector<int> &heapArray) {
    /*
    Sorts the elements of the heap array in ascending order using the heap sort algorithm.
    Parameters:
       - heapArray <vector<int>>: The vector representing the heap to be sorted.
    Returns:
        - None
            - Array is modified in place to represent the sorted array.
    */
    buildMaxHeap(heapArray, heapArray.size());

    int heapSize = heapArray.size();
    for (int i = heapSize - 1; i > 0; i--) {
        // swap(heapArray[0], heapArray[i]);
        int tempIndex = heapArray[0];
        heapArray[0] = heapArray[i];
        heapArray[i] = tempIndex;
        heapSize--;
        maxHeapify(heapArray, 0, heapSize);
    }
}

void printHeap(vector<int> &heapArray) {
    /*
    Prints the elements of the heap array to standard output.
    As according to the rules of heaps, the elements are printed in a level-order traversal manner.
    Parameters:
       - heapArray <vector<int>>: The vector representing the heap to be printed.
    Returns:
        - None
            - No need to return anything as the function prints directly to standard output.
    */
    for (int i = 0; i < heapArray.size(); i++){
        cout << heapArray[i] << endl;
    }
    return;
}

void buildArrayFromFile(ifstream &inputFile, vector<int> &arrayToBuild) {
    /*
    Reads integers from the input file and populates the provided vector with these integers.
    Parameters:
       - inputFile <ifstream>: The input file stream from which to read the integers.
       - arrayToBuild <vector<int>>: The vector to be populated with the integers read from the file.
    Returns:
        - None
            - The vector is modified in place to contain the integers read from the file.
    */
    int totalNumber;
    inputFile >> totalNumber;  // Read the total number of elements from the first line of the file
    for (int i = 0; i < totalNumber; ++i) {
        int num;
        inputFile >> num;
        arrayToBuild.push_back(num);
    }
    return;
}


int main(int argc, char *argv[]) {
    /*
    Main function to execute the heap sort algorithm.
    CommandLine Usage:
        - ./heapSort <input_file>
    Command line arguments:
        - argv[1]: The name of the input file containing the integers to be sorted.
        - If no command line argument is provided, the user will be prompted to enter the file name.
    Returns:
        - 0: Successful execution
        - 1: Error in opening the input file
    */

    //Read the input file and build the array to be sorted
    ifstream inputFile;
    if (argc != 2) {
        string fileName;
        cout << "Enter File Name:" << endl;
        cin >> fileName;
        inputFile.open(fileName);
        if (!inputFile) {
            cout << "Cannot Open File: " << fileName << endl;
            cout << "CommandLine Usage: ./heapSort <input_file>" << endl;
            return 1;
        }
    } else {
        inputFile.open(argv[1]);
        if (!inputFile) {
            cout << "Cannot Open File: " << argv[1] << endl;
            cout << "CommandLine Usage: ./heapSort <input_file>" << endl;
            return 1;
        }
    }

    vector<int> heapArray;
    // Build the array from the input file
    buildArrayFromFile(inputFile, heapArray);
    //Turn the array into a max heap
    // buildMaxHeap(heapArray, heapArray.size());
    //Perform Heap Sort on the max heap
    heapSort(heapArray);
    //Print the sorted array
    printHeap(heapArray);

    return 0;

}