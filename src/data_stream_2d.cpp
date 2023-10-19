#include "data_stream_2d.h"

DataStream2D::DataStream2D(int window_size)
  : window_size_(std::max(window_size, 1)), x_1d_(window_size_), y_1d_(window_size_), xy_1d_(window_size_)
{
}

void DataStream2D::add(double x, double y)
{
  x_1d_.add(x);
  y_1d_.add(y);
  xy_1d_.add(x * y);
}

double DataStream2D::cov()
{
  auto x_sum = x_1d_.sum();
  auto x_avg = x_1d_.average();
  auto y_sum = y_1d_.sum();
  auto y_avg = y_1d_.average();
  auto xy_sum = xy_1d_.sum();
  return x_avg * y_avg + (xy_sum - x_avg * y_sum - y_avg * x_sum) / window_size_;
}
