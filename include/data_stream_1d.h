#pragma once
#include <deque>

class DataStream1D {
 public:
  DataStream1D(const int window_size);
  ~DataStream1D(){};
  void add(double val);
  double sum();
  double average();
  double std();
  double variance();

 private:
  const int window_size_;
  std::deque<double> vals;
  double sum_, variance_, square_sum_;
};