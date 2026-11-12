#include "common.h"

s32 func_0014EFA8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
void func_001513D0(f32 farg0, s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5,
                   s32 arg6, s32 arg7, s32 stk0, s32 stk8);

void func_00172830(s32 arg0, u8 *arg1, u8 **arg2) {
    u8 *s1;
    u8 *s4;
    u8 *s2;
    u8 *s0;
    s32 s7;
    s32 s6;
    s32 s3;
    s32 sp10;
    s32 flags;
    s32 r;

    s1 = *(u8 **)(arg1 + 0x38);
    s7 = *(s32 *)(s1 + 0xA0);
    s6 = 0;
    sp10 = 0;
    do {
        s4 = *arg2 + sp10;
        s3 = 0;
        if (*s4 != 0) {
            s2 = s4 + 0x10;
            do {
                if (s2[1] != 2 || ((u32)((s2[0] + 0xFF) & 0xFF) >= 2U)) {
                    flags = *(s32 *)s1;
                    s0 = s1 + 0xA4;
                    r = func_0014EFA8(arg0, (s32)arg2, (s32)s0, s6, s3, flags & 1, flags & 4);
                    if (r != 0) {
                        func_001513D0(*(f32 *)(s1 + 0x14), s7, (s32)arg2, (s32)s0, (s32)(s1 + 0x850),
                                      (s32)(s1 + 0x70), (s32)(s1 + 0x20), s6, s3, s3, r);
                    }
                }
                s3 += 1;
                s2 += 0x20;
            } while (s3 < *s4);
        }
        s6 += 1;
        sp10 += 0x110;
    } while (s6 < 0x10);
}
