#include "data_stream_1d.h"

#include <gtest/gtest.h>

#include <cmath>

using namespace std;
const int WINDOW_SIZE = 10;

static double sum_of(deque<double>& vals) {
  double s = 0;
  for (auto& val : vals) s += val;
  return s;
}

static double average_of(deque<double>& vals) {
  return sum_of(vals) / vals.size();
}

static double variance_of(deque<double>& vals) {
  auto avg = average_of(vals);
  auto res = 0;
  for (auto& val : vals) {
    res += (val - avg) * (val - avg);
  }
  return res / vals.size();
}

static double std_of(deque<double>& vals) { return sqrt(variance_of(vals)); }

TEST(DataStream1D, test_normal_window_size) {
  DataStream1D obj(6);
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

TEST(DataStream1D, test_window_size_one) {
  DataStream1D obj(1);
  for (int i = 0; i < 16; i++) {
    obj.add(i);
  }
  EXPECT_DOUBLE_EQ(obj.sum(), 15);
  EXPECT_DOUBLE_EQ(obj.average(), 15);
  EXPECT_DOUBLE_EQ(obj.variance(), 0);
  EXPECT_DOUBLE_EQ(obj.std(), 0);
}

TEST(DataStream1D, test_window_size_zero) {
  DataStream1D obj(0);
  for (int i = 0; i < 16; i++) {
    obj.add(i);
  }
  EXPECT_DOUBLE_EQ(obj.sum(), 15);
  EXPECT_DOUBLE_EQ(obj.average(), 15);
  EXPECT_DOUBLE_EQ(obj.variance(), 0);
  EXPECT_DOUBLE_EQ(obj.std(), 0);
}

TEST(DataStream1D, test_window_size_negtaive) {
  DataStream1D obj(-1);
  for (int i = 0; i < 16; i++) {
    obj.add(i);
  }
  EXPECT_DOUBLE_EQ(obj.sum(), 15);
  EXPECT_DOUBLE_EQ(obj.average(), 15);
  EXPECT_DOUBLE_EQ(obj.variance(), 0);
  EXPECT_DOUBLE_EQ(obj.std(), 0);
}

TEST(DataStream1D, test_stress) {
  DataStream1D obj(WINDOW_SIZE);
  for (int i = 1000000; i >= 0; i--) {
    obj.add(i);
    EXPECT_TRUE(obj.sum());
    EXPECT_TRUE(obj.average());
    EXPECT_TRUE(obj.std());
    EXPECT_TRUE(obj.variance());
  }
}

TEST(DataStream1D, test_naive) {
  deque<double> vals;
  for (int i = 1000000; i >= 0; i--) {
    vals.push_back(i);
    if (vals.size() == WINDOW_SIZE) {
      EXPECT_TRUE(sum_of(vals));
      EXPECT_TRUE(average_of(vals));
      EXPECT_TRUE(variance_of(vals));
      EXPECT_TRUE(std_of(vals));
      vals.pop_front();
    }
  }
}
