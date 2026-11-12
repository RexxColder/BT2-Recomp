#include "common.h"

#define W32(p, off) (*(s32 *)((u8 *)(p) + (off)))

extern u8 *D_003876A0;
extern u8 *gEftShotFx;
extern f32 D_00384FE8;
extern f32 D_00384FEC;
extern f32 D_00384FF0;

void func_001B6670(s32 arg0, f32 farg0);
void func_001B6AF0(s32 arg0, f32 farg0);
void func_001B7070(s32 arg0, f32 farg0);

void func_001B5EC8(void) {
    s64 flag;
    s32 s1;
    u8 *s0;
    s32 a4;
    s32 a1;

    flag = *(s64 *)(D_003876A0 + 0x4D8);
    if (flag & 0x100) {
        return;
    }

    for (s1 = 0; s1 < 5; s1++) {
        s0 = *(u8 **)gEftShotFx + s1 * 16;
        a4 = W32(s0, 0xC);
        if (a4 == 0 || (a4 & 4)) {
            continue;
        }

        if (a4 & 0x60) {
            func_001B6670(W32(s0, 0x0), D_00384FE8);
            a4 = W32(s0, 0xC);
        }
        if (a4 & 1) {
            a1 = W32(s0, 0x4);
            if (a1 == 1) {
                a4 = a4 | 8;
                W32(s0, 0xC) = a4;
            }
            if (a1 == 4) {
                if (a4 & 2) {
                    a4 = a4 & ~1;
                } else {
                    a4 = 0;
                }
                W32(s0, 0xC) = a4;
            }
            if (a4 & 8) {
                func_001B6AF0(W32(s0, 0x0), D_00384FEC);
                a4 = W32(s0, 0xC) & ~0x28;
                W32(s0, 0xC) = a4;
            }
            W32(s0, 0x4) = W32(s0, 0x4) + 1;
        }

        if (a4 & 2) {
            a1 = W32(s0, 0x8);
            if (a1 == 1) {
                a4 = a4 | 0x40;
                W32(s0, 0xC) = a4;
            }
            if (a1 == 4) {
                if (a4 & 1) {
                    a4 = (a4 & ~2) & ~0x40;
                } else {
                    a4 = 0;
                }
                W32(s0, 0xC) = a4;
            }
            if (a4 & 0x10) {
                func_001B7070(W32(s0, 0x0), D_00384FF0);
                W32(s0, 0xC) = W32(s0, 0xC) & ~0x50;
            }
            W32(s0, 0x8) = W32(s0, 0x8) + 1;
        }
    }
}
