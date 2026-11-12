#include "common.h"

s32 func_0014EFA8(s32 a0, s32 a1, s32 a2, s32 a3, s32 t0, s32 t1, s32 t2);
void func_001513D0(f32 f12, s32 a0, s32 a1, s32 a2, s32 a3, s32 t0, s32 t1, s32 t2, s32 t3, s32 sp0, s32 sp8);

void func_0016B540(s32 arg0, u8 *arg1, u8 **arg2) {
    s32 sp10 = 0;
    s32 s7 = 0;
    s32 s3;
    s32 t1;
    s32 v;
    s32 ret;
    s32 t4;
    s32 *a0p;
    s32 *p;
    u8 *s1 = *(u8 **)(arg1 + 0x38);
    u8 *s5 = *(u8 **)(s1 + 0xB0);
    u8 *s4;
    u8 *s2;
    u8 *s0;
    int docall;

    do {
        s4 = *arg2 + sp10;
        s3 = 0;
        if (*s4 != 0) {
            s2 = s4 + 0x11;
            do {
                t1 = *(s32 *)s1;
                a0p = *(s32 **)(s5 + 0x20);
                v = *a0p;
                if (v == 0x97 && (t1 & 0x4000) && *s2 == 4) {
                    docall = 0;
                } else if (v == 0x62 || v == 0x98) {
                    docall = (!(t1 & 0x4000)) || (*s2 != 1);
                } else {
                    docall = 1;
                }
                if (docall) {
                    s0 = s1 + 0xB4;
                    ret = func_0014EFA8(arg0, (s32)arg2, (s32)s0, s7, s3, t1 & 1, t1 & 4);
                    if (ret != 0) {
                        t4 = ret;
                        p = *(s32 **)(s5 + 0x20);
                        if ((*p ^ 0x134) == 0) {
                            t4 = ret | 0x40;
                        }
                        func_001513D0(*(f32 *)(s1 + 0x20), (s32)s5, (s32)arg2, (s32)s0,
                                      (s32)(s1 + 0x860), (s32)(s1 + 0x80), (s32)(s1 + 0x30),
                                      s7, s3, s3, t4);
                    }
                }
                s3 += 1;
                s2 += 0x20;
            } while (s3 < (s32)*s4);
        }
        s7 += 1;
        sp10 += 0x110;
    } while (s7 < 0x10);
}
