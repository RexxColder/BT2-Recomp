#include "common.h"

s32 func_002B2F48(s32 arg0);
s32 func_002B4B08(s32 arg0, s32 arg1);
extern s32 D_00345338 __attribute__((section(".data")));
extern s32 D_0034533C __attribute__((section(".data")));
extern u8 D_0038BAF8[] __attribute__((section(".data")));

s32 func_002B3370(s32 arg0, void *arg1, s32 *arg2) {
    s32 s0;
    s32 s1;
    s32 s2;
    s32 s3;
    s32 s4;
    s32 w;
    s32 h;
    s32 v;
    s32 off;
    s32 a0v;
    s32 *p;

    s4 = 0;
    s1 = *(s32 *)((u8 *)arg1 + 0x8);
    s0 = *(s32 *)((u8 *)arg1 + 0xC);
    s3 = *(s32 *)((u8 *)arg1 + 0x10);
    w = ((s1 < 0) ? (s1 + 0xF) : s1) >> 4;
    h = ((s0 < 0) ? (s0 + 0xF) : s0) >> 4;
    if (func_002B2F48(*(s32 *)((u8 *)arg1 + 0x24)) == 2) {
        v = (w * h) << 10;
    } else {
        v = w * h * 0x180;
    }
    s2 = v + 0x40;
    if (D_00345338 != 0) {
        if (D_00345338 < (s3 + 2)) {
            s4 = -1;
        } else {
            s0 = 0;
            if (D_0034533C < s2) {
                s4 = -1;
            } else {
                while (s0 < s3) {
                    off = s0 * 4;
                    s0 += 1;
                    a0v = *(s32 *)((u8 *)D_0038BAF8 + off);
                    *(s32 *)((u8 *)arg2 + off) = a0v;
                    if (a0v == 0) {
                        s4 = -1;
                    }
                }
            }
        }
        return s4;
    }
    if (s3 > 0) {
        s0 = s3;
        p = arg2;
        do {
            v = func_002B4B08(arg0, s2);
            s0 -= 1;
            *p = v;
            p += 1;
            if (v == 0) {
                s4 = -1;
            }
        } while (s0 != 0);
    }
    return s4;
}
