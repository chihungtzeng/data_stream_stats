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

int MedianTracker::add(double val)
{
  if (min_ipq_ptr_->empty())
  {
    min_ipq_ptr_->add(val);
    return EXIT_SUCCESS;
  }

  if (val >= min_ipq_ptr_->top())
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
    if (min_ipq_ptr_->size() < max_ipq_ptr_->size())
    {
      return max_ipq_ptr_->top();
    }
    else
    {
      return min_ipq_ptr_->top();
    }
  }
  return (min_ipq_ptr_->top() + max_ipq_ptr_->top()) / 2;
}

void MedianTracker::rebalance()
{
  while (min_ipq_ptr_->size() >= max_ipq_ptr_->size() + 2)
  {
    auto val = min_ipq_ptr_->top();
    min_ipq_ptr_->pop();
    max_ipq_ptr_->add(val);
  }
  while (max_ipq_ptr_->size() >= min_ipq_ptr_->size() + 2)
  {
    auto val = max_ipq_ptr_->top();
    max_ipq_ptr_->pop();
    min_ipq_ptr_->add(val);
  }
}
