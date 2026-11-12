#include "common.h"

/* cvt.w.s truncates toward zero (saturating): plain cast */
#define CVT_W_S(out, x) do { \
    (out) = (s32)(x); \
} while (0)

s32 func_002768D8(s32 arg0, s64 arg1, s32 arg2, s32 arg3);
s32 func_001437A8(s32 arg0);
s32 func_002769F0(void);
s32 rand();
extern f32 D_00384218;
extern f32 D_0038421C;

void EftGeyser_StartSmoke(s32 arg0) {
    u8 buf[0xA0];
    s32 s0;
    s32 p;
    s32 ret;
    s32 r;
    s32 k;
    s32 rnd;
    f32 f20;
    f32 f0;
    f32 f1;

    s0 = *(s32 *)(arg0 + 0x38);
    *(f32 *)(buf + 0x50) = *(f32 *)(s0 + 0x70);
    *(f32 *)(buf + 0x54) = *(f32 *)(s0 + 0x74);
    *(f32 *)(buf + 0x58) = *(f32 *)(s0 + 0x78);
    *(f32 *)(buf + 0x5C) = 1.0f;
    *(f32 *)(buf + 0x60) = 32.0f;
    *(f32 *)(buf + 0x64) = 32.0f;
    *(f32 *)(buf + 0x68) = 32.0f;
    *(f32 *)(buf + 0x6C) = 0.0f;
    *(f32 *)(buf + 0x70) = 192.0f;
    *(f32 *)(buf + 0x74) = 192.0f;
    *(f32 *)(buf + 0x78) = 192.0f;
    *(f32 *)(buf + 0x7C) = 0.0f;
    *(f32 *)(buf + 0x80) = 2.0f;
    *(f32 *)(buf + 0x84) = 64.0f;
    *(f32 *)(buf + 0x88) = 1.0f;
    *(f32 *)(buf + 0x8C) = D_00384218;
    *(s32 *)(buf + 0x90) = 0x5A;
    *(s32 *)(buf + 0x94) = 0x1E;
    *(s32 *)(buf + 0x98) = 3;

    /* the 0x50 bytes at buf+0x50 are copied to buf+0x00 in dwords (ld/sd) */
    for (k = 0; k < 10; k++) {
        *(s64 *)(buf + k * 8) = *(s64 *)(buf + 0x50 + k * 8);
    }

    ret = func_002768D8(0xB, *(s64 *)(buf + 0x88), (s32)(buf + 0x90), (s32)(buf + 0x40));
    if (ret != 0) {
        p = func_002769F0();
        *(f32 *)(buf + 0x10) = (f32)*(u8 *)(p + 0x1C);
        *(f32 *)(buf + 0x14) = (f32)*(u8 *)(p + 0x1D);
        *(f32 *)(buf + 0x18) = (f32)*(u8 *)(p + 0x1E);
        *(f32 *)(buf + 0x1C) = (f32)*(u8 *)(p + 0x1F);
        *(f32 *)(buf + 0x20) = (f32)*(u8 *)(p + 0x20);
        *(f32 *)(buf + 0x24) = (f32)*(u8 *)(p + 0x21);
        *(f32 *)(buf + 0x28) = (f32)*(u8 *)(p + 0x22);
        *(f32 *)(buf + 0x2C) = (f32)*(u8 *)(p + 0x23);

        r = rand();
        f20 = ((f32)r / D_0038421C) * 5.0f - 2.5f;
        r = rand();
        *(s32 *)(buf + 0x48) = (r - (((r + (s32)((u32)r >> 31)) >> 1) << 1)) + 2;

        f1 = *(f32 *)(s0 + 0xB4) / 150.0f;
        f1 = f1 + f20;
        *(f32 *)(buf + 0x38) = f1;
        f0 = *(f32 *)(s0 + 0xB0) / 10.0f;
        f0 = f0 + f0;
        *(f32 *)(buf + 0x30) = f0;
        f1 = *(f32 *)(s0 + 0xB4) / 150.0f;
        f1 = f1 + 90.0f;
        CVT_W_S(rnd, f1);
        *(s32 *)(buf + 0x40) = rnd;

        if (*(s32 *)(s0 + 0xEC) == 0) {
            *(s32 *)(s0 + 0xEC) = func_001437A8((s32)buf);
        }
    }
}
