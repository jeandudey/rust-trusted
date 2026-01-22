#include <stdint.h>

#include <string.h>


int32_t base58_char2index(char c) {
  int cond, cond1, cond2, cond3, cond4, cond5;
  int32_t q1_, q1_1, q1_2, q1_3, q1_4, q1_5;
  q1_ = c;
  if (49 <= q1_) {
    cond = q1_ <= 57;
  } else {
    cond = 0;
  }
  if (cond) {
    return c - 49;
  } else {
    q1_1 = c;
    if (65 <= q1_1) {
      cond1 = q1_1 <= 72;
    } else {
      cond1 = 0;
    }
    if (cond1) {
      return c + 9 - 65;
    } else {
      q1_2 = c;
      if (74 <= q1_2) {
        cond2 = q1_2 <= 78;
      } else {
        cond2 = 0;
      }
      if (cond2) {
        return c + 17 - 74;
      } else {
        q1_3 = c;
        if (80 <= q1_3) {
          cond3 = q1_3 <= 90;
        } else {
          cond3 = 0;
        }
        if (cond3) {
          return c + 22 - 80;
        } else {
          q1_4 = c;
          if (97 <= q1_4) {
            cond4 = q1_4 <= 107;
          } else {
            cond4 = 0;
          }
          if (cond4) {
            return c + 33 - 97;
          } else {
            q1_5 = c;
            if (109 <= q1_5) {
              cond5 = q1_5 <= 122;
            } else {
              cond5 = 0;
            }
            if (cond5) {
              return c + 44 - 109;
            } else {
              return -1;
            }
          }
        }
      }
    }
  }
}
