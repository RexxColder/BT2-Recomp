#include "common.h"

s32 func_0014EFA8(s32 a0, s32 *a1, void *a2, s32 a3, s32 t0, s32 t1, s32 t2);
s32 func_0014F2B8(s32 *a0, void *a1, s32 a2, s32 a3);
void func_001513D0(f32 farg0, void *a0, void *a1, void *a2, void *a3, void *t0, void *t1, s32 t2, s32 t3, s32 st0, s32 st1);

void func_00174E40(s32 arg0, u8 *arg1, s32 *arg2, s32 arg3) {
    s32 s3;
    s32 s6;
    s32 sp1C;
    s32 sp14;
    s32 v;
    s32 t4;
    s32 cond;
    u8 *s1;
    u8 *s2;
    u8 *s4;
    u8 *s7;
    u8 *sp18;

    s6 = 0;
    s1 = *(u8 **)(arg1 + 0x38);
    sp14 = arg3 & 0xFF;
    sp1C = 0;
    sp18 = *(u8 **)(s1 + 0xB0);
    do {
        s4 = (u8 *)(*arg2) + sp1C;
        s3 = 0;
        if (*s4 != 0) {
            s7 = s1 + 0xB4;
            s2 = s4 + 0x10;
            do {
                if (s2[1] != 2 || ((s2[0] + 0xFF) & 0xFF) >= 2) {
                    if (sp14 == 0) {
                        v = func_0014EFA8(arg0, arg2, s7, s6, s3, *(s32 *)s1 & 1, *(s32 *)s1 & 4);
                    } else {
                        v = func_0014F2B8(arg2, s7, s6, s3);
                    }
                    t4 = (*(s32 *)s1 & 0x100) ? 2 : v;
                    cond = t4;
                    if ((*(s32 *)(*(u8 **)(sp18 + 0x20)) ^ 0x75) == 0) {
                        cond = t4 | 0x48;
                    }
                    if (cond != 0) {
                        func_001513D0(*(f32 *)(s1 + 0x1C), sp18, arg2, s7, s1 + 0x860, s1 + 0x80, s1 + 0x30,
                                      s6, s3, s3, t4);
                    }
                }
                s3 += 1;
                s2 += 0x20;
            } while (s3 < *s4);
        }
        s6 += 1;
        sp1C += 0x110;
    } while (s6 < 0x10);
}
