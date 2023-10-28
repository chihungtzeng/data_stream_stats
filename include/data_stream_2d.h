#pragma once
#include <deque>
#include <vector>
#include "data_stream_1d.h"

class DataStream2D {
 public:
  DataStream2D(int window_size);
  ~DataStream2D(){};
  void add(double x, double y);
  double cov();  // covariance

 private:
  int window_size_;
  DataStream1D x_1d_, y_1d_, xy_1d_;
};
