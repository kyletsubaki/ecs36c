#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "json.hpp"

int main(int argc, char* argv[]) {
    std::ifstream in(argv[1]); // Opens file from command line
    nlohmann::json jsonObject; // Declares the nlohmann::json object

    // Checks if the file opened correctly
    if (!in) { 
        std::cerr << "Could not open " << argv[1] << std::endl; // Error message
        return 1; // Terminates program
    }
    in >> jsonObject; // Parses file with the >> operator

    // Gets metadata
    int arraySize = jsonObject["metadata"]["arraySize"]; // Gets sample sizes
    int numSamples = jsonObject["metadata"]["numSamples"]; // Gets number of samples
    std::string filename = argv[1]; // Gets file name from command line

    // Output structure
    nlohmann::json output; // Declares nlohmann::json object to store output
    output["metadata"]["arraySize"] = arraySize; // Copies sample size to output
    output["metadata"]["file"] = filename; // Copies file name to output
    output["metadata"]["numSamples"] = numSamples; // Copies sample count to output
    output["metadata"]["samplesWithInversions"] = 0; // Initializes inversion count to output

    int samplesWithInversions = 0; // Initializes inversion count
    // Iterates over every sample
    for (auto itr = jsonObject.begin(); itr != jsonObject.end(); ++itr) {
        std::string sampleName = itr.key(); // Assigns key to sample name
        if (sampleName == "metadata") continue; // Skips metadata
        auto sampleArray = itr.value().get<std::vector<long long>>(); // Converts sample to std::vector<long long>

        // Finds consecutive inversions (where arr[i] > arr[i+1])
        nlohmann::json inversions; // Declares nlohmann::json object for inversion pairs
        bool hasInversion = false; // Initializes inversion check
        for (size_t i = 0; i + 1 < sampleArray.size(); ++i) {
            if (sampleArray[i] > sampleArray[i + 1]) {
                inversions[std::to_string(i)] = {sampleArray[i], sampleArray[i + 1]}; // Stores inversion pair at index i
                hasInversion = true; // Updates inversion check
            }
        }

        if (hasInversion) {
            samplesWithInversions++; // Increments inversion count
            output[sampleName]["ConsecutiveInversions"] = inversions; // Updates output for inversion count
            output[sampleName]["sample"] = sampleArray; // Stores the original sample in the output
        }
    }
    output["metadata"]["samplesWithInversions"] = samplesWithInversions; // Updates final count in metadata
    std::cout << output.dump(4) << std::endl; // Prints output 
}