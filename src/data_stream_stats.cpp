#include "data_stream_stats.h"

using namespace std;

DataStreamStats::DataStreamStats(const int window_size)
    : window_size_(window_size) {
  sum_ = 0;
  average_ = 0;
  std_ = 0;
  variance_ = 0;
}

void DataStreamStats::add(double val) {}

double DataStreamStats::sum() { return 0; }
double DataStreamStats::average() { return 0; }
double DataStreamStats::std() { return 0; }
double DataStreamStats::variance() { return 0; }
