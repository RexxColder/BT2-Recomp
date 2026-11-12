#include "common.h"

void func_002E9A80(void *a0, void *a1, void *a2, void *a3, void *t0, void *t1, void *t2, void *t3, void *s8a);

s32 func_002E99B8(void *arg0, void *arg1, u16 *arg2, s32 *arg3, s32 *arg4) {
    u8 f[0x30];
    u16 a1;
    s32 A;
    s32 B;
    s32 C;
    s32 rem;

    func_002E9A80(arg0, arg1, f + 0x18, f + 0x10, f + 0x12, f + 0x1C, f + 0x20, f + 0x24, f + 0x14);
    a1 = *(u16 *)(f + 0x10);
    if (*(s16 *)(f + 0x10) != 1) {
        *(s16 *)(f + 0x10) = 0;
        a1 = 0;
    }
    *arg2 = a1;
    if (a1 == 0) {
        *arg4 = 0;
        *arg3 = 0;
        return 0;
    }
    A = *(s32 *)(f + 0x18);
    B = *(s32 *)(f + 0x1C);
    C = *(s32 *)(f + 0x24);
    rem = A - (((A < 0 ? A + 0x7FF : A) >> 11) << 11);
    C = C - rem;
    B = B - rem;
    *arg3 = B;
    *arg4 = C;
    return 0;
}
