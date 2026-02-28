#include <iostream>
#include <fstream>
#include "priorityqueue.h"

int main(int argc, char** argv) {
    std::ifstream in(argv[1]); // Open file from command line first arg
    if (!in) {
        std::cerr << "Error: Could not open file." << std::endl; // Error if file can't open
        return 1; // End if error
    }

    // JSON file handling
    nlohmann::json json; // Create JSON object
    in >> json; // Parse object
    int maxHeapSize = json["metadata"]["maxHeapSize"]; // Store the maximum heap size from metadata
    int numOperations = json["metadata"]["numOperations"];

    // Execute operations
    PriorityQueue minHeap(maxHeapSize); // Create the PriorityQueue object as a MinHeap
    for (const auto& [op_name, op_element] : json.items()) {
        if (op_name == "metadata") break; // End if metadata
        std::string op = op_element["operation"]; // Store operations in string
        if (op == "insert") {
            Key key = op_element["key"]; // Store key
            minHeap.insert(key); // Insert into the heap
        } else if (op == "removeMin") {
            minHeap.removeMin(); // Remove root
        }
    }

    // Output Structure
    nlohmann::json output = minHeap.JSON(); // Output JSON object
    output["metadata"]["maxHeapSize"] = maxHeapSize; // Add maxHeapSize to metadata
    output["metadata"]["numOperations"] = numOperations; // Add numOperations to metadata
    std::cout << output.dump(2); // Print JSON
}