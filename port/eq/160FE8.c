#include "common.h"

s32 func_0014EFA8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
s32 func_0014F2B8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_001513D0(f32 farg0, s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6,
                   s32 arg7, s32 arg8, s32 arg9);

void func_00160FE8(s32 arg0, u8 *arg1, s32 *arg2, s32 arg3) {
    u8 *s0;
    u8 *s2;
    u8 *s5;
    s32 s1;
    s32 s4;
    s32 s6;
    s32 sp10;
    s32 v;
    s32 flags;
    s32 r;

    s0 = *(u8 **)(arg1 + 0x38);
    s6 = *(s32 *)(s0 + 0xB0);
    s4 = 0;
    sp10 = 0;
    do {
        s5 = (u8 *)(*arg2 + sp10);
        s1 = 0;
        if (*s5 != 0) {
            s2 = s0 + 0xB4;
            do {
                if ((arg3 & 0xFF) != 0) {
                    v = func_0014F2B8((s32)arg2, (s32)s2, s4, s1);
                } else {
                    flags = *(s32 *)s0;
                    v = func_0014EFA8(arg0, (s32)arg2, (s32)s2, s4, s1, flags & 1, flags & 4);
                }
                r = ((*(s32 *)s0 & 0x100) != 0) ? 2 : v;
                if (r != 0) {
                    func_001513D0(*(f32 *)(s0 + 0x18), s6, (s32)arg2, (s32)s2, (s32)(s0 + 0x860),
                                  (s32)(s0 + 0x80), (s32)(s0 + 0x30), s4, s1, s1, r);
                }
                s1 += 1;
            } while (s1 < (s32)*s5);
        }
        s4 += 1;
        sp10 += 0x110;
    } while (s4 < 0x10);
}
