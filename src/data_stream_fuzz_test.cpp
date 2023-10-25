#include <cassert>
#include <fuzzer/FuzzedDataProvider.h>

int iteration = 0;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* Data, size_t Size)
{
// TODO: make fuzz work
/*
  auto fdp = FuzzedDataProvider{ Data, Size };
  iteration++;
  if (iteration % 100000 == 0)
  {
    LOG(INFO) << iteration << "th iteration, Size " << Size;
  }

  while (fdp.remaining_bytes() >= sizeof(int) * 3)
  {
    IPQ ipq;
    int op = fdp.ConsumeIntegral<int>() % 5;
    int key = fdp.ConsumeIntegral<int>();
    int val = fdp.ConsumeIntegral<int>();
    switch (op)
    {
      case 0:
        ipq.empty();
        break;
      case 1:
        ipq.top();
        break;
      case 2:
        ipq.update(key, val);
        break;
      case 3:
        ipq.push(key, val);
        break;
      default:
        ipq.pop();
    }
  }
*/
  return 0;  // Values other than 0 and -1 are reserved for future use.
}

