#include "data_stream_2d.h"

#include <gtest/gtest.h>

#include <cmath>

using namespace std;

TEST(DataStream2D, test_normal_window_size) {
  DataStream2D obj(6);
  for (int i = 0; i < 16; i++) {
    obj.add(i, (i + 15) % 7);
  }

  obj.add(0, 3);
  obj.add(2, 4);
  obj.add(4, 8);
  obj.add(6, 5);
  obj.add(8, 13);
  obj.add(10, 1);

  // EXPECT_DOUBLE_EQ(obj.cov(), 7 / 3.0);
  EXPECT_NEAR(obj.cov(), 7 / 3.0, 1e-9);
}
