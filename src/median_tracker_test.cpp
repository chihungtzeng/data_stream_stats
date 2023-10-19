#include <gtest/gtest.h>
#include "median_tracker.h"

using namespace std;

TEST(MedianTrackerTest, test_simple_even)
{
  MedianTracker obj;
  obj.add(3);
  obj.add(1);
  obj.add(4);
  obj.add(1);
  obj.add(5);
  obj.add(9);
  // [1, 1, 3] [4, 5, 9]
  EXPECT_EQ(obj.median(), 3.5);

  // [1, 1, 2] [4, 5, 9]
  obj.remove(3);
  obj.add(2);
  EXPECT_EQ(obj.median(), 3);

  // [1, 2, 4] [5, 6, 9]
  obj.remove(1);
  obj.add(6);
  EXPECT_EQ(obj.median(), 4.5);

  // [1, 2, 2] [5, 6, 9]
  obj.remove(4);
  obj.add(2);
  EXPECT_EQ(obj.median(), 3.5);
}

TEST(MedianTrackerTest, test_simple_odd)
{
  MedianTracker obj;
  obj.add(3);
  obj.add(1);
  obj.add(4);
  obj.add(1);
  obj.add(5);
  obj.add(9);
  obj.add(2);
  // 1, 1, 2, 3, 4, 5, 9
  EXPECT_EQ(obj.median(), 3);

  obj.remove(3);
  obj.add(6);
  // 1, 1, 2, 4, 5, 6, 9
  EXPECT_EQ(obj.median(), 4);
}
