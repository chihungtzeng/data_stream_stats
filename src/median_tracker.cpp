#include <iostream>
#include "median_tracker.h"
#include "indexed_priority_queue.h"

// Work in progress
MedianTracker::MedianTracker()
  : min_ipq_ptr_{ new IndexedPriorityQueue(false) }, max_ipq_ptr_{ new IndexedPriorityQueue(true) }
{
}

MedianTracker::~MedianTracker()
{
}

std::size_t MedianTracker::size()
{
  return min_ipq_ptr_->size() + max_ipq_ptr_->size();
}

int MedianTracker::add(double val)
{
  if (min_ipq_ptr_->empty() || val >= min_ipq_ptr_->top())
  {
    min_ipq_ptr_->add(val);
  }
  else
  {
    max_ipq_ptr_->add(val);
  }
  rebalance();
  return EXIT_SUCCESS;
}

int MedianTracker::remove(double val)
{
  if (val >= min_ipq_ptr_->top())
  {
    min_ipq_ptr_->remove(val);
  }
  else
  {
    max_ipq_ptr_->remove(val);
  }
  rebalance();
  return EXIT_SUCCESS;
}

double MedianTracker::median()
{
  size_t nelem = max_ipq_ptr_->size() + min_ipq_ptr_->size();
  if (nelem & 1)
  {
    return min_ipq_ptr_->top();
  }
  return (min_ipq_ptr_->top() + max_ipq_ptr_->top()) / 2;
}

void MedianTracker::rebalance()
{
  // make sure min_ipq_ptr_->size() == max_ipq_ptr_->size() or
  //           min_ipq_ptr_->size() == max_ipq_ptr_->size() + 1
  // So that we can get the median from min_ipq_ptr if the total size is odd.
  while (min_ipq_ptr_->size() >= max_ipq_ptr_->size() + 2)
  {
    auto val = min_ipq_ptr_->top();
    min_ipq_ptr_->pop();
    max_ipq_ptr_->add(val);
  }
  while (max_ipq_ptr_->size() >= min_ipq_ptr_->size() + 1)
  {
    auto val = max_ipq_ptr_->top();
    max_ipq_ptr_->pop();
    min_ipq_ptr_->add(val);
  }
}
