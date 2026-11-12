#include "common.h"

void *func_00107848(void *a0);
s32 Font_GetGlyphHeight(void);
s32 func_00109818(void *a0, s32 a1, s32 a2);
s32 func_0028C648(void *a0);
void func_00297FE0(s32 a0, s32 a1, s32 a2, s32 a3, s32 t0);
extern u8 D_003B0C44[] __attribute__((section(".data")));

s32 func_00106318(void **arg0) {
    u8 *obj;
    u8 *s4;
    u8 *ptr;
    s32 s1;
    s32 s2;
    s32 s3;
    s32 s5;
    s32 flags;
    s32 idx;

    s4 = func_00107848(arg0);
    s3 = Font_GetGlyphHeight() * 0x12;
    obj = *arg0;
    if (*(s32 *)(obj + 0x1C) != 4) {
        return 0;
    }
    s1 = 0;
    s5 = func_00109818(obj, 4, 4);
    idx = *(s32 *)(s4 + 8);
    ptr = s4 + 4 * idx;
    flags = *(s32 *)(D_003B0C44 + 0x180 * idx);
    s2 = *(s32 *)(ptr + 0x10);
    if (func_0028C648(ptr) != 0) {
        flags = 0;
    }
    s1 = (flags & 0x10) ? -0x20 : 0;
    if (flags & 0x40) {
        s1 += 0x20;
    }
    if (flags & 0x20) {
        s1 += s3;
    }
    if (flags & 0x80) {
        s1 -= s3;
    }
    if (flags & 0x800) {
        s1 += s3;
    }
    if (flags & 0x400) {
        s1 -= s3;
    }
    if (flags & 0x200) {
        s1 += 0x2710;
    }
    if (flags & 0x100) {
        s1 -= 0x2710;
    }
    if (s1 != 0) {
        if (s1 < 0) {
            if (s2 != 0) {
                func_00297FE0(0, 0, 0x40, 0x40, 1);
            }
        } else if (s2 != s5) {
            func_00297FE0(0, 0, 0x40, 0x40, 1);
        }
        s2 += s1;
    }
    if (s2 < 0) {
        s2 = 0;
    }
    if (s5 < s2) {
        s2 = s5;
    }
    *(s32 *)(s4 + 4 * idx + 0x10) = s2;
    return 0;
}
