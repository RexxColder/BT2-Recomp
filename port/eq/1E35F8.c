#include "common.h"

extern f32 D_00385688;

void func_001E65C8(f32 *out, u8 *src, s32 idx);
void func_00312680(f32 f12, f32 *out, f32 *in);
s32 func_001F23B8(s32 a0, s32 a1, s32 a2, s32 a3, s32 t0, s32 t1, s32 t2, s32 t3,
                  f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, f32 f17, f32 f18, f32 f19,
                  f32 st0, f32 st1, f32 st2, s32 st3, s32 st4, s32 st5, u8 *st6);

/* byte copy of a game structure (optnone: no memcpy intrinsic on game memory) */
__attribute__((noinline, optnone)) static void blob_copy(u8 *d, u8 *s, u32 n) {
    u32 i;
    for (i = 0; i < n; i++) {
        d[i] = s[i];
    }
}

/* float -> u32 conversion with the 2^31 split */
static u32 f2u(f32 v) {
    u32 r = (u32)(s32)v;
    if (v >= 2147483648.0f) {
        r = (u32)(s32)(v - 2147483648.0f) | 0x80000000;
    }
    return r;
}

/* Draws the four quads of a frame/ring effect (arg0 = 0x50-byte descriptor, arg2 = table base):
   builds 8 texture-coordinate pairs and 4 corner offsets from func_001E65C8's size ratios, then
   emits one func_001F23B8 sprite per corner. arg1 (0x130 bytes) is copied by the original and
   never read. fa / fb are the scale factors passed through. */
void func_001E35F8(u8 *arg0, u8 *arg1, u8 *arg2, u8 arg3, f32 fa, f32 fb) {
    u8 desc[0x50];
    f32 size[4];
    f32 corner[4];
    f32 uv[16];
    f32 pos[8];
    f32 ratioA, ratioB, ratioC, ratioD;
    f32 x, y;
    s32 i;
    u8 *d = desc;

    blob_copy(desc, arg0, 0x50);
    func_001E65C8(size, arg2, desc[0x4C]);
    ratioC = (size[0] - 1.0f) / size[0];
    ratioD = 1.0f / size[1];
    func_00312680(fa, corner, (f32 *)(d + 0x20));
    func_00312680(0.5f, corner, corner);

    ratioA = ratioC;
    ratioB = ratioD;
    pos[0] = ratioA; pos[1] = ratioB;
    pos[2] = ratioB; pos[3] = ratioA;
    pos[4] = ratioB; pos[5] = ratioB;
    pos[6] = ratioA; pos[7] = ratioA;
    uv[0] = ratioA; uv[1] = ratioB;
    uv[2] = ratioB; uv[3] = ratioA;
    uv[4] = ratioB; uv[5] = ratioB;
    uv[6] = ratioA; uv[7] = ratioA;
    uv[8] = ratioA; uv[9] = ratioA;
    uv[10] = ratioB; uv[11] = ratioB;
    uv[12] = ratioB; uv[13] = ratioA;
    uv[14] = ratioA; uv[15] = ratioB;

    x = corner[0];
    y = corner[1];
    pos[0] = x;  pos[1] = -y;
    pos[2] = -x; pos[3] = -y;
    pos[4] = x;  pos[5] = y;
    pos[6] = -x; pos[7] = y;

    for (i = 0; i < 4; i++) {
        func_001F23B8(f2u(*(f32 *)(d + 0x30)) & 0xFF,
                      f2u(*(f32 *)(d + 0x34)) & 0xFF,
                      f2u(*(f32 *)(d + 0x38)) & 0xFF,
                      f2u(*(f32 *)(d + 0x3C)) & 0xFF,
                      f2u(corner[0]), f2u(corner[1]), 0,
                      *(s32 *)(d + 0x40) << 12,
                      *(f32 *)(d + 0x10), *(f32 *)(d + 0x14), *(f32 *)(d + 0x18),
                      pos[2 * i], pos[2 * i + 1], fb, uv[4 * i], uv[4 * i + 1],
                      uv[4 * i + 2], uv[4 * i + 3],
                      (((f32)i * 90.0f + *(f32 *)(d + 0x44)) * D_00385688) / 180.0f,
                      0, *(s32 *)(d + 0x48), arg3,
                      arg2 + (d[0x4C] << 4));
    }
}
