#include <cmath>
#include <numeric>
#include <vector>
#include <gtest/gtest.h>
#include "data_stream_1d.h"

using namespace std;
const int WINDOW_SIZE = 300;
const int NUM_LOOPS = 100000;
const int P1 = 7727, P2 = 65537;  // prime numbers

static double sum_of(deque<double>& vals)
{
  return accumulate(vals.begin(), vals.end(), 0.0);
}

static double average_of(deque<double>& vals)
{
  return sum_of(vals) / vals.size();
}

static double min_of(deque<double>& vals)
{
  double res = std::numeric_limits<double>::max();
  for (auto val : vals)
  {
    res = min(val, res);
  }
  return res;
}

static double variance_of(deque<double>& vals)
{
  auto avg = average_of(vals);
  double res = 0;
  for (auto& val : vals)
  {
    res += (val - avg) * (val - avg);
  }
  return res / vals.size();
}

static double std_of(deque<double>& vals)
{
  return sqrt(variance_of(vals));
}

static double median_of(deque<double>& vals)
{
  std::vector<double> vec{ vals.begin(), vals.end() };
  std::sort(vec.begin(), vec.end());
  auto m = vec.size() / 2;
  if (vec.size() % 2 == 0)
  {
    return (vec[m] + vec[m - 1]) / 2;
  }
  else
  {
    return vec[m];
  }
}

TEST(DataStream1D, test_naive_variance)
{
  deque<double> vals{ 18770, 11043, 3316, 61126, 53399 };
  EXPECT_NEAR(variance_of(vals), 542551387.76, 1e-2);
}

TEST(DataStream1D, test_normal_window_size)
{
  DataStream1D obj(6);
  for (int i = 0; i < 16; i++)
  {
    obj.add(i);
  }
  for (int i = 1; i <= 6; i++)
  {
    obj.add(i);
  }

  EXPECT_DOUBLE_EQ(obj.sum(), 21);
  EXPECT_DOUBLE_EQ(obj.average(), 3.5);
  EXPECT_DOUBLE_EQ(obj.min(), 1);
  EXPECT_DOUBLE_EQ(obj.variance(), 35 / 12.0);
  EXPECT_NEAR(obj.std(), 1.70782, 1e-5);

  obj.add(-1);
  EXPECT_DOUBLE_EQ(obj.min(), -1);
}

TEST(DataStream1D, test_window_size_one)
{
  DataStream1D obj(1);
  for (int i = 0; i < 16; i++)
  {
    obj.add(i);
  }
  EXPECT_DOUBLE_EQ(obj.sum(), 15);
  EXPECT_DOUBLE_EQ(obj.average(), 15);
  EXPECT_DOUBLE_EQ(obj.min(), 15);
  EXPECT_DOUBLE_EQ(obj.variance(), 0);
  EXPECT_DOUBLE_EQ(obj.std(), 0);
}

TEST(DataStream1D, test_stress_no_median)
{
  DataStream1D obj(WINDOW_SIZE);
  for (int i = NUM_LOOPS; i >= 0; i--)
  {
    obj.add((i * P1) % P2);
    obj.sum();
    obj.average();
    obj.min();
    obj.std();
    obj.variance();
  }
}

TEST(DataStream1D, test_stress_with_median)
{
  DataStream1D obj(WINDOW_SIZE, true);
  for (int i = NUM_LOOPS; i >= 0; i--)
  {
    obj.add((i * P1) % P2);
    obj.sum();
    obj.average();
    obj.min();
    obj.std();
    obj.variance();
    obj.median();
  }
}

TEST(DataStream1D, test_correctness)
{
  deque<double> vals;
  DataStream1D obj(WINDOW_SIZE, true);
  bool done = false;
  for (int i = NUM_LOOPS; i >= 0 && !done; i--)
  {
    int val = (i * P1) % P2;
    vals.push_back(val);
    obj.add(val);

    if (vals.size() == WINDOW_SIZE)
    {
      // done = true;
      /*
            std::cout << "i: " << i << "\n";
            for(auto val: vals) {
              std::cout << val << " ";
            }
              std::cout << "\n";
              */
      EXPECT_EQ(obj.median_tracker_size(), WINDOW_SIZE);
      EXPECT_EQ(obj.sum(), sum_of(vals));
      EXPECT_EQ(obj.average(), average_of(vals));
      EXPECT_EQ(obj.min(), min_of(vals));
      EXPECT_NEAR(obj.variance(), variance_of(vals), 1e-5);
      EXPECT_NEAR(obj.std(), std_of(vals), 1e-5);
      EXPECT_EQ(obj.median(), median_of(vals));
      vals.pop_front();
    }
  }
}

TEST(DataStream1D, test_naive_no_median)
{
  deque<double> vals;
  for (int i = NUM_LOOPS; i >= 0; i--)
  {
    vals.push_back((i * P1) % P2);
    if (vals.size() == WINDOW_SIZE)
    {
      sum_of(vals);
      average_of(vals);
      min_of(vals);
      variance_of(vals);
      std_of(vals);

      vals.pop_front();
    }
  }
}

TEST(DataStream1D, test_naive_with_median)
{
  deque<double> vals;
  for (int i = NUM_LOOPS; i >= 0; i--)
  {
    vals.push_back((i * P1) % P2);
    if (vals.size() == WINDOW_SIZE)
    {
      sum_of(vals);
      average_of(vals);
      min_of(vals);
      variance_of(vals);
      std_of(vals);
      median_of(vals);

      vals.pop_front();
    }
  }
}
