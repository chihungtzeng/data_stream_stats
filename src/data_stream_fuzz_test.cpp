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

  bool enable_median = true;
  DataStream1D obj(fdp.ConsumeIntegralInRange<int>(1, 32768), enable_median);
  while (fdp.remaining_bytes() >= sizeof(double))
  {
    double val = fdp.ConsumeFloatingPoint<double>();
    obj.add(val);
    obj.sum();
    obj.average();
    obj.std();
    obj.variance();
    obj.median();
  }
  return 0;  // Values other than 0 and -1 are reserved for future use.
}

