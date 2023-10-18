#include <vector>
#include "indexed_priority_queue.h"

#include <gtest/gtest.h>

using namespace std;

TEST(IndexedPriorityQueueTest, test_simple) {
  IndexedPriorityQueue obj;
  obj.add(3);
  obj.add(1);
  obj.add(4);
  obj.add(1);
  obj.add(5);
  obj.add(9);
  obj.add(2);
  EXPECT_EQ(obj.top(), 9);
  obj.pop();
  EXPECT_EQ(obj.top(), 5);
  obj.pop();
  EXPECT_EQ(obj.top(), 4);
  obj.add(3);
  EXPECT_EQ(obj.top(), 4);
  obj.pop();
  EXPECT_EQ(obj.top(), 3);
  obj.pop();
  EXPECT_EQ(obj.top(), 3);
  obj.pop();
  EXPECT_EQ(obj.top(), 2);
  obj.pop();
  EXPECT_EQ(obj.top(), 1);
  obj.pop();
  EXPECT_EQ(obj.top(), 1);
  obj.pop();
  EXPECT_EQ(obj.top(), MIN_DOUBLE);
}

TEST(IndexedPriorityQueueTest, test_remove) {
  IndexedPriorityQueue obj;
  obj.add(3);
  obj.add(1);
  obj.add(4);
  obj.add(1);
  obj.add(5);
  obj.add(9);
  obj.add(2);
  EXPECT_EQ(obj.top(), 9);
  obj.remove(5);
  obj.remove(4);
  obj.remove(1);
  obj.pop();
  EXPECT_EQ(obj.top(), 3);
}

TEST(IndexedPriorityQueueTest, test_stress) {
  IndexedPriorityQueue obj;
  const int ub = 100000;
  for (int i = ub; i >= 0; i--) {
    obj.add(i);
  }
  for (int i = ub - 1000; i >= 1000; i--) {
    obj.remove(i);
  }
  EXPECT_EQ(obj.top(), ub);
}

TEST(IndexedPriorityQueueTest, test_min_heap)
{
  vector<double> vals{3, 1, 4, 1, 5, 9, 2, 6};
  bool use_max_heap = false;
  IndexedPriorityQueue obj(use_max_heap);
  for(auto val: vals)
  {
    obj.add(val);
  }
  EXPECT_EQ(obj.top(), 1);
  obj.pop();
  EXPECT_EQ(obj.top(), 1);
  obj.remove(2);
  obj.pop();
  EXPECT_EQ(obj.top(), 3);
}
