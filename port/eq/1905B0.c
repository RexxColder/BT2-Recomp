#include "common.h"

void func_00129C38();
extern s32 D_003877BC;

void func_001905B0(u8 *arg0, u8 *arg1, u8 *arg2) {
    s64 a[2];
    s64 b[2];
    u8 *s0;

    a[0] = *(s64 *)(arg1 + 0);
    a[1] = *(s64 *)(arg1 + 8);
    b[0] = *(s64 *)(arg2 + 0);
    b[1] = *(s64 *)(arg2 + 8);
    if (D_003877BC != 0) {
        if (arg0 != NULL) {
            s0 = *(u8 **)(arg0 + 0x38);
            if (s0 != NULL && (*(u16 *)(s0 + 0x44) & 2)) {
                func_00129C38(s0 + 0x10, a, arg0);
                func_00129C38(s0 + 0x20, b);
            }
        }
    }
}
