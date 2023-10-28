#pragma once
#include <memory>

// Work In Progress
class IndexedPriorityQueue;

class MedianTracker
{
public:
  MedianTracker();
  ~MedianTracker();
  int add(double val);
  int remove(double val);
  double median();
  std::size_t size();

private:
  std::unique_ptr<IndexedPriorityQueue> min_ipq_ptr_, max_ipq_ptr_;
  void rebalance();
};
