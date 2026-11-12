#include "common.h"

typedef struct { u64 lo, hi; } q128;

void func_00129B10(q128 *arg0, q128 *arg1) {
    q128 temp;
    temp = *arg1;
    *arg1 = *arg0;
    *arg0 = temp;
}
