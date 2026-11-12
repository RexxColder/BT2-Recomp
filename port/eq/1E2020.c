#include "common.h"

extern f32 D_00343258[];
extern f32 D_00343298[];
extern f32 D_003433A8[];
extern f32 D_00343318[];
extern f32 D_0038566C;
extern f32 D_00385670;

void func_001E65C8(f32 *out, u8 *base, s32 idx);
void func_00312680(f32 *out, u8 *vec, f32 s);
s32 func_001E4760(u8 a0, u8 a1, u8 a2, u8 a3, s64 hx, s64 hy, s64 unused6, s64 scaleBits,
                  s32 st0, s32 stFlag, u8 stByte, s64 *stPtr,
                  f32 fx, f32 fy, f32 fz, f32 c0, f32 c1, f32 c2, f32 c3, f32 angle);

/* float -> u32 the way the EE compiler emits it (values >= 2^31 are rebased) */
static s32 ftou(f32 x) {
    if (x >= 2147483648.0f) {
        return (s32)(x - 2147483648.0f) | (s32)0x80000000;
    }
    return (s32)x;
}

/* Variant of 1E2978: copies two by-value blocks (A 0x50 bytes, B 0x130 bytes), builds a 4-float tint from B's
   mode and calls func_001E4760; B[0x10A] selects which byte offsets feed the output slot. */
s32 func_001E2020(u8 *srcA, u8 *srcB, u8 *base, s32 colorIdx, u32 flag, f32 fc) {
    u8 A[0x50];
    u8 B[0x130];
    f32 vec1a0[4];
    f32 vec1c0[8];
    f32 c[4] = {0.0f, 0.0f, 0.0f, 0.0f};
    f32 k0;
    f32 k1;
    f32 *v;
    f32 ang;
    s64 *slot;

    __builtin_memcpy(A, srcA, 0x50);
    __builtin_memcpy(B, srcB, 0x130);
    flag &= 0xFF;
    func_001E65C8(vec1a0, base, A[0x4C]);
    k1 = 1.0f / vec1a0[1];
    k0 = (vec1a0[0] - 1.0f) / vec1a0[0];
    func_00312680(vec1c0, A + 0x20, fc);

    if (B[0x10E] != 0) {
        switch (*(s32 *)(B + 0x110)) {
        case 0:
            v = D_00343258 + colorIdx * 4;
            c[0] = v[0]; c[1] = v[1]; c[2] = v[2]; c[3] = v[3];
            break;
        case 1:
            v = D_00343298 + colorIdx * 4;
            c[0] = v[0]; c[1] = v[1]; c[2] = v[2]; c[3] = v[3];
            break;
        case 2:
            v = D_003433A8 + colorIdx * 4;
            c[0] = v[0]; c[1] = v[1]; c[2] = v[2]; c[3] = v[3];
            break;
        case 3:
            v = D_00343318 + colorIdx * 4;
            c[0] = v[0]; c[1] = v[1]; c[2] = v[2]; c[3] = v[3];
            break;
        default:
            break;
        }
    } else {
        c[1] = k1;
        c[3] = k0;
        c[0] = k1;
        c[2] = k0;
    }

    if (B[0x10A] == 0) {
        ang = *(f32 *)(A + 0x44) * D_0038566C / 180.0f;
        slot = (s64 *)(base + A[0x4C] * 16);
    } else {
        ang = *(f32 *)(A + 0x44) * D_00385670 / 180.0f;
        slot = (s64 *)(base + (B[0x108] + B[0x109]) * 16);
    }
    return func_001E4760(ftou(*(f32 *)(A + 0x30)) & 0xFF, ftou(*(f32 *)(A + 0x34)) & 0xFF,
                         ftou(*(f32 *)(A + 0x38)) & 0xFF, ftou(*(f32 *)(A + 0x3C)) & 0xFF,
                         ftou(vec1c0[0]), ftou(vec1c0[1]), 0, *(s32 *)(A + 0x40) << 12,
                         0, *(s32 *)(A + 0x48), (u8)flag, slot,
                         *(f32 *)(A + 0x10), *(f32 *)(A + 0x14), *(f32 *)(A + 0x18),
                         c[0], c[1], c[2], c[3], ang);
}
