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
