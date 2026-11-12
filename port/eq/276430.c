#include "common.h"

extern u8 *D_003876A0;

void func_00276430(u8 *arg0) {
    u8 *v1;

    if (*(u8 **)(arg0 + 4) == NULL) {
        v1 = *(u8 **)(D_003876A0 + 4);
        if (*(s64 *)(D_003876A0 + 0x4D8) & ((s64)0x8000 << 47)) {
            v1 += 0x40;
        }
        *(u8 **)(arg0 + 4) = v1 + (((*(u32 *)(v1 + 8)) >> 2) << 2);
    }
}
