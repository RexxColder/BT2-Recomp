#include "common.h"

extern f32 D_0038568C;
extern f32 D_00385690;
extern f32 D_00385694;

extern void func_00312490(f32 *dst, f32 *a, f32 *b);
extern void func_00312638(f32 *dst, f32 *a, f32 *b);
extern void func_00312650(f32 *dst, f32 *a, f32 *b);
extern s32 func_00312680(f32 *dst, f32 *src, f32 s);
extern void sceVu0Normalize(f32 *dst, f32 *src);
extern void sceVu0ApplyMatrix(f32 *dst, f32 *m, f32 *v);
extern void sceVu0TransMatrix(f32 *dst, f32 *m, f32 *t);
extern void sceVu0RotTransPersN(s32 *dst, f32 *m, f32 *v, s32 n, s32 flag);
extern void Vu0Cur_StoreMtx(f32 *m);
extern void Vu0Screen_StoreMtx(f32 *m);
extern void EftShotFx_UpdateLines(void);
void func_001E4020(u8 *arg0, f32 farg0);
s32 func_001E6400(u8 *arg0, u8 *arg1, u8 *arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7,
                  s32 arg8, u64 arg9 /* TEX0 (64-bit; was u8 *: truncated to 32 bits) */, s32 arg10, u8 arg11);

/* byte copy of game memory (optnone so clang does not turn it into a memcpy on 4-byte game pointers) */
__attribute__((noinline, optnone)) static void blob_copy(u8 *d, u8 *s, u32 n) {
    u32 i;
    for (i = 0; i < n; i++) {
        d[i] = s[i];
    }
}

/* f32 -> u32 as the original does it (cvt.w.s truncates; >= 2^31 handled by subtracting 2^31) */
static u32 f2u(f32 f) {
    if (f >= 2147483648.0f) {
        return (u32)(s32)(f - 2147483648.0f) | 0x80000000u;
    }
    return (u32)(s32)f;
}

/* Builds a billboard quad around a point (axes from the cross products with (0,-1,0,1)), scales it by the
   effect struct, projects it, and hands the 4 corners to func_001E6400. */
s32 func_001E3AC8(f32 farg0, u8 *effA, u8 *effB, f32 *center, f32 *size, f32 *axisIn, s32 arg5, s32 arg6,
                  s32 flag, s32 table) {
    u8 A[0x50] __attribute__((aligned(16)));
    u8 B[0x130] __attribute__((aligned(16)));
    f32 up[4] __attribute__((aligned(16)));    /* 0x1A0 */
    f32 right[4] __attribute__((aligned(16))); /* 0x1B0 */
    f32 ax[4] __attribute__((aligned(16)));    /* 0x1C0 */
    f32 quad[16] __attribute__((aligned(16))); /* 0x1D0 */
    s32 proj[16];                              /* 0x210 */
    f32 inv[4];                                /* 0x250 */
    f32 offX[4] __attribute__((aligned(16)));  /* 0x260 */
    f32 offY[4] __attribute__((aligned(16)));  /* 0x270 */
    f32 p0[4] __attribute__((aligned(16)));    /* 0x280 */
    f32 p1[4] __attribute__((aligned(16)));    /* 0x290 */
    f32 mtx[16] __attribute__((aligned(16)));  /* 0x2A0 */
    f32 scr[16] __attribute__((aligned(16)));  /* 0x2E0 */
    f32 tmp[4] __attribute__((aligned(16)));   /* 0x320 */
    s32 i, key, idx;
    u32 cnt;
    u64 slot;
    u32 r, g, b, a;
    f32 fcnt;

    blob_copy(A, effA, 0x50);
    blob_copy(B, effB, 0x130);
    ax[0] = axisIn[0];
    ax[1] = axisIn[1];
    ax[2] = axisIn[2];
    ax[3] = axisIn[3];
    up[0] = 0.0f;
    up[1] = -1.0f;
    up[2] = 0.0f;
    up[3] = 1.0f;
    func_00312490(right, ax, up);
    func_00312490(up, right, ax);
    sceVu0Normalize(right, right);
    sceVu0Normalize(up, up);
    cnt = *(u32 *)(A + 0x40);
    fcnt = (f32)cnt;
    func_00312680(offX, right, ((size[0] * fcnt) * D_0038568C) * 0.5f);
    func_00312680(offY, up, ((size[1] * fcnt) * D_00385690) * 0.5f);
    func_00312638(p0, center, offX);
    func_00312650(p1, center, offX);
    func_00312638(&quad[0], p0, offY);
    func_00312638(&quad[4], p1, offY);
    func_00312650(&quad[8], p0, offY);
    func_00312650(&quad[12], p1, offY);
    for (i = 0; i < 4; i++) {
        func_001E4020((u8 *)&quad[i * 4], *(f32 *)(A + 0x44) * D_00385694);
    }
    EftShotFx_UpdateLines();
    Vu0Cur_StoreMtx(mtx);
    sceVu0TransMatrix(mtx, mtx, (f32 *)(A + 0x10));
    for (i = 0; i < 4; i++) {
        sceVu0ApplyMatrix(&quad[i * 4], mtx, &quad[i * 4]);
    }
    Vu0Screen_StoreMtx(scr);
    sceVu0RotTransPersN(proj, scr, quad, 4, 1);
    if (flag != 0) {
        for (i = 3; i >= 0; i--) {
            proj[i * 4 + 2] = 0xFFFFFF;
        }
    }
    for (i = 0; i < 4; i++) {
        sceVu0ApplyMatrix(tmp, scr, &quad[i * 4]);
        inv[i] = 1.0f / tmp[3];
    }
    if (B[0x10A] != 0) {
        idx = B[0x108] + B[0x109];
    } else {
        idx = A[0x4C];
    }
    slot = *(u64 *)(u32)(table + idx * 16);
    quad[3] = 1.0f;
    quad[7] = 1.0f;
    quad[11] = 1.0f;
    quad[15] = 1.0f;
    key = (proj[2] + proj[14] + (proj[10] + proj[6])) >> 10;
    r = f2u(*(f32 *)(A + 0x30)) & 0xFF;
    g = f2u(*(f32 *)(A + 0x34)) & 0xFF;
    b = f2u(*(f32 *)(A + 0x38)) & 0xFF;
    a = f2u(*(f32 *)(A + 0x3C)) & 0xFF;
    return func_001E6400((u8 *)quad, (u8 *)(u32)arg5, (u8 *)(u32)arg6, r, g, b, a, *(s32 *)(A + 0x48), -1,
                         slot, key, (u8)flag);
}
