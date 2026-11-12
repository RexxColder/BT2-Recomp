#include "common.h"

void func_002D8C90(u8 *arg0, s64 arg1) {
    s64 a3 = *(s64 *)(arg0 + 0x8);
    s64 t0 = *(s64 *)(arg0 + 0x10);
    s64 a2 = *(s64 *)(arg0 + 0x0);

    *(s32 *)(arg0 + 0x18) += 1;
    *(s64 *)(arg0 + 0x0) = a2 + arg1;
    *(s64 *)(arg0 + 0x8) = (arg1 < a3) ? arg1 : a3;
    *(s64 *)(arg0 + 0x10) = (t0 < arg1) ? arg1 : t0;
}
