#include "common.h"

#define W(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define F(p, o) (*(f32 *)((u8 *)(p) + (o)))
/* cvt.w.s with the unsigned-range fixup the compiler emits for (u32) casts */
#define F2I(f) ((f) >= 2147483648.0f ? (s32)((s32)((f) - 2147483648.0f) | (s32)0x80000000) : (s32)(f))

extern f32 D_00385680;
extern f32 D_00385684;

extern void func_001E65C8(f32 *out, u8 *base, s32 idx);
extern void func_00312680(f32 *dst, u8 *src, f32 s);
extern s32 func_001E4258(s32 a0, s32 a1, s32 a2, s32 a3, s32 t0, s32 t1, s32 t2, s32 t3,
                         f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, f32 f17, f32 f18, f32 f19,
                         s32 s0, s32 s1, s32 s2, s32 s3, s32 s4, s32 s5, s32 s6, s32 s7);
extern s32 func_001E4750(s32 a0, s32 a1, s32 a2, s32 a3, s32 t0, s32 t1, s32 t2, s32 t3,
                         f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, f32 f17, f32 f18, f32 f19,
                         s32 s0, s32 s1, s32 s2, s32 s3, s32 s4, s32 s5, s32 s6);

/* Draws the 4 corner quads of a framed 9-slice-like element: A (0x50 bytes) = colour/size block copied by
   value, B (0x130 bytes) = second block (B[0x109] = param, B[0x10A] = mode flag), a2 = base table,
   a3 = byte, f12 = scale. Mode 0 uses func_001E4258 (with a corner index), mode 1 uses func_001E4750. */
s32 func_001E2F60(u8 *srcA, u8 *srcB, u8 *base, s32 a3, f32 scale) {
    u8 A[0x50];
    u8 B[0x130];
    f32 vec[4];
    f32 P[4];
    f32 U[16];
    f32 V[16];
    s32 zero = 0;
    f32 X;
    f32 Y;
    s32 sel = a3 & 0xFF;
    s32 i;
    s32 r = 0;
    s32 t2;
    s32 t3;

    __builtin_memcpy(A, srcA, 0x50);
    __builtin_memcpy(B, srcB, 0x130);
    func_001E65C8(vec, base, A[0x4C]);
    Y = 1.0f / vec[1];
    X = (vec[0] - 1.0f) / vec[0];
    func_00312680(P, A + 0x20, scale * 0.5f);

    V[0] = X;  V[1] = Y;  V[2] = Y;  V[3] = X;
    V[4] = Y;  V[5] = Y;  V[6] = X;  V[7] = X;
    V[8] = X;  V[9] = X;  V[10] = Y; V[11] = Y;
    V[12] = Y; V[13] = X; V[14] = X; V[15] = Y;
    __builtin_memcpy(U, V, 0x40);

    V[8] = P[0];  V[9] = -P[1];
    V[10] = -P[0]; V[11] = -P[1];
    V[12] = P[0];  V[13] = P[1];
    V[14] = -P[0]; V[15] = P[1];
    __builtin_memcpy(V, V + 8, 0x20);

    t2 = F2I(P[0]);
    t3 = F2I(P[1]);

    if (B[0x10A] == 0) {
        for (i = 0; i < 4; i++) {
            r = func_001E4258((u8)F2I(F(A, 0x30)), (u8)F2I(F(A, 0x34)), (u8)F2I(F(A, 0x38)), (u8)F2I(F(A, 0x3C)),
                              (s32)V[i * 2], (s32)V[i * 2 + 1], t2, t3,
                              F(A, 0x10), F(A, 0x14), F(A, 0x18), U[i * 4], U[i * 4 + 1], U[i * 4 + 2], U[i * 4 + 3],
                              F(A, 0x44) * D_00385680 / 180.0f,
                              0, W(A, 0x40) << 12, 0, W(A, 0x48), sel, i, (s32)&zero,
                              (s32)(base + (A[0x4C] << 4)));
        }
    } else {
        for (i = 0; i < 4; i++) {
            r = func_001E4750((u8)F2I(F(A, 0x30)), (u8)F2I(F(A, 0x34)), (u8)F2I(F(A, 0x38)), (u8)F2I(F(A, 0x3C)),
                              (s32)V[i * 2], (s32)V[i * 2 + 1], t2, t3,
                              F(A, 0x10), F(A, 0x14), F(A, 0x18), U[i * 4], U[i * 4 + 1], U[i * 4 + 2], U[i * 4 + 3],
                              F(A, 0x44) * D_00385684 / 180.0f,
                              0, W(A, 0x40) << 12, 0, W(A, 0x48), B[0x109], sel,
                              (s32)(base + (A[0x4C] << 4)));
        }
    }
    return r;
}
