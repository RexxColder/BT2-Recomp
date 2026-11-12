#include "common.h"

extern u8 *D_0042732C __attribute__((section(".data")));

s32 func_26EB70(u8 *a0, u8 *a1, u8 *a2, void *a3);
void func_26E9E8(u8 *p);
void func_2493C0(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);

/* 0x003DDC88: per-frame update of G = D_0042732C. Moves G->0x758 toward G->0x754 * G->0x75C by 0.2 * G->0x75C per
 * frame (clamped at the product), steps the float G->0x76C by +-0.075 (clamped to [0,1] by the sign test), then
 * func_26EB70(G+0x2C, a1, G, &D); if it returns bit 0x200, func_2493C0(G->0x14, 0x3422, 0x383B, 0, G->0x10C).
 * Finally G->0x770 counts down to 0 and func_26E9E8(G+0x2C). a1 is G on the moving paths and G->0x758 when equal. */
void func_003DDC88(void) {
    u8 *g;
    s32 t;
    s32 prod;
    u8 *a1;
    f32 f;
    s32 cond;
    f32 target;

    g = D_0042732C;
    t = *(s32 *)(g + 0x758);
    prod = (s32)((s64)*(s32 *)(g + 0x754) * *(s32 *)(g + 0x75C));
    if (prod < t) {
        f = (f32)*(s32 *)(g + 0x75C) * 0x1.999998p-3f;
        *(s32 *)(g + 0x758) = t - (s32)f;
        if (*(s32 *)(g + 0x758) < prod) {
            *(s32 *)(g + 0x758) = prod;
        }
        a1 = g;
    } else if (t < prod) {
        f = (f32)*(s32 *)(g + 0x75C) * 0x1.999998p-3f;
        *(s32 *)(g + 0x758) = t + (s32)f;
        if (prod < *(s32 *)(g + 0x758)) {
            *(s32 *)(g + 0x758) = prod;
        }
        a1 = g;
    } else {
        a1 = (u8 *)0 + (u32)t;
    }

    if (*(s32 *)(g + 0x108) & 0x40) {
        *(f32 *)(g + 0x76C) = *(f32 *)(g + 0x76C) + 0x1.333332p-4f;
        target = 1.0f;
        cond = 1.0f < *(f32 *)(g + 0x76C);
    } else {
        *(f32 *)(g + 0x76C) = *(f32 *)(g + 0x76C) - 0x1.333332p-4f;
        target = 0.0f;
        cond = *(f32 *)(g + 0x76C) < 0.0f;
    }
    if (cond) {
        *(f32 *)(g + 0x76C) = target;
    }

    if (func_26EB70(g + 0x2C, a1, g, (void *)&D_0042732C) & 0x200) {
        func_2493C0(*(s32 *)(g + 0x14), 0x3422, 0x383B, 0, *(s32 *)(g + 0x10C));
    }

    if (*(s32 *)(g + 0x770) > 0) {
        *(s32 *)(g + 0x770) = *(s32 *)(g + 0x770) - 1;
    }
    func_26E9E8(g + 0x2C);
}
