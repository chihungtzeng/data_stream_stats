#include <gtest/gtest.h>
#include <cassert>
#include "data_stream_stats.h"

TEST(kk, t1) {
  DataStreamStats obj(6);
  for(int i=0; i<16; i++)
  {
    obj.add(i);
  }
  for(int i=1; i<=6; i++)
  {
    obj.add(i);
  }

  EXPECT_EQ(obj.sum(), 21);
}

