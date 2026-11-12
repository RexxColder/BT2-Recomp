#include "common.h"

void func_0027F030(u8 *arg0, u8 *arg1);
extern void *memset(void *dst, s32 c, u32 n);

/* 0x0027F7B0: buf[256] (f32) = memset 0, func_0027F030(arg1, buf); for i in 0..255: byte (4*v + 3) of arg0 = low byte of
 * round(buf[i] * 128 * arg2), bytes 4*v+0..2 = 0, v = (i & 0xE7) | ((i & 8) << 1) | ((i & 0x10) >> 1). */
void func_0027F7B0(u8 *arg0, u8 *arg1, f32 arg2) {
    f32 buf[256];
    s32 i;
    s32 v;
    s32 t;
    f32 f;
    f32 r;
    u8 *o;

    memset(buf, 0, 0x400);
    func_0027F030(arg1, (u8 *)buf);
    for (i = 0; i < 256; i++) {
        v = (i & 0xE7) | ((i & 8) << 1) | ((i & 0x10) >> 1);
        f = buf[i] * 128.0f * arg2;
        t = (s32)f;
        r = f - (f32)t;
        if (r > 0.5f || (r == 0.5f && (t & 1))) {
            t++;
        } else if (r < -0.5f || (r == -0.5f && (t & 1))) {
            t--;
        }
        o = arg0 + v * 4;
        o[0] = 0;
        o[1] = 0;
        o[2] = 0;
        o[3] = (u8)t;
    }
}
