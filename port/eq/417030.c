#include "common.h"

extern u8 *D_0042BB7C __attribute__((section(".data")));
extern u8 *D_003876A4 __attribute__((section(".data")));
extern u8 *D_003876AC __attribute__((section(".data")));

u8 *func_100D58(void *a0, s32 a1, s32 a2);
s32 func_243A80(s32 a0, s32 a1, s32 a2);
void func_29BD28(s32 a0);
s32 func_250978(s32 a0);
void func_2539C8(s32 a0);
void func_243968(s32 a0, s32 a1, s32 a2);
void func_28BB60(void *a0);
s32 func_29BB88(void *a0, s32 a1);

s32 func_00417030(void) {
    u8 *b;
    u8 *t;
    u8 *g4;
    s32 f;
    s32 s3;
    s32 s4;
    s32 st;
    s32 x;
    s32 v;
    s32 a3;
    s32 off1;
    s32 off2;
    u32 w1;
    u32 w2;

    b = D_0042BB7C;
    f = *(s32 *)(b + 0x238);
    if ((f & 0x10000) == 0) {
        *(s32 *)(b + 0x238) = f | 0x10000;
        t = D_003876A4;
        func_100D58(*(u8 **)(t + 4) + 0xE, 0, 1);
        return func_243A80(0, 0, 0);
    }

    if ((f & 0x20000) != 0) {
        return 0x20000;
    }

    D_003876AC = func_100D58(0, 0, 0);
    if (D_003876AC == 0) {
        return 0;
    }
    *(s32 *)(b + 0x238) = *(s32 *)(b + 0x238) | 0x20000;

    b = D_0042BB7C;
    f = *(s32 *)(b + 0x238);
    if ((f & 0x4000) != 0) {
        if (*(s32 *)(b + 0x3740) == 2) {
            t = D_003876A4;
            *(s32 *)(t + 0x48C) = *(s32 *)(t + 0x48C) | 0x20;
        }
    } else if ((f & 0x8000) != 0) {
        t = D_003876A4;
        if (*(s32 *)(b + 0x3740) == 1) {
            *(s32 *)(t + 0x48C) = *(s32 *)(t + 0x48C) | 1;
        } else {
            *(s32 *)(t + 0x48C) = *(s32 *)(t + 0x48C) | 0x20;
        }
        *(s32 *)(t + 0x48C) = *(s32 *)(t + 0x48C) | 2;
    }

    /* L417198 */
    t = D_003876A4;
    a3 = *(s32 *)(t + 0x48C) & 2;
    s3 = 0;
    b = D_0042BB7C;
    x = *(s32 *)(b + 0xC + ((a3 != 0) ? 0x294 : 0x290));
    s4 = 1;
    v = (x < 2) ? x : 1;
    off1 = 4 * v + ((a3 != 0) ? 0x248 : 0x240);
    off2 = 4 * v + ((a3 != 0) ? 0x238 : 0x230);
    w1 = *(u32 *)(b + 0xC + off1);
    w2 = *(u32 *)(b + 0xC + off2);
    *(u32 *)(t + 0x494) = w2 + 7 * w1;

    t = D_003876A4;
    s3 = *(s32 *)(t + 0x1C);
    *(s32 *)(t + 0x1C) = 0x37;
    func_29BD28(4 * v + 0x230);

    while (s4 != 0) {
        t = D_003876A4;
        st = *(s32 *)(t + 0x1C);
        if (st == 0x37) {
            if (func_250978(1) == 0) {
                s4 = 0;
            } else {
                *(s32 *)(D_003876A4 + 0x1C) = 0x38;
            }
        } else if (st == 0x38) {
            func_2539C8(2);
            *(s32 *)(D_003876A4 + 0x1C) = 0x37;
        }
    }

    t = D_003876A4;
    *(s32 *)(t + 0x1C) = s3;

    b = D_0042BB7C;
    f = *(s32 *)(b + 0x238);
    if ((f & 0x4000) != 0) {
        *(s32 *)(b + 0x238) = f ^ 0x4000;
    } else if ((f & 0x8000) != 0) {
        *(s32 *)(b + 0x238) = f ^ 0x8000;
    }

    b = D_0042BB7C;
    *(s32 *)(b + 0x238) = *(s32 *)(b + 0x238) & (s32)0xFFFEFFFF;

    b = D_0042BB7C;
    *(s32 *)(b + 0x238) = *(s32 *)(b + 0x238) & (s32)0xFFFDFFFF;

    t = D_003876A4;
    *(s32 *)(t + 0x48C) = *(s32 *)(t + 0x48C) & -2;
    *(s32 *)(t + 0x48C) = *(s32 *)(t + 0x48C) & -3;
    *(s32 *)(t + 0x48C) = *(s32 *)(t + 0x48C) & -0x21;
    func_243968(0, 0, 0);

    func_28BB60(D_003876AC);
    D_003876AC = 0;

    b = D_0042BB7C;
    g4 = *(u8 **)(b + 4);
    return func_29BB88(g4 + (*(u32 *)(g4 + 0x6C) & ~3u), *(s32 *)(b + 0x34));
}
