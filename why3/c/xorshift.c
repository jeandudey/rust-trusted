#include <stdint.h>


struct xoshiro256ss_state {
  uint64_t s0;
  uint64_t s1;
  uint64_t s2;
  uint64_t s3;
};
