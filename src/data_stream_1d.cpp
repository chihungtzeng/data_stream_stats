#include <cmath>
#include "data_stream_1d.h"
#include "median_tracker.h"

DataStream1D::DataStream1D(int window_size):
  median_tracker_ptr_{new MedianTracker}
{
  window_size_ = std::max(window_size, 1);
  for (int i = 0; i < window_size_; i++)
  {
    vals.push_back(0);
  }
  sum_ = 0;
  variance_ = 0;
  square_sum_ = 0;
}


DataStream1D::~DataStream1D()
{
}

void DataStream1D::add(double val)
{
  auto front = vals.front();
  vals.pop_front();
  // median_tracker_ptr_->remove(front);

  sum_ += val - front;
  square_sum_ += val * val - front * front;
  auto mu = sum_ / window_size_;

  variance_ = (square_sum_ - 2 * mu * sum_) / window_size_ + mu * mu;

  vals.push_back(val);
  // median_tracker_ptr_->add(val);
}

double DataStream1D::sum()
{
  return sum_;
}
double DataStream1D::average()
{
  return sum_ / window_size_;
}
double DataStream1D::std()
{
  return sqrt(variance_);
}
double DataStream1D::variance()
{
  return variance_;
}

/*
double DataStream1D::median()
{
  return median_tracker_ptr_->median();
}
*/
