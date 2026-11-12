#include "common.h"

extern s32 D_00377950[9];
extern f32 D_003872BC;
extern f32 D_003872C0;

s32 func_002A3C68(void);
void func_002A4CF0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8,
                   s32 arg9, s32 arg10, s32 arg11, s32 arg12, s32 arg13, s32 arg14, s32 arg15, s32 arg16);

/* Draws a pulsing menu cursor / frame at point `idx` (x, y, z triples copied from D_00377950) in mode 0/1 (one
 * 512 wide sprite) or 2 (three 64 wide pieces), growing for the first 37 frames of `t` then pulsing. */
void func_002A4420(s32 idx, s32 mode, s32 t) {
    s32 tbl[12];
    s32 *p;
    s32 w;
    s32 h;
    s32 alpha;
    s32 x;
    s32 y;
    s32 z;
    s32 left;
    s32 mid;
    f32 frac;
    f32 amp;
    f32 d;
    s32 period;
    s32 q;
    s32 r;
    s32 k;
    s32 slot;

    for (k = 0; k < 9; k++) {
        tbl[k] = D_00377950[k];
    }
    p = &tbl[idx * 3 + 3];
    if (t < 0) {
        w = 0;
        h = 0;
        alpha = 0;
    } else if (t < 37) {
        frac = (f32)t / 37.0f;
        if (mode == 2) {
            h = 128;
            w = (s32)(frac * 384.0f);
            alpha = 128;
        } else {
            h = (s32)(frac * 128.0f);
            w = (s32)(frac * 256.0f);
            alpha = h;
        }
    } else {
        t -= 37;
        amp = D_003872BC;
        period = 150;
        if (mode != 0) {
            if (mode == 1) {
                amp = D_003872C0;
                period = 37;
            } else {
                period = 1;
                amp = 0.0f;
            }
        }
        q = t / period;
        r = t % period;
        if ((q & 1) == 0) {
            k = r;
        } else {
            k = period - r;
        }
        alpha = 128;
        d = ((f32)k / (f32)period) * amp + 1.0f;
        w = (s32)(d * 256.0f);
        h = (s32)(d * 128.0f);
        if (mode == 2) {
            w = 0x180;
        }
    }
    x = p[0];
    y = p[1];
    z = p[2];
    if (mode != 2) {
        slot = func_002A3C68();
        func_002A4CF0(27, 6, slot, mode + 2, x - w, y - h, x + w, y + h, 128, 128, 128, alpha, 0, 0, 512, 256, z);
        return;
    }
    left = x - 0xC0;
    mid = left + w;
    slot = func_002A3C68();
    func_002A4CF0(27, 6, slot, 4, x - 0x100, y - h, left, y + h, 128, 128, 128, alpha, 0, 0, 64, 256, z);
    slot = func_002A3C68();
    func_002A4CF0(28, 6, slot, 4, left, y - h, mid, y + h, 128, 128, 128, alpha, 64, 0, 0x41, 256, z);
    slot = func_002A3C68();
    func_002A4CF0(29, 6, slot, 4, mid, y - h, mid + 64, y + h, 128, 128, 128, alpha, 64, 0, 128, 256, z);
}
