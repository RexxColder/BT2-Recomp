#include "common.h"

extern s32 func_00126598(s32 arg0);
extern void func_00186B80(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7,
                          f32 farg0, f32 farg1, f32 farg2, f32 farg3, f32 farg4, f32 farg5, f32 farg6, f32 farg7,
                          s32 stk0, s32 stk1, f32 stk2, s32 stk3, s32 stk4, s32 stk5, s64 stk6);

/* Walks the particle list of obj (head at +0x1A4, next at +0xC0) and submits each one to func_00186B80.
 * addPos: add obj->+0x40 position to the particle position; noScale: do not multiply by obj->+0x80;
 * flip: swap the uv pairs of a particle whose +0xA8 is negative. */
void func_00185368(u8 *obj, s32 mode, s32 noScale, s32 addPos, s32 flip, f32 scaleX, f32 scaleY) {
    f32 pos[4];
    f32 size[2];
    f32 uv[4];
    u8 *p;
    u8 *tab;
    s32 isFlagged = 0;
    f32 scale;
    u32 c0, c1, c2, c3;
    u32 sx, sy;

    noScale &= 0xFF;
    addPos &= 0xFF;
    flip &= 0xFF;
    pos[0] = pos[1] = pos[2] = pos[3] = 0.0f;
    pos[3] = 1.0f;
    size[0] = size[1] = 0.0f;
    uv[0] = uv[1] = uv[2] = uv[3] = 0.0f;
    if (*(s32 *)(obj + 0x19C) & 0x200) {
        if (func_00126598(*(s32 *)(obj + 0x94)) == 0) {
            return;
        }
        isFlagged = 1;
    }
    tab = obj + 8;
    for (p = *(u8 **)(obj + 0x1A4); p != 0; p = *(u8 **)(p + 0xC0)) {
        scale = *(f32 *)(obj + 0x80);
        if (addPos != 0) {
            if (noScale != 0) {
                pos[0] = *(f32 *)(p + 0) + *(f32 *)(obj + 0x40);
                pos[1] = *(f32 *)(p + 4) + *(f32 *)(obj + 0x44);
                pos[2] = *(f32 *)(p + 8) + *(f32 *)(obj + 0x48);
            } else {
                pos[0] = *(f32 *)(p + 0) * scale + *(f32 *)(obj + 0x40);
                pos[1] = *(f32 *)(p + 4) * scale + *(f32 *)(obj + 0x44);
                pos[2] = *(f32 *)(p + 8) * scale + *(f32 *)(obj + 0x48);
            }
        } else if (noScale != 0) {
            pos[0] = *(f32 *)(p + 0);
            pos[1] = *(f32 *)(p + 4);
            pos[2] = *(f32 *)(p + 8);
        } else {
            pos[0] = *(f32 *)(p + 0) * scale;
            pos[1] = *(f32 *)(p + 4) * scale;
            pos[2] = *(f32 *)(p + 8) * scale;
        }
        if (*(f32 *)(p + 0xA8) < 0.0f && flip != 0) {
            u8 *e = tab + p[0xBD] * 16;
            uv[0] = *(f32 *)(e + 0x98);
            uv[1] = *(f32 *)(e + 0x9C);
            uv[2] = *(f32 *)(e + 0x90);
            uv[3] = *(f32 *)(e + 0x94);
        } else {
            u8 *e = tab + p[0xBD] * 16;
            uv[0] = *(f32 *)(e + 0x90);
            uv[1] = *(f32 *)(e + 0x94);
            uv[2] = *(f32 *)(e + 0x98);
            uv[3] = *(f32 *)(e + 0x9C);
        }
        size[0] = *(f32 *)(p + 0x88) * scale * 10.0f;
        size[1] = *(f32 *)(p + 0x8C) * scale * 10.0f;
        c0 = (u32)*(f32 *)(p + 0x20);
        c1 = (u32)*(f32 *)(p + 0x24);
        c2 = (u32)*(f32 *)(p + 0x28);
        c3 = (u32)*(f32 *)(p + 0x2C);
        sx = (u32)size[0];
        sy = (u32)size[1];
        func_00186B80(c0 & 0xFF, c1 & 0xFF, c2 & 0xFF, c3 & 0xFF,
                      (s32)(scaleX * size[0]), (s32)(scaleY * size[1]), sx, sy,
                      pos[0], pos[1], pos[2], uv[0], uv[1], uv[2], uv[3], *(f32 *)(p + 0xA4),
                      0, 0x1000, *(f32 *)(p + 0xAC), 0, mode, isFlagged, *(s64 *)(obj + 0x28));
    }
}
