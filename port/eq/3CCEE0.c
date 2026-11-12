#include "common.h"

extern u8 *D_00423118 __attribute__((section(".data")));
extern u8 D_00424CC8[] __attribute__((section(".data")));
extern s32 D_003B0C34 __attribute__((section(".data")));

s32 func_001018B8(void);
void func_002493C0(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
void func_0026E9E8(u8 *a0);
s32 func_0026EB70(u8 *a0);
void func_0026EB78(u8 *a0, u8 *a1);
s32 func_00297FE0(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);

/* 0x003CCEE0: per-frame state machine on the object at D_00423118 (state word at +0x144,
   flags at +0x134, sub-state at +0x148). Returns the value left in v0 by the matching path. */
s32 func_003CCEE0(void) {
    u8 *obj;
    s32 flags;
    s32 s1;
    s32 s0;
    s32 ret;
    s32 n;

    obj = D_00423118;
    if ((u32)*(s32 *)(obj + 0x144) < 2) {
        if (*(s32 *)(obj + 0x158) != 0) {
            if (func_001018B8() == 5) {
                *(s32 *)(obj + 0x144) = *(s32 *)(obj + 0x138) + 2;
                func_002493C0(*(s32 *)(obj + 0x8), 0x342E, 0x3847, 0, *(s32 *)(obj + 0x144));
            }
        }
    }
    flags = *(s32 *)(obj + 0x134);

    s1 = 0;
    if (flags & 0x200) {
        if (func_001018B8() != 5) {
            s0 = 3;
            goto loop;
        }
        {
            u32 a1v = *(u32 *)(obj + 0x180 + *(s32 *)(obj + 0x138) * 4);
            if (a1v > 0x7A11F) {
                n = (a1v > 0xF423F) ? 17 : 16;
            } else {
                n = 15;
            }
        }
        *(s32 *)(obj + 0x144) = n;
        func_002493C0(*(s32 *)(obj + 0x8), 0x342E, 0x3847, 0, *(s32 *)(obj + 0x144));
        *(s32 *)(obj + 0x134) ^= 0x200;
        s1 = 0;
    }
    s0 = 3;
loop:
    /* 4 iterations, s0 = 2,1,0,-1 after decrement; each call gets obj + s1 + 0x10, s1 += 0x28 */
    do {
        s0 -= 1;
        func_0026E9E8(obj + s1 + 0x10);
        s1 += 0x28;
    } while (s0 >= 0);

    if (func_0026EB70(obj + 0x38) & 0x200) {
        *(s32 *)(obj + 0x134) |= 0x4000;
    }

    ret = 2;
    if (*(s32 *)(obj + 0x148) != 0) {
        if (*(s32 *)(obj + 0x148) == 2) {
            if (func_001018B8() == 5) {
                *(s32 *)(obj + 0x148) += 1;
                return *(s32 *)(obj + 0x148);
            }
            if (D_003B0C34 & 0x4000) {
                *(s32 *)(obj + 0x148) = 3;
                return func_00297FE0(0, 1, 64, 64, 1);
            }
            ret = D_003B0C34 & 0x1000;
            if (ret == 0) {
                return ret;
            }
            *(s32 *)(obj + 0x148) = 0;
            *(s32 *)(obj + 0x144) = 5;
            func_002493C0(*(s32 *)(obj + 0x8), 0x342E, 0x3847, 0, 5);
            return func_00297FE0(0, 2, 64, 64, 1);
        } else if (*(s32 *)(obj + 0x148) >= 3) {
            ret = 3;
            if (*(s32 *)(obj + 0x148) == 3) {
                *(s32 *)(obj + 0x148) = 0;
                *(s32 *)(obj + 0x134) |= 1;
                *(s32 *)(obj + 0x134) |= 2;
                *(s32 *)(obj + 0x154) = 15;
                func_00297FE0(2, 11, 64, 64, 1);
                func_0026EB78(obj + 0x38, D_00424CC8);
                *(s32 *)(obj + 0xC0) = 0;
                /* asm: v0 still holds obj here (lw v0,0(s0) before the sw), returned as-is */
                return (s32)(long)obj;
            }
        } else {
            ret = 6;
            if (*(s32 *)(obj + 0x148) == 1) {
                *(s32 *)(obj + 0x144) = 6;
                func_002493C0(*(s32 *)(obj + 0x8), 0x342E, 0x3847, 0, 6);
                *(s32 *)(obj + 0x148) += 1;
                *(s32 *)(obj + 0x134) |= 0x8000;
                return *(s32 *)(obj + 0x134);
            }
        }
    }
    return ret;
}
