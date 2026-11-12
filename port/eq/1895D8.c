#include "common.h"

s32 func_00126598(s32 arg0);
void func_0018AE98(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7,
                   s32 arg8, s32 arg9,
                   f32 farg0, f32 farg1, f32 farg2, f32 farg3, f32 farg4, f32 farg5, f32 farg6, f32 farg7,
                   f32 farg8, s32 arg10, s32 arg11, s32 arg12, u64 arg13);

/* 0x001895D8: draw every node of the object's list (self+0x1E0, linked through +0xC0) as a quad via 0x18AE98.
 * a2: add the object offset (self+0x40) to node positions; a3: if 0, positions are used unscaled/unoffset...
 * t0: use the swapped colour order for nodes with a negative value at +0xA8. f12/f13: size scale factors. */
void func_001895D8(u8 *self, s32 a1, u32 a2, u32 a3, u32 t0, f32 f12, f32 f13) {
    u8 mode = (u8)a2;
    u8 keep = (u8)a3;
    u8 swap = (u8)t0;
    f32 pos[4];   /* sp 0x40 */
    f32 size[2];  /* sp 0x50 */
    f32 col[4];   /* sp 0x60 */
    u8 *node;
    f32 scale;
    s32 viewOnly = 0;
    f32 *palette;
    f32 s0;
    f32 s1;
    u32 r;
    u32 g;
    u32 b;
    u32 a;

    __builtin_memset(pos, 0, 16);
    pos[3] = 1.0f;
    __builtin_memset(size, 0, 8);
    __builtin_memset(col, 0, 16);
    if ((*(u32 *)(self + 0x1D8) & 0x200) != 0) {
        if (func_00126598(*(s32 *)(self + 0xD0)) == 0) {
            return;
        }
        viewOnly = 1;
    }
    scale = *(f32 *)(self + 0x88) * *(f32 *)(self + 0x80);
    for (node = *(u8 **)(self + 0x1E0); node != NULL; node = *(u8 **)(node + 0xC0)) {
        if (mode != 0) {
            pos[0] = *(f32 *)node + *(f32 *)(self + 0x40);
            pos[1] = *(f32 *)(node + 4) + *(f32 *)(self + 0x44);
            pos[2] = *(f32 *)(node + 8) + *(f32 *)(self + 0x48);
            if (keep == 0) {
                pos[0] = *(f32 *)node;
                pos[1] = *(f32 *)(node + 4);
                pos[2] = *(f32 *)(node + 8);
            }
        } else {
            pos[0] = *(f32 *)node * scale + *(f32 *)(self + 0x40);
            pos[1] = *(f32 *)(node + 4) * scale + *(f32 *)(self + 0x44);
            pos[2] = *(f32 *)(node + 8) * scale + *(f32 *)(self + 0x48);
        }
        palette = (f32 *)(self + 4 + (node[0xBD] << 4));
        if (*(f32 *)(node + 0xA8) < 0.0f && swap != 0) {
            col[0] = palette[0xD8 / 4];
            col[1] = palette[0xDC / 4];
            col[2] = palette[0xD0 / 4];
            col[3] = palette[0xD4 / 4];
        } else {
            col[0] = palette[0xD0 / 4];
            col[1] = palette[0xD4 / 4];
            col[2] = palette[0xD8 / 4];
            col[3] = palette[0xDC / 4];
        }
        size[0] = *(f32 *)(node + 0x88) * scale * 10.0f;
        size[1] = *(f32 *)(node + 0x8C) * scale * 10.0f;
        r = (u32)*(f32 *)(node + 0x20);
        g = (u32)*(f32 *)(node + 0x24);
        b = (u32)*(f32 *)(node + 0x28);
        a = (u32)*(f32 *)(node + 0x2C);
        s0 = size[0];
        s1 = size[1];
        func_0018AE98((s32)(u8)r, (s32)(u8)g, (s32)(u8)b, (s32)(u8)a,
                      (s32)(f12 * s0), (s32)(f13 * s1), (s32)(u32)s0, (s32)(u32)s1,
                      0, 0x1000,
                      pos[0], pos[1], pos[2], col[0], col[1], col[2], col[3], *(f32 *)(node + 0xA4),
                      *(f32 *)(node + 0xAC), 0, a1, viewOnly, *(u64 *)(self + 0x28));
    }
}
