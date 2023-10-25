#include <iostream>
#include <fuzzer/FuzzedDataProvider.h>
#include "data_stream_1d.h"

int iteration = 0;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* Data, size_t Size)
{
  auto fdp = FuzzedDataProvider{ Data, Size };
  iteration++;
  if (iteration % 1000 == 0)
  {
    std::cout << iteration << "th iteration, Size " << Size << std::endl;
  }

  DataStream1D obj(fdp.ConsumeIntegralInRange<int>(1, 32768));
  while (fdp.remaining_bytes() >= sizeof(double))
  {
    double val = fdp.ConsumeFloatingPoint<double>();
    obj.add(val);
    auto res = obj.sum();
    res = obj.average();
    res = obj.std();
    res = obj.variance();
  }
  return 0;  // Values other than 0 and -1 are reserved for future use.
}

