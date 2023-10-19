#pragma once
#include <memory>

// Work In Progress
class IndexedPriorityQueue;

class MedianTracker
{
public:
  MedianTracker(int window_size);
  ~MedianTracker(){};
  int add(double val);
  int remove(double val);
  double median();

private:
  int window_size_;
  std::unique_ptr<IndexedPriorityQueue> max_ipq_ptr_, min_ipq_ptr_;
};
