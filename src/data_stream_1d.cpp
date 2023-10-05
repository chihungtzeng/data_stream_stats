#include "data_stream_1d.h"

#include <cmath>

DataStream1D::DataStream1D(const int window_size)
    : window_size_(window_size) {
  for (int i = 0; i < window_size; i++) {
    vals.push_back(0);
  }
  sum_ = 0;
  variance_ = 0;
  square_sum_ = 0;
}

void DataStream1D::add(double val) {
  auto front = vals.front();
  vals.pop_front();

  if (window_size_ > 0) {
    sum_ += val - front;
    square_sum_ += val * val - front * front;
    auto mu = sum_ / window_size_;

    variance_ = (square_sum_ - 2 * mu * sum_) / window_size_ + mu * mu;

    vals.push_back(val);
  }
}

double DataStream1D::sum() { return sum_; }
double DataStream1D::average() {
  if (window_size_ > 0) {
    return sum_ / window_size_;
  } else {
    return 0;
  }
}
double DataStream1D::std() { return sqrt(variance_); }
double DataStream1D::variance() { return variance_; }
