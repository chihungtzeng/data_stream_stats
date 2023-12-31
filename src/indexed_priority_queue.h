#pragma once
#include <functional>
#include <limits>
#include <unordered_map>
// #include <set>
#include <unordered_set>
#include <vector>

constexpr double MIN_DOUBLE = std::numeric_limits<double>::lowest();

class IndexedPriorityQueue
{
public:
  IndexedPriorityQueue(bool use_max_heap = true);
  ~IndexedPriorityQueue();
  double top();
  int remove(double val);
  int add(double val);
  int pop();
  bool empty() {return vals_.empty();}
  std::size_t size();

private:
  std::vector<double> vals_;
  // When window size is small, use std::set<int> as the key type is faster.
  std::unordered_map<double, std::unordered_set<int>> indexes_of_;
  std::function<bool(double, double)> less_;

  int heapify_down(int index);
  int heapify_up(int index);
  int exchange(int index1, int index2);
  int pop_back();
};
