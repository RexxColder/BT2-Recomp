#include "common.h"

s32 func_0026EB60(s32 arg0);
s32 func_0026EB70(s32 arg0);
f32 func_0028C610(s32 arg0, s32 arg1, s32 arg2);
void func_00298548(s32 arg0, s32 arg1);
void func_00298660(s32 arg0, s32 arg1);
extern f32 D_00387210;
extern f32 D_00387214;
extern f32 D_00387218;
extern f32 D_0038721C;
extern f32 D_00387220;
extern u8 D_0038B058[] __attribute__((section(".data")));

void func_00299110(void) {
    u8 *s0;
    s32 s1;
    s32 a1;
    s32 old;
    s32 cond;
    f32 f1;
    f32 f20;
    f32 f21;
    f32 f22;

    if ((D_0038B058[0] & 2) != 0) {
        return;
    }
    if ((D_0038B058[0] & 4) != 0) {
        if ((func_0026EB70(*(s32 *)(D_0038B058 + 8)) & 0x200) != 0) {
            D_0038B058[0] = (u8)(D_0038B058[0] ^ 4);
        }
        return;
    }

    s0 = D_0038B058 + 2;
    if (func_0026EB60(*(s32 *)(D_0038B058 + 8)) == 0) {
        return;
    }
    f21 = D_00387210;
    f22 = D_00387214;
    s1 = 0;
    do {
        f20 = func_0028C610(s1, 0x40000, 0x1E);
        f1 = func_0028C610(s1, 0x80000, 0x1E);
        cond = 0;
        if (f21 <= f20) {
            if (f21 <= f1) {
                if (*s0 == 0) {
                    a1 = 6;
                    goto block41;
                }
                goto block43;
            }
            cond = 1;
        }
        if (cond && f1 <= f22) {
            if (*s0 == 0) {
                a1 = 4;
                goto block41;
            }
            goto block43;
        }
        if (f20 <= f22 && f21 <= f1) {
            if (*s0 == 0) {
                a1 = 0;
                goto block41;
            }
            goto block43;
        }
        if (f20 <= D_00387218 && f1 <= D_00387218) {
            if (*s0 == 0) {
                a1 = 2;
                goto block41;
            }
            goto block43;
        }
        if (f1 <= D_0038721C) {
            if (*s0 == 0) {
                a1 = 3;
                goto block41;
            }
            goto block43;
        }
        if (0.5f <= f1) {
            if (*s0 == 0) {
                func_00298660(s1, 3);
                *s0 = 1;
            }
            goto block43;
        }
        if (f20 <= D_0038721C) {
            if (*s0 == 0) {
                a1 = 1;
                goto block41;
            }
            goto block43;
        }
        if (!(D_00387220 <= f20)) {
            *s0 = 0;
            goto block43;
        }
        if (*s0 == 0) {
            a1 = 5;
            goto block41;
        }
        goto block43;

block41:
        /* the asm passes the old s1 in a0 and increments s1 in the jal's delay slot */
        old = s1;
        s1 = old + 1;
        func_00298548(old, a1);
        *s0 = 1;
        s0 += 1;
        continue;

block43:
        s1 += 1;
        s0 += 1;
    } while (s1 < 2);
}
