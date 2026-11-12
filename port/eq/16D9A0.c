#include "common.h"

s32 func_0014EFA8(s32 a0, s32 *a1, void *a2, s32 a3, s32 t0, s32 t1, s32 t2);
void func_001513D0(f32 farg0, void *a0, void *a1, void *a2, void *a3, void *t0, void *t1, s32 t2, s32 t3, s32 st0, s32 st1);

void func_0016D9A0(s32 arg0, u8 *arg1, s32 *arg2) {
    u8 *t;
    u8 *p20;
    u8 *s4;
    u8 *s1;
    u8 *s0;
    u8 *fp;
    s32 s3;
    s32 s6;
    s32 sp14;
    s32 a0v;
    s32 a1b;
    s32 v0;
    s32 v1;
    s32 flags;
    s32 cond;

    s6 = 0;
    t = *(u8 **)(arg1 + 0x38);
    fp = *(u8 **)(t + 0xB0);
    sp14 = 0;
    do {
        s4 = (u8 *)(*arg2) + sp14;
        s3 = 0;
        if (*s4 != 0) {
            s1 = s4 + 0x10;
            do {
                a1b = s1[1];
                cond = 1;
                if (a1b == 2 && ((s1[0] + 0xFF) & 0xFF) < 2) {
                    cond = 0;
                }
                if (cond) {
                    p20 = *(u8 **)(fp + 0x20);
                    if (*(s32 *)p20 == 0x157 && a1b == 4 && (s1[0] == 2 || s1[0] == a1b)) {
                        cond = 0;
                    }
                }
                if (cond) {
                    p20 = *(u8 **)(fp + 0x20);
                    v1 = *(s32 *)p20;
                    if (v1 == 0x168 && a1b == 1 && ((s1[0] + 0xFE) & 0xFF) < 2) {
                        cond = 0;
                    }
                }
                if (cond) {
                    s0 = t + 0xB4;
                    flags = *(s32 *)t;
                    v0 = func_0014EFA8(arg0, arg2, s0, s6, s3, flags & 1, flags & 4);
                    if (v0 != 0) {
                        func_001513D0(*(f32 *)(t + 0x1C), fp, arg2, s0, t + 0x860, t + 0x80, t + 0x30,
                                      s6, s3, s3, v0);
                    }
                }
                s3 += 1;
                s1 += 0x20;
            } while (s3 < *s4);
        }
        s6 += 1;
        sp14 += 0x110;
    } while (s6 < 0x10);
    (void)a0v;
}
