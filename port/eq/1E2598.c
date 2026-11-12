#include "common.h"

extern void func_001E65C8(f32 *out, u8 *src, s32 idx);
extern void func_00312680(f32 f12, f32 *out, f32 *in);
extern s32 func_001F23B8(s32 a0, s32 a1, s32 a2, s32 a3, s32 t0, s32 t1, s32 t2, s32 t3,
                         f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, f32 f17, f32 f18, f32 f19,
                         f32 st0, f32 st1, f32 st2, s32 st3, s32 st4, s32 st5, u8 *st6);
extern f32 D_00343258[];
extern f32 D_00343298[];
extern f32 D_00343318[];
extern f32 D_003433A8[];
extern f32 D_00385674;

/* float -> u32 conversion with the 2^31 split */
static u32 f2u(f32 v) {
    u32 r = (u32)(s32)v;
    if (v >= 2147483648.0f) {
        r = (u32)(s32)(v - 2147483648.0f) | 0x80000000;
    }
    return r;
}

/* GUESS arity: the first two floats (f12, f13) are passed through */
s32 func_001E2598(f32 fa, f32 fb, u8 *a, u8 *b, u8 *tbl, s32 idx, s32 flag) {
    u8 objA[0x50];
    u8 objB[0x120];
    f32 outA[4];
    f32 outB[4];
    f32 vec[4];
    f32 inv;
    f32 ratio;
    f32 *ent;
    s32 mask = flag & 0xFF;

    __builtin_memcpy(objA, a, 0x50);
    __builtin_memcpy(objB, b, 0x120);
    func_001E65C8(outA, tbl, objA[0x4C]);
    inv = 1.0f / outA[1];
    ratio = (outA[0] - 1.0f) / outA[0];
    func_00312680(fa, outB, (f32 *)(objA + 0x20));
    if (objB[0x10E] != 0) {
        switch (*(s32 *)(objB + 0x110)) {
        case 0: ent = D_00343258 + idx * 4; break;
        case 1: ent = D_00343298 + idx * 4; break;
        case 2: ent = D_003433A8 + idx * 4; break;
        case 3: ent = D_00343318 + idx * 4; break;
        default: ent = NULL; break;
        }
        if (ent != NULL) {
            vec[0] = ent[0];
            vec[1] = ent[1];
            vec[2] = ent[2];
            vec[3] = ent[3];
        }
    } else {
        vec[1] = inv;
        vec[3] = ratio;
        vec[0] = inv;
        vec[2] = ratio;
    }
    return func_001F23B8(f2u(*(f32 *)(objA + 0x30)) & 0xFF,
                         f2u(*(f32 *)(objA + 0x34)) & 0xFF,
                         f2u(*(f32 *)(objA + 0x38)) & 0xFF,
                         f2u(*(f32 *)(objA + 0x3C)) & 0xFF,
                         f2u(outB[0]), f2u(outB[1]), 0,
                         *(s32 *)(objA + 0x40) << 12,
                         *(f32 *)(objA + 0x10), *(f32 *)(objA + 0x14), *(f32 *)(objA + 0x18),
                         0.0f, 0.0f, fb, vec[0], vec[1],
                         vec[2], vec[3],
                         (*(f32 *)(objA + 0x44) * D_00385674) / 180.0f,
                         0, *(s32 *)(objA + 0x48), mask,
                         tbl + (objA[0x4C] << 4));
}
