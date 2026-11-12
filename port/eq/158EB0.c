#include "common.h"

s32 func_0014EFA8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
void func_001513D0(f32 farg0, s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5,
                   s32 arg6, s32 arg7, s32 stk0, s32 stk8);

void func_00158EB0(s32 arg0, u8 *arg1, s32 *arg2) {
    s32 s6;
    s32 sp10;
    s32 s7;
    s32 s2;
    s32 flags;
    s32 e;
    s32 r;
    u8 *s1;
    u8 *s4;
    u8 *s3;
    u8 v0;

    s6 = 0;
    s1 = *(u8 **)(arg1 + 0x38);
    s7 = *(s32 *)(s1 + 8);
    sp10 = 0;
    do {
        s4 = (u8 *)(arg2[0] + sp10);
        s2 = 0;
        if (*s4 != 0) {
            s3 = s4 + 0x11;
            v0 = *s3;
            for (;;) {
                s3 += 0x20;
                if (v0 != 1) {
                    flags = *(s32 *)s1;
                    r = func_0014EFA8(arg0, (s32)arg2, (s32)(s1 + 0xB0), s6, s2, flags & 1, flags & 4);
                    flags = *(s32 *)s1;
                    e = (flags & 0x100) ? 2 : r;
                    if (e != 0) {
                        func_001513D0(*(f32 *)(*(u8 **)(*(u8 **)(s1 + 8) + 0x24) + 4), s7, (s32)arg2,
                                      (s32)(s1 + 0xB0), (s32)(s1 + 0x860), (s32)(s1 + 0x80),
                                      (s32)(s1 + 0x30), s6, s2, s2, e);
                    }
                }
                s2 += 1;
                if (s2 < (s32)*s4) {
                    v0 = *s3;
                    continue;
                }
                break;
            }
        }
        s6 += 1;
        sp10 += 0x110;
    } while (s6 < 0x10);
}
