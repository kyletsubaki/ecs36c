#ifndef _PRIORITYQUEUE_H_
#define _PRIORITYQUEUE_H_

#include <vector>
#include <utility>
#include "json.hpp"

typedef double                  Key; // The key is how the MinHeap is ordered
typedef std::pair<int, int>     Value; // The value is additional information about the node
typedef std::pair<Key, Value>   KeyValuePair; // The KeyValuePair is the information on each node

class PriorityQueue {
  public:
    PriorityQueue(std::size_t max_nodes);
    void insert(Key k);
    void insert(KeyValuePair kv);
    KeyValuePair min();
    KeyValuePair removeMin();
    bool isEmpty() const;
    size_t size() const;
    nlohmann::json JSON() const;

  private:
    void heapifyUp(size_t i);
    void heapifyDown(size_t i);
    void removeNode(size_t i);
    Key getKey(size_t i);

    std::vector<KeyValuePair>   nodes_; // This is the array that stores the MinHeap
    size_t                      max_size_; // This is the maximum number of nodes allowed in the MinHeap
    size_t                      size_; // This is the number of elements in the MinHeap

    const static size_t         ROOT = 1; // The index of the root is 1
};  // class PriorityQueue

#endif  // _PRIORITYQUEUE_H_