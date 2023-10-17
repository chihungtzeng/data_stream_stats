
#include "indexed_priority_queue.h"


//constexpr int EXIT_SUCCESS = 0;
//constexpr int EXIT_FAILURE = 1;

static int parent(int index) { return (index - 1) / 2; }
static int left(int index) { return 2 * index + 1; }
static int right(int index) { return 2 * index + 2; }

IndexedPriorityQueue::IndexedPriorityQueue() {
  less_ = [](double a, double b){return a < b;};
}

IndexedPriorityQueue::~IndexedPriorityQueue() {}

std::size_t IndexedPriorityQueue::size() {
  return vals_.size();
}

double IndexedPriorityQueue::top() {
  if (!vals_.empty()) {
    return vals_[0];
  } else {
    return MIN_DOUBLE;
  }
}

int IndexedPriorityQueue::remove(double val) {
  if (indexes_of_[val].size() == 0) {
    return EXIT_FAILURE;
  }
  int idx = *indexes_of_[val].begin();
  exchange(idx, vals_.size() - 1);
  pop_back();
  if (less_(vals_[idx], val)) {
    heapify_down(idx);
  } else {
    heapify_up(idx);
  }
  return EXIT_SUCCESS;
}

int IndexedPriorityQueue::pop_back() {
  if (vals_.empty()) {
    return EXIT_FAILURE;
  }

  double val = vals_.back();

  indexes_of_[val].erase(vals_.size() - 1);
  if (indexes_of_[val].size() == 0) {
    indexes_of_.erase(val);
  }
  vals_.pop_back();
  return EXIT_SUCCESS;
}

int IndexedPriorityQueue::exchange(int index1, int index2) {
  const int n = vals_.size();
  if (index1 < 0 || index1 >= n || index2 < 0 || index2 >= n) {
    return EXIT_FAILURE;
  }
  auto v1 = vals_[index1], v2 = vals_[index2];
  indexes_of_[v1].erase(index1);
  indexes_of_[v2].erase(index2);
  std::swap(vals_[index1], vals_[index2]);
  indexes_of_[v1].insert(index2);
  indexes_of_[v2].insert(index1);
  return EXIT_SUCCESS;
}

int IndexedPriorityQueue::add(double val)
{
  vals_.push_back(val);
  indexes_of_[val].insert(vals_.size() - 1);
  heapify_up(vals_.size() - 1);
  return EXIT_SUCCESS;
}

int IndexedPriorityQueue::pop() {
  return remove(vals_[0]);
}


int IndexedPriorityQueue::heapify_down(int index)
{
  auto largest = vals_[index];
  int next = index;
  int left_child = left(index);
  const int n = vals_.size();
  if (left_child < n && less_(largest, vals_[left_child]))
  {
    largest = vals_[left_child];
    next = left_child;
  }
  int right_child = right(index);
  if (right_child < n && less_(largest, vals_[right_child]))
  {
    largest = vals_[right_child];
    next = right_child;
  }
  if (next != index)
  {
    exchange(index, next);
    heapify_down(next);
  }
  return EXIT_SUCCESS;
}

int IndexedPriorityQueue::heapify_up(int index)
{
  bool done = false;
  while (index > 0 && !done)
  {
    int pidx = parent(index);
    if (less_(vals_[index], vals_[pidx]))
    {
      done = true;
    } else {
      exchange(index, pidx);
      index = pidx;
    }
  }
  return EXIT_SUCCESS;
}
