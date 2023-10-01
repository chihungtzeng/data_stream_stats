#pragma once
#include <deque>

class DataStreamStats {
 public:
  DataStreamStats(const int window_size);
  ~DataStreamStats(){};
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
