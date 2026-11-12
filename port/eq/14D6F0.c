#include "common.h"

void func_00129C28(s32 arg0, s32 arg1);
void func_0012A360(f32 farg0, s32 arg0, s32 arg1, s32 arg2);
void func_001501C0(f32 farg0, f32 farg1, f32 farg2, f32 farg3, s32 arg0, s32 arg1, s32 arg2, s32 arg3,
                   s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8);

void func_0014D6F0(s32 arg0, u8 *arg1, u8 **arg2) {
    u8 *s5;
    u8 *fp;
    u8 *base;
    u8 *s1;
    u8 *s2;
    u8 *s3;
    u8 *s4;
    u8 *sp2C;
    s32 var_a1;
    s32 s0;
    s32 s6;
    s32 s7;
    s32 sp14;
    s32 sp18;
    s32 sp1C;
    s32 sp20;
    s32 sp24;
    s32 sp28;
    s32 v;
    s32 v0;
    f32 f13;
    f32 f15;

    sp14 = (s32)arg2;
    s5 = *(u8 **)(arg1 + 0x38);
    sp20 = 0;
    sp18 = 0;
    sp2C = s5;
    *(f32 *)(s5 + 0xAA8) = *(f32 *)(s5 + 0xAA8) - 1.0f;
    fp = *arg2 + 0x550;
    var_a1 = *(u8 *)fp;

    do {
        s7 = 0;
        sp1C = 0;
        base = sp2C + 0xAB0;
        if (!(*(s32 *)s5 & 1)) {
            if (*(f32 *)(s5 + 0xAA8) <= 0.0f && *(s32 *)(s5 + 0xAA4) == sp18) {
                s6 = 0;
                sp1C = 1;
                if (var_a1 != 0) {
                    v = *(s32 *)(sp2C + 0xBD0);
                    for (;;) {
                        if (v == 0) {
                            s6 += 1;
                            if (!(s6 < var_a1)) {
                                break;
                            }
                            v = *(s32 *)(base + 0x120 + 4 * s6);
                        } else {
                            sp1C = 0;
                            break;
                        }
                    }
                }
                if (sp1C != 0) {
                    s7 = 1;
                    sp20 = 1;
                    *(f32 *)(s5 + 0xAA8) = 4.0f;
                    var_a1 = *(u8 *)fp;
                }
            }
        } else {
            s7 = 2;
        }

        s6 = 0;
        sp28 = 0;
        if (var_a1 != 0) {
            s1 = base;
            s4 = base + 0xB0;
            s3 = base + 0x40;
            s2 = fp + 0x10;
            sp24 = (s32)(base + 0xC);
            do {
                if (*(u8 *)s2 == 2) {
                    if (sp1C != 0) {
                        s0 = sp28;
                        *(s32 *)s1 = *(s32 *)s1 | 1;
                        *(f32 *)(s1 + 0x1C) = *(f32 *)(s2 + 0xC);
                        func_00129C28((s32)s3, (s32)(s5 + 0x40));
                        func_00129C28((s32)s4, (s32)(s5 + 0x20));
                    } else {
                        s0 = s6 * 4;
                    }
                    if ((*(s32 *)s1 & 1) != 0) {
                        s7 = s7 | 0x28;
                    }
                    if (s7 != 0) {
                        f13 = *(f32 *)(s5 + 0x14);
                        f15 = *(f32 *)((u8 *)(s0 + sp24) + 0x10) * f13;
                        v0 = *(s32 *)((u8 *)(s0 + sp14) + 0x658);
                        func_001501C0(*(f32 *)(s2 + 0x8), f13, f13, f15, sp14, (s32)s2, v0,
                                      (s32)(s1 + 0x120), s7, arg0, (s32)s3, (s32)s4,
                                      (s32)(s1 + 0x1C));
                        if (*(s32 *)s1 & 1) {
                            func_0012A360(*(f32 *)(s5 + 0x10), (s32)s3, (s32)s4, (s32)s3);
                        }
                    }
                    var_a1 = *(u8 *)fp;
                }
                s6 += 1;
                s4 += 0x10;
                s3 += 0x10;
                s1 += 4;
                sp28 += 4;
                s2 += 0x20;
            } while (s6 < var_a1);
        }

        sp18 += 1;
        sp2C += 0x140;
    } while (sp18 < 8);

    if (sp20 == 1) {
        v0 = *(s32 *)(s5 + 0xAA4) + 1;
        *(s32 *)(s5 + 0xAA4) = v0;
        if (v0 >= 8) {
            *(s32 *)(s5 + 0xAA4) = 0;
        }
    }
}
