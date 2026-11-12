#include "common.h"

void func_00129C28(void *arg0, void *arg1);
s32 func_0014EFA8(s32 a0, void *a1, void *a2, s32 a3, s32 t0, s32 t1, s32 t2);
void func_001513D0(f32 farg0, s32 a0, void *a1, void *a2, void *a3, void *t0, void *t1, s32 t2, s32 t3, s32 st0, s32 st1);

void func_0015F718(s32 arg0, u8 *arg1, s32 *arg2) {
    u8 sp10[16];
    s32 sp24;
    s32 sp28;
    s32 sp2C;
    s32 s2;
    s32 s3;
    s32 s6;
    s32 fp;
    s32 t2;
    s32 v0;
    s32 v1;
    u8 *s0;
    u8 *s1;
    u8 *s4;
    u8 *s5;

    s0 = *(u8 **)(arg1 + 0x38);
    sp24 = *(s32 *)(s0 + 0xF0);
    func_00129C28(sp10, s0 + 0x80);
    v1 = *(s32 *)s0;
    sp28 = 0;
    sp2C = 0;
    s3 = v1 & 1;
    if (v1 & 0x200) {
        if (!(v1 & 0x400)) {
            *(s32 *)s0 = v1 | 0x400;
        } else {
            func_00129C28(sp10, s0 + 0xC0);
            sp2C = 1;
            s3 = *(s32 *)s0 & 0x100;
            sp28 = s3;
        }
    }

    s6 = 0;
    fp = 0;
    do {
        s4 = (u8 *)(*arg2) + fp;
        s2 = 0;
        if (*s4 != 0) {
            s5 = s0 + 0xF4;
            s1 = s4 + 0x18;
            do {
                t2 = *(s32 *)s0 & 4;
                if (sp2C != 0) {
                    s3 = sp28;
                    if (*(u8 *)(s1 - 6) == 0 && *(f32 *)s1 > 0.0f) {
                        s3 = 0;
                        t2 = 0;
                    }
                }
                v0 = func_0014EFA8(arg0, arg2, s5, s6, s2, s3, t2);
                if (v0 != 0) {
                    func_001513D0(*(f32 *)(s0 + 0x1C), sp24, arg2, s5, s0 + 0x8A0, sp10, s0 + 0x30,
                                  s6, s2, s2, v0);
                }
                s2 += 1;
                s1 += 0x20;
            } while (s2 < *s4);
        }
        s6 += 1;
        fp += 0x110;
    } while (s6 < 0x10);
}
