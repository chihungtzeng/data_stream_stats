#pragma once
#include <deque>
#include <memory>

class MedianTracker;

class DataStream1D
{
public:
  DataStream1D(int window_size, bool enable_median = false);
  ~DataStream1D();
  void add(double val);
  double sum();
  double average();
  double max();
  double min();
  double std();
  double variance();
  double median();
  std::size_t median_tracker_size();

private:
  int window_size_;
  std::deque<double> vals_;
  std::deque<double> max_vals_, min_vals_;
  double sum_, variance_, square_sum_;
  std::unique_ptr<MedianTracker> median_tracker_ptr_;
  const bool enable_median_;
};
