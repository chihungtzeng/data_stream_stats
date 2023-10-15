#pragma once
#include <limits>
#include <vector>
#include <unordered_map>
#include <unordered_set>

constexpr double MIN_DOUBLE = std::numeric_limits<double>::lowest();

class IndexedPriorityQueue {
  public:
    IndexedPriorityQueue();
    ~IndexedPriorityQueue();
    double top();
    int remove(double val);
    int add(double val);
    int pop();

  private:
    std::vector<double> vals_;
    std::unordered_map<double, std::unordered_set<int>> indexes_of_;

    int heapify_down(int index);
    int heapify_up(int index);
    int exchange(int index1, int index2);
    int pop_back();
};
