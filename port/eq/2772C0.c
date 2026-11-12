#include "common.h"

s32 rand(void);
f32 func_0020B4E8(void);
void func_00276FD0(f32 farg0);
void func_00297FE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
extern f32 D_00387030;
extern f32 D_00387034;
extern f32 D_00387038;
extern u8 *D_003876A0;
extern s32 D_00388D68[] __attribute__((section(".data")));

void func_002772C0(void) {
    u8 *p;
    s32 a0;
    s32 v;
    s32 r;
    s32 s0;
    s32 tr;
    f32 f;
    f32 f12;

    p = (u8 *)&D_00388D68;

    a0 = *(s32 *)(p + 0xC);
    if (a0 == 0) {
        a0 = (rand() % 90) + 0x5A;
        *(s32 *)(p + 0xC) = a0;
    }
    v = a0 - 1;
    *(s32 *)(p + 0xC) = v;

    if (v <= 0) {
        r = rand();
        a0 = (r % 90) + 0x5A;
        *(s32 *)(p + 0xC) = a0;
        r = rand();
        f = (f32)r / D_00387030;
        f = f * 62.0f;
        /* cvt.w.s: truncates toward zero */
        tr = (s32)f;
        s0 = tr;
        r = rand();
        func_00297FE0(2, 0xA, (s0 + 0x3F) >> 2, r % 127, 0);
    }

    if (*(s64 *)(D_003876A0 + 0x4D8) & 8) {
        func_00276FD0(D_00387034);
        return;
    }
    f12 = (func_0020B4E8() * 1.25f) + D_00387038;
    if (1.0f < f12) {
        f12 = 1.0f;
    }
    func_00276FD0(f12);
}
