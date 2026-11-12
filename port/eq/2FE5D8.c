#include "common.h"

extern u8 D_00356CF0[] __attribute__((section(".data")));

s32 func_002FE090(u8 *arg0, u8 *arg1);

void func_002FE5D8(u8 *arg0, u8 *arg1, u8 *arg2, s32 arg3) {
    s32 i = 0;
    u8 *s1 = arg2;
    s32 r;

    if (arg3 > 0) {
        for (;;) {
            s32 off = (*(s32 *)(D_00356CF0 + 8) << 3) + *(s32 *)(D_00356CF0 + 0xC) * i + i;

            r = func_002FE090(arg1, arg2 + off);
            i += 1;
            if (r == 0) {
                *(s32 *)(arg0 + 0) = *(s32 *)(s1 + 0);
                *(s32 *)(arg0 + 4) = *(s32 *)(s1 + 4);
                return;
            }
            s1 += 8;
            if (!(i < arg3)) {
                break;
            }
        }
    }
    *(s32 *)(arg0 + 4) = 0;
    *(s32 *)(arg0 + 0) = 0;
}
