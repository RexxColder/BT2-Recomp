#include "common.h"

typedef struct { u64 lo, hi; } q128;

void func_00128798(q128 *arg0, u8 *arg1) {
    *arg0 = *(q128 *)(arg1 + 0x30);
}
