#include "median_tracker.h"
#include "indexed_priority_queue.h"

// Work in progress
MedianTracker::MedianTracker(int window_size)
    : window_size_(std::max(window_size, 1)) {

  bool use_max_heap = true;
  max_ipq_ptr_ = std::make_unique<IndexedPriorityQueue>(
      new IndexedPriorityQueue(use_max_heap));

  use_max_heap = false;
  min_ipq_ptr_ = std::make_unique<IndexedPriorityQueue>(
      new IndexedPriorityQueue(use_max_heap));
}

int MedianTracker::add(double val) {
  return 0;
}

int MedianTracker::remove(double val) {
  return 0;
}

double MedianTracker::median() { return 0; }
