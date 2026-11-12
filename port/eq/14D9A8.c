#include "common.h"

s32 func_0014D620(s32 a0, s32 a1);
void func_0014D6F0(s32 a0, s32 a1, s32 a2);
s32 func_0014EFA8(s32 a0, s32 a1, s32 a2, s32 a3, s32 t0, s32 t1, s32 t2);
void func_001513D0(f32 f12, s32 a0, s32 a1, s32 a2, s32 a3, s32 t0, s32 t1, s32 t2, s32 t3, s32 sp0, s32 sp8);

s32 func_0014D9A8(s32 arg0, u8 *arg1, u8 **arg2) {
    s32 sp14;
    s32 s4;
    s32 s2;
    s32 r;
    s32 fp;
    u8 *s0;
    u8 *s1;
    u8 *s3;
    u8 *s5;

    s4 = 0;
    s0 = *(u8 **)(arg1 + 0x38);
    sp14 = 0;
    fp = *(s32 *)(s0 + 0xA0);
    do {
        s3 = *arg2 + sp14;
        s2 = 0;
        if (*s3 != 0) {
            s5 = s0 + 0xA4;
            s1 = s3 + 0x10;
            do {
                r = func_0014EFA8(arg0, (s32)arg2, (s32)s5, s4, s2, *(s32 *)s0 & 1, *(s32 *)s0 & 4);
                if (r != 0) {
                    if (s4 != 5 || *s1 != 2) {
                        func_001513D0(*(f32 *)(s0 + 0x14), fp, (s32)arg2, (s32)s5,
                                      (s32)(s0 + 0x850), (s32)(s0 + 0x70), (s32)(s0 + 0x20),
                                      s4, s2, s2, r);
                    } else {
                        *(u8 *)(s0 + 0xAA0) = 1;
                    }
                }
                s2 += 1;
                s1 += 0x20;
            } while (s2 < (s32)*s3);
        }
        s4 += 1;
        sp14 += 0x110;
    } while (s4 < 0x10);
    if (*(u8 *)(s0 + 0xAA0) == 1) {
        func_0014D6F0(arg0, (s32)arg1, (s32)arg2);
        return func_0014D620((s32)arg1, (s32)arg2);
    }
    return 1;
}
