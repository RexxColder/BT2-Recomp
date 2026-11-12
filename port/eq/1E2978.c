#include "common.h"

extern f32 D_00343258[];
extern f32 D_00343298[];
extern f32 D_003433A8[];
extern f32 D_00343318[];
extern f32 D_00385678;
extern f32 D_0038567C;

extern void func_001E65C8(f32 *out, u8 *base, s32 idx);
extern void func_00312680(f32 *out, u8 *vec, f32 s);
extern void func_001E4258(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7,
                          s32 s0, s32 s1, s32 s2, s32 s3, s32 s4, s32 s5, s32 s6, s32 s7,
                          f32 f0, f32 f1, f32 f2, f32 f3, f32 f4, f32 f5, f32 f6, f32 f7);
extern void func_001E4750(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7,
                          s32 s0, s32 s1, s32 s2, s32 s3, s32 s4, s32 s5, s32 s6, s32 s7,
                          f32 f0, f32 f1, f32 f2, f32 f3, f32 f4, f32 f5, f32 f6, f32 f7);

/* float -> u32 the way the EE compiler emits it (values >= 2^31 are rebased) */
static s32 ftou(f32 x) {
    if (x >= 2147483648.0f) {
        return (s32)(x - 2147483648.0f) | (s32)0x80000000;
    }
    return (s32)x;
}

/* Queues one textured quad/sprite for an effect: copies the two by-value parameter blocks (0x50 and 0x130
   bytes), derives a 4-float tint/scale from a table chosen by block B's mode, then calls the 1E4258 variant
   (B[0x10A] == 0) or the 1E4750 variant. */
void func_001E2978(u8 *srcA, u8 *srcB, s32 colorIdx, u8 *base, u32 flag, f32 fa, f32 fb, f32 fc) {
    u8 A[0x50];
    u8 B[0x130];
    f32 vec1c0[8];
    f32 vec1e0[4];
    f32 c[4];
    u8 buf[0x10];
    f32 k0, k1;
    f32 *v;
    f32 ang;

    __builtin_memcpy(A, srcA, 0x50);
    __builtin_memcpy(B, srcB, 0x130);
    flag &= 0xFF;
    func_001E65C8(vec1c0, base, A[0x4C]);
    k1 = 1.0f / vec1c0[1];
    k0 = (vec1c0[0] - 1.0f) / vec1c0[0];
    func_00312680(vec1e0, A + 0x20, fc);
    if (B[0x10E] == 0) {
        c[3] = k1;
        c[1] = k0;
        c[2] = k1;
        c[0] = k0;
    } else {
        switch (*(s32 *)(B + 0x110)) {
        case 0:
            v = D_00343258 + colorIdx * 4;
            c[2] = v[0]; c[3] = v[1]; c[0] = v[2]; c[1] = v[3];
            break;
        case 1:
            v = D_00343298 + colorIdx * 4;
            c[2] = v[0]; c[3] = v[1]; c[0] = v[2]; c[1] = v[3];
            break;
        case 2:
            v = D_003433A8 + colorIdx * 4;
            c[2] = v[0]; c[3] = v[1]; c[0] = v[2]; c[1] = v[3];
            break;
        case 3:
            v = D_00343318 + colorIdx * 4;
            c[0] = v[0]; c[1] = v[1]; c[2] = v[2]; c[3] = v[3];
            break;
        default:
            break;
        }
    }
    if (B[0x10A] == 0) {
        ang = *(f32 *)(A + 0x44) * D_00385678 / 180.0f;
        func_001E4258(ftou(*(f32 *)(A + 0x30)) & 0xFF, ftou(*(f32 *)(A + 0x34)) & 0xFF,
                      ftou(*(f32 *)(A + 0x38)) & 0xFF, ftou(*(f32 *)(A + 0x3C)) & 0xFF,
                      ftou(fa), ftou(fb), ftou(vec1e0[0]), ftou(vec1e0[1]),
                      0, *(s32 *)(A + 0x40) << 12, 0, *(s32 *)(A + 0x48),
                      (s32)flag, 0, (s32)buf, (s32)(base + A[0x4C] * 16),
                      *(f32 *)(A + 0x10), *(f32 *)(A + 0x14), *(f32 *)(A + 0x18),
                      c[0], c[1], c[2], c[3], ang);
    } else {
        ang = *(f32 *)(A + 0x44) * D_0038567C / 180.0f;
        func_001E4750(ftou(*(f32 *)(A + 0x30)) & 0xFF, ftou(*(f32 *)(A + 0x34)) & 0xFF,
                      ftou(*(f32 *)(A + 0x38)) & 0xFF, ftou(*(f32 *)(A + 0x3C)) & 0xFF,
                      ftou(fa), ftou(fb), ftou(vec1e0[0]), ftou(vec1e0[1]),
                      0, *(s32 *)(A + 0x40) << 12, 0, *(s32 *)(A + 0x48),
                      B[0x109], (s32)flag, (s32)(base + A[0x4C] * 16), 0,
                      *(f32 *)(A + 0x10), *(f32 *)(A + 0x14), *(f32 *)(A + 0x18),
                      c[0], c[1], c[2], c[3], ang);
    }
}
