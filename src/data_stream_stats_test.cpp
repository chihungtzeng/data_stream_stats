#include <cmath>
#include <gtest/gtest.h>
#include "data_stream_stats.h"


using namespace std;

static double sum_of(deque<double>& vals)
{
  double s = 0;
  for(auto& val: vals) s+= val;
  return s;
}

static double average_of(deque<double>& vals)
{
  return sum_of(vals) / vals.size();
}

static double variance_of(deque<double>& vals)
{
  auto avg = average_of(vals);
  auto res = 0;
  for(auto& val: vals)
  {
    res += (val - avg) * (val - avg);
  }
  return res / vals.size();
}

static double std_of(deque<double>& vals)
{
  return sqrt(variance_of(vals));
}


TEST(DataStreamStats, test_6) {
  DataStreamStats obj(6);
  for (int i = 0; i < 16; i++) {
    obj.add(i);
  }
  for (int i = 1; i <= 6; i++) {
    obj.add(i);
  }

  EXPECT_DOUBLE_EQ(obj.sum(), 21);
  EXPECT_DOUBLE_EQ(obj.average(), 3.5);
  EXPECT_DOUBLE_EQ(obj.variance(), 35 / 12.0);
  EXPECT_NEAR(obj.std(), 1.70782, 1e-5);
}

TEST(DataStreamStats, test_0) {
  DataStreamStats obj(0);
  for (int i = 0; i < 16; i++) {
    obj.add(i);
  }
  EXPECT_DOUBLE_EQ(obj.sum(), 0);
  EXPECT_DOUBLE_EQ(obj.average(), 0);
}

TEST(DataStreamStats, test_1) {
  DataStreamStats obj(1);
  for (int i = 0; i < 16; i++) {
    obj.add(i);
  }
  EXPECT_DOUBLE_EQ(obj.sum(), 15);
  EXPECT_DOUBLE_EQ(obj.average(), 15);
  EXPECT_DOUBLE_EQ(obj.variance(), 0);
  EXPECT_DOUBLE_EQ(obj.std(), 0);
}

TEST(DataStreamStats, test_stress) {
  DataStreamStats obj(100);
  for (int i = 1000000; i >= 0; i--) {
    obj.add(i);
    EXPECT_TRUE(obj.sum());
    EXPECT_TRUE(obj.average());
    EXPECT_TRUE(obj.std());
    EXPECT_TRUE(obj.variance());
  }
}

TEST(DataStreamStats, test_naive) {
  deque<double> vals;
  for (int i = 1000000; i >= 0; i--) {
    vals.push_back(i);
    if (vals.size() == 100)
    {
      EXPECT_TRUE(sum_of(vals));
      EXPECT_TRUE(average_of(vals));
      EXPECT_TRUE(variance_of(vals));
      EXPECT_TRUE(std_of(vals));
      vals.pop_front();
    }
  }
}

