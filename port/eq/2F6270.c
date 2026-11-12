#include "common.h"

void func_002EA050(u8 *arg0);
void func_002E93C0(s32 arg0, s32 arg1);
void func_002E93D8(void);
void func_002EFE20(s32 arg0, s32 arg1);
void func_002F4960(s32 arg0, s32 arg1, s32 arg2);
extern s32 D_0034AED8 __attribute__((section(".data")));
extern s32 D_00354EC8 __attribute__((section(".data")));
extern s32 D_00354F14 __attribute__((section(".data")));
extern u8 D_0037CD88[] __attribute__((section(".data")));

void func_002F6270(u8 *arg0, s32 arg1) {
    s32 sp[2];
    s32 temp_s1_2;
    s32 temp_a0;
    s32 r;
    s32 v1;
    s32 hi;
    s8 temp_s1;
    f32 f1;
    f32 fv;
    f32 x;
    f32 t;

    if (arg0 == NULL) {
        func_002EA050(D_0037CD88);
        return;
    }

    if (arg1 == *(s8 *)(arg0 + 0x72)) {
        return;
    }
    temp_s1 = *(s8 *)(arg0 + 0x1);
    func_002E93C0((s32)arg0, arg1);
    *(u8 *)(arg0 + 0x72) = (u8)arg1;

    if ((u32)((s32)temp_s1 - 3) < 2U) {
        temp_a0 = *(s32 *)(arg0 + 0xC);
        if (arg1 == 1) {
            func_002EFE20(temp_a0, 0);
        } else {
            func_002EFE20(temp_a0, 1);
            *(s32 *)(arg0 + 0xA0) = D_0034AED8;
        }
        temp_s1_2 = D_00354EC8;
        D_00354EC8 = 0;
        func_002F4960((s32)arg0, (s32)sp, (s32)&sp[1]);
        f1 = (f32)D_00354F14;
        D_00354EC8 = temp_s1_2;

        fv = ((f32)sp[0] / (f32)sp[1]) * f1;
        if (fv >= 2147483648.0f) {
            x = fv - 2147483648.0f;
            hi = (s32)0x80000000;
        } else {
            x = fv;
            hi = 0;
        }
        /* cvt.w.s (truncates toward zero) of x */
        t = x;
        r = (s32)t;
        v1 = (s32)((u32)r | (u32)hi);
        *(s32 *)(arg0 + 0x9C) = v1;
    }
    func_002E93D8();
}
