#include <iostream>
#include <algorithm>
#include <stdexcept>
#include "priorityqueue.h"

PriorityQueue::PriorityQueue(std::size_t max_size) :
	nodes_(max_size + 1, KeyValuePair()),
	max_size_(max_size),
	size_(0) {
}

void PriorityQueue::insert(Key k) {
	insert(std::make_pair(k, std::make_pair(0, 0)));
}

void PriorityQueue::insert(KeyValuePair kv) {
	// TODO: complete this function
    if (size_ > max_size_) {
        throw std::overflow_error("Error: MinHeap is already full."); // Handles overflow case
    }
    ++size_;
    nodes_[size_] = kv;
    heapifyUp(size_);
}

KeyValuePair PriorityQueue::min() {
	// TODO: complete this function
    if (isEmpty()) {
        throw std::underflow_error("Error: MinHeap is empty."); // Handles empty case
    }
    return nodes_[ROOT]; // The root of a MinHeap is the min
}

KeyValuePair PriorityQueue::removeMin() {
	// TODO: complete this function
    if (isEmpty()) {
        throw std::underflow_error("Error: MinHeap is empty."); // Handles empty case
    }
    auto root = min(); // Save the root since it's the min
    removeNode(ROOT); // Remove the root
    return root; // Return the saved root
}

bool PriorityQueue::isEmpty() const {
	// TODO: complete this function
    return (size_ == 0) ? true : false; // If the size of the heap is empty, return true; if not, return false.
}

size_t PriorityQueue::size() const {
	// TODO: complete this function
    return size_; // Provides the size of the heap.
}

nlohmann::json PriorityQueue::JSON() const {
	nlohmann::json result;
  for (size_t i = 1; i <= size_; i++) {
      nlohmann::json node;
      KeyValuePair kv = nodes_[i];
      node["key"] = kv.first;
      node["value"] = kv.second;
      if (i != ROOT) {
          node["parent"] = std::to_string(i / 2);
      }
      if (2 * i <= size_) {
          node["leftChild"] = std::to_string(2 * i);
      }
      if (2 * i + 1 <= size_) {
          node["rightChild"] = std::to_string(2 * i + 1);
      }
      result[std::to_string(i)] = node;
  }
  result["metadata"]["max_size"] = max_size_;
  result["metadata"]["size"] = size_;
	return result;
}

void PriorityQueue::heapifyUp(size_t i) {
	// TODO: complete this function
    size_t current = i; // Set current node to input
    size_t parent = i / 2; // Find parent 
    while (current > ROOT) {
        if (!(getKey(current) < getKey(parent))) break; // Negation of condition
        std::swap(nodes_[current], nodes_[parent]); // Swap the current node and the parent node
        current = parent; // Update current node to previous parent
        parent = current / 2; // Update parent node to parent of previous parent 
    }
}

void PriorityQueue::heapifyDown(size_t i) {
	// TODO: complete this function
    while (2 * i <= size_) {  // While at least a left child exists
        size_t left = 2 * i;
        size_t right = 2 * i + 1;
        size_t smallest = left; // Assume left child is smaller to start

        // If right child exists and is smaller, choose right child
        if (right <= size_ && getKey(right) < getKey(left)) smallest = right;

        // If the smallest child is smaller than current node, swap
        if (getKey(smallest) < getKey(i)) {
            std::swap(nodes_[i], nodes_[smallest]);
            i = smallest;  // Move down to child
        } else {
            break;  // Heap property restored
        }
    }
}

void PriorityQueue::removeNode(size_t i) {
	// TODO: complete this function
    if (i > size_) return; // In case node index doesn't exist
    std::swap(nodes_[i], nodes_[size_]); // Swap with last node
    --size_; // Decrement size
    if (i > size_) return; // In case the last element was removed
    if (i == ROOT) { 
        heapifyDown(i); // If root, only heapify down if necessary
        return; // Stop from continuing down the function
    }

    Key new_key = getKey(i); // Declare the new key
    Key parent = getKey(i / 2); // Declare parent to the new key
    if (new_key < parent) {
        heapifyUp(i); // If the new key is smaller than the parent, go up towards the root
    } else {
        heapifyDown(i); // Otherwise, go down
    }
}

Key PriorityQueue::getKey(size_t i) {
	// TODO: complete this function
    return nodes_[i].first; // nodes_[i] is the kv, so .first provides the key.
}
