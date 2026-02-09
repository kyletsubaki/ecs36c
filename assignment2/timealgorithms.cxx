#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <chrono>
#include "json.hpp"
#include "insertionsort.h"
#include "mergesort.h"
#include "quicksort.h"

int main(int argc, char* argv[]) {
    std::ifstream in(argv[1]); // Opens file from command line
    nlohmann::json jsonObject; // Declares the nlohmann::json object

    // Checks if the file opened correctly
    if (!in) {
        std::cerr << "Could not open " << argv[1] << std::endl; // Error message
        return 1; // Terminates program
    }
    in >> jsonObject; // Parses file with the >> operator

    std::ofstream csv("stats.csv"); // Opens csv output
    csv << std::fixed << std::setprecision(6); 
    // Checks if csv opens properly
    if (!csv) {
        std::cerr << "Could not open stats.csv" << std::endl; // Error Message
        return 1; // Terminates Program
    }
    csv << "Sample,InsertionSortTime,InsertionSortCompares,InsertionSortMemaccess,"
        "MergeSortTime,MergeSortCompares,MergeSortMemaccess,"
        "QuickSortTime,QuickSortCompares,QuickSortMemaccess\n"; // csv header row

    // Iterates over every sample
    for (auto itr = jsonObject.begin(); itr != jsonObject.end(); ++itr) {
        std::string sampleName = itr.key(); // Assigns key to sample name
        if (sampleName == "metadata") continue; // Skips metadata
        auto sampleArray = itr.value().get<std::vector<long long>>(); // Converts sample to std::vector<long long>

        // Copies of sample for each algorithm 
        auto arrInsertion = sampleArray; // Copy of sample for inserstionsort
        auto arrMerge = sampleArray; // Copy of sample for mergesort
        auto arrQuick = sampleArray; // Copy of sample for quicksort

        // Insertionsort
        auto start = std::chrono::high_resolution_clock::now(); // Start insertion runtime
        long long insertionCompares = 0, insertionMemaccess = 0; // Initializes stats for insertion
        insertionSort(arrInsertion, &insertionCompares, &insertionMemaccess); // Runs insertionSort
        auto end = std::chrono::high_resolution_clock::now(); // End insertion runtime
        double insertionTime = std::chrono::duration<double>(end - start).count(); // Elapsed time in seconds

        // Mergesort
        start = std::chrono::high_resolution_clock::now(); // Start mergeSort runtime
        long long mergeCompares = 0, mergeMemaccess = 0; // Initializes stats for mergeSort
        mergeSort(arrMerge, 0, arrMerge.size() - 1, &mergeCompares, &mergeMemaccess); // Runs mergeSort
        end = std::chrono::high_resolution_clock::now(); // End merge runtime
        double mergeTime = std::chrono::duration<double>(end - start).count(); // Elapsed time in seconds

        // Quicksort
        long long* quickArray = arrQuick.data(); // Converts std::vector to pointer
        int n = arrQuick.size(); // // Stores array length for bounds
        start = std::chrono::high_resolution_clock::now(); // Start quicksort time
        long long quickCompares = 0, quickMemaccess = 0; // Initializes stats for quicksort
        quickSort(quickArray, 0, n - 1, &quickCompares, &quickMemaccess); // Runs quicksort
        end = std::chrono::high_resolution_clock::now();
        double quickTime = std::chrono::duration<double>(end - start).count(); // Elapsed time in seconds

        // Write csv row for this sample
        csv << sampleName << ',' // Writes sample name
            << insertionTime << ',' << insertionCompares << ',' << insertionMemaccess << ',' // Writes insertion stats 
            << mergeTime << ',' << mergeCompares << ',' << mergeMemaccess << ',' // Writes merge stats
            << quickTime << ',' << quickCompares << ',' << quickMemaccess << '\n'; // Writes quicksort stats
    }
    csv.close();
}