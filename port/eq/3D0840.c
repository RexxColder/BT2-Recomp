#include "common.h"

extern u8 *D_00423120 __attribute__((section(".data")));
extern u8 D_003B0B00[] __attribute__((section(".data")));

s32 func_26EB60(u8 *arg0);
void func_003D7BE8(u8 *arg0);
void func_297FE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

/* 0x003D0840 (G = D_00423120, C = D_003B0B00): if func_26EB60(G+0xF8) == 0 return; if !(G->0x2BC & 4) return;
 * a0 = C->0x12C. If a0 & 0x80: G->0x3330 (float) < 0 -> G->0x3330 = min(G->0x3330 + 3, 0). Else if a0 & 0x20:
 * if (float)G->0x3328 < G->0x3330: G->0x3330 -= 3, then clamp below at (float)G->0x3328. Else: return if
 * !(C->0x134 & 0x4000) or (G->0x2BC & 0x100). If G->0x2BC & 0x80: when G->0x3310 == 0, G->0x2BC = flags | 2,
 * G->0x3308 = 0xF, *arg0 = 0. Else func_003D7BE8(G) and G->0x2BC ^= 4. Then func_297FE0(0,1,0x40,0x40,1). */
void func_003D0840(s32 *arg0) {
    u8 *g;
    s32 flags;
    s32 a0v;
    f32 f0;
    f32 f1;

    if (func_26EB60(D_00423120 + 0xF8) == 0) {
        return;
    }
    g = D_00423120;
    flags = *(s32 *)(g + 0x2BC);
    if (!(flags & 0x4)) {
        return;
    }
    a0v = *(s32 *)(D_003B0B00 + 0x12C);
    if (a0v & 0x80) {
        f1 = *(f32 *)(g + 0x3330);
        if (f1 < 0.0f) {
            f1 = f1 + 3.0f;
            *(f32 *)(g + 0x3330) = f1;
            if (0.0f < *(f32 *)(g + 0x3330)) {
                *(f32 *)(g + 0x3330) = 0.0f;
            }
        }
        return;
    }
    if (a0v & 0x20) {
        f0 = (f32)*(s32 *)(g + 0x3328);
        f1 = *(f32 *)(g + 0x3330);
        if (f0 < f1) {
            *(f32 *)(g + 0x3330) = f1 - 3.0f;
            f1 = (f32)*(s32 *)(g + 0x3328);
            if (*(f32 *)(g + 0x3330) < f1) {
                *(f32 *)(g + 0x3330) = f1;
            }
        }
        return;
    }
    if (!(*(s32 *)(D_003B0B00 + 0x134) & 0x4000)) {
        return;
    }
    if (flags & 0x100) {
        return;
    }
    if (flags & 0x80) {
        if (*(s32 *)(g + 0x3310) == 0) {
            *(s32 *)(g + 0x2BC) = flags | 0x2;
            *(s32 *)(g + 0x3308) = 0xF;
            *(s32 *)arg0 = 0;
        }
    } else {
        func_003D7BE8(g);
        *(s32 *)(g + 0x2BC) = *(s32 *)(g + 0x2BC) ^ 0x4;
    }
    func_297FE0(0, 1, 0x40, 0x40, 1);
}
