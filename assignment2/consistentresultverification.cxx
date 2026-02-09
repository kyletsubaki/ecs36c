#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "json.hpp"

int main(int argc, char* argv[]) {
    std::ifstream in1(argv[1]); // Opens file1 from command line
    nlohmann::json jsonObject1; // Declares the first nlohmann::json object
    if (!in1) { 
        std::cerr << "Could not open " << argv[1] << std::endl; // Error message for failed file1 opening
        return 1; // Terminates program
    }
    in1 >> jsonObject1; // Parse file1

    std::ifstream in2(argv[2]); // Opens file1 from command line
    nlohmann::json jsonObject2; // Declares the second nlohmann::json object
    if (!in2) { 
        std::cerr << "Could not open " << argv[2] << "\n"; // Error message for failed file2 opening
        return 1; // Terminates program
    }
    in2 >> jsonObject2; // Parse file2

    // Get metadata from file1
    int arraySize1 = jsonObject1["metadata"]["arraySize"]; // Gets sample sizes from file1
    int numSamples1 = jsonObject1["metadata"]["numSamples"]; // Gets number of samples from file1
    std::string filename1 = argv[1]; // Gets file1 name from command line

    // Get metadata from file2
    int arraySize2 = jsonObject2["metadata"]["arraySize"]; // Gets sample sizes from file2
    int numSamples2 = jsonObject2["metadata"]["numSamples"]; // Gets number of samples from file2
    std::string filename2 = argv[2]; // Gets file2 name from command line

    // Output structure 
    nlohmann::json output; // Declares nlohmann::json object to store output
    output["metadata"]["File1"]["arraySize"] = arraySize1; // Copies file1 sample size to output
    output["metadata"]["File1"]["name"] = filename1; // Copies file1 name to output
    output["metadata"]["File1"]["numSamples"] = numSamples1; // Copies file1 sample count to output
    output["metadata"]["File2"]["arraySize"] = arraySize2; // Copies file2 sample size to output
    output["metadata"]["File2"]["name"] = filename2; // Copies file2 name to output
    output["metadata"]["File2"]["numSamples"] = numSamples2; // Copies file2 sample count to output
    output["metadata"]["samplesWithConflictingResults"] = 0; // Initializes conflict count to output

    int samplesWithConflictingResults = 0; // Initializes conflict count
    for (auto itr = jsonObject1.begin(); itr != jsonObject1.end(); ++itr) {
        std::string sampleName = itr.key(); // Assigns key to sample name
        if (sampleName == "metadata") continue; // Skips metadata

        // Gets sample arrays from both files
        auto sampleArray1 = itr.value().get<std::vector<long long>>(); // Converts file1 sample to std::vector<long long>
        auto sampleArray2 = jsonObject2[sampleName].get<std::vector<long long>>(); // Converts file2 sample to std::vector<long long>

        // Finds conflicts 
        nlohmann::json mismatches; // Declares nlohmann::json object for conflicting pairs
        bool hasMismatch = false; // Initializes conflict check
        for (size_t i = 0; i < sampleArray1.size(); ++i) {
            if (sampleArray1[i] != sampleArray2[i]) {
                mismatches[std::to_string(i)] = {sampleArray1[i], sampleArray2[i]}; // Stores mismatched pair at index i
                hasMismatch = true; // Updates mismatch check
            }
        }

        // If mismatches found, add to output
        if (hasMismatch) {
            samplesWithConflictingResults++; // Increments conflict count
            output[sampleName][argv[1]] = sampleArray1; // File1 array
            output[sampleName][argv[2]] = sampleArray2; // File2 array  
            output[sampleName]["Mismatches"] = mismatches; // Mismatch positions
        }
    }
    output["metadata"]["samplesWithConflictingResults"] = samplesWithConflictingResults; // Updates final count
    std::cout << output.dump(4) << std::endl; // Prints output
}