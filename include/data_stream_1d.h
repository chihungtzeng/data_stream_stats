#pragma once
#include <deque>
#include <memory>

class MedianTracker;

class DataStream1D {
 public:
  DataStream1D(int window_size);
  ~DataStream1D();
  void add(double val);
  double sum();
  double average();
  double std();
  double variance();
  // double median();

 private:
  int window_size_;
  std::deque<double> vals;
  double sum_, variance_, square_sum_;
  std::unique_ptr<MedianTracker> median_tracker_ptr_;
};
