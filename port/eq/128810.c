#include "common.h"

typedef struct { u64 lo, hi; } q128;

void func_00128810(u8 *arg0, q128 *arg1) {
    *(q128 *)(arg0 + 0x30) = *arg1;
}
