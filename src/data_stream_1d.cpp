#include <cmath>
#include "data_stream_1d.h"
#include "median_tracker.h"

DataStream1D::DataStream1D(int window_size, bool enable_median)
  : median_tracker_ptr_{ new MedianTracker }, enable_median_(enable_median)
{
  window_size_ = std::max(window_size, 1);
  for (int i = 0; i < window_size_; i++)
  {
    vals_.push_back(0);
  }
  sum_ = 0;
  variance_ = 0;
  square_sum_ = 0;
}

DataStream1D::~DataStream1D()
{
}

std::size_t DataStream1D::median_tracker_size()
{
  return median_tracker_ptr_->size();
}

void DataStream1D::add(double val)
{
  auto front = vals_.front();
  vals_.pop_front();
  sum_ += val - front;
  square_sum_ += val * val - front * front;
  auto mu = sum_ / window_size_;

  variance_ = (square_sum_ - 2 * mu * sum_) / window_size_ + mu * mu;

  vals_.push_back(val);
  if (enable_median_)
  {
    median_tracker_ptr_->add(val);
    median_tracker_ptr_->remove(front);
  }
  // Update min_vals_;
  while (!min_vals_.empty() && min_vals_.back() > val)
  {
    min_vals_.pop_back();
  }
  min_vals_.push_back(val);
  if (min_vals_.front() == front)
  {
    min_vals_.pop_front();
  }
}

double DataStream1D::sum()
{
  return sum_;
}

double DataStream1D::average()
{
  return sum_ / window_size_;
}

double DataStream1D::min()
{
  return min_vals_.front();
}

double DataStream1D::std()
{
  return sqrt(variance_);
}
double DataStream1D::variance()
{
  return variance_;
}

double DataStream1D::median()
{
  if (enable_median_)
  {
    return median_tracker_ptr_->median();
  }
  return 0;
}
