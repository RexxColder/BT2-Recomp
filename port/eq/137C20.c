#include "common.h"

void func_00129A50(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_00126588(void);
s32 func_00126698(void);
void func_0013A070(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7,
                   s32 a8, s32 a9, s32 a10, s32 a11, s32 a12);

void EftSurf_DrawReflectTri(s32 arg0, s32 arg1, s32 arg2) {
    u8 fr[0x90];
    s32 hi;
    s32 lo;
    s32 a;
    s32 b;
    s32 c;
    s32 x;
    s32 y;

    func_00129A50((s32)&fr[0x30], (s32)&fr[0x60], arg0, 3);
    hi = 0x910;
    lo = 0x6F0;
    if (func_00126698() == 0) {
        if (func_00126588() != 0) {
            lo = 0x7F0;
        } else {
            hi = 0x810;
        }
    }
    a = 1;
    if (*(s32 *)(fr + 0x38) > 0) {
        x = *(s32 *)(fr + 0x30);
        if ((x < (hi * 0x10)) && ((lo * 0x10) < x)) {
            y = *(s32 *)(fr + 0x34);
            a = ((y < 0x8F00) ? (y < 0x7101) : 1);
        }
    }
    if (a != 0) {
        hi = 0x910;
        lo = 0x6F0;
        if (func_00126698() == 0) {
            if (func_00126588() != 0) {
                lo = 0x7F0;
            } else {
                hi = 0x810;
            }
        }
        b = 1;
        if (*(s32 *)(fr + 0x48) > 0) {
            x = *(s32 *)(fr + 0x40);
            if ((x < (hi * 0x10)) && ((lo * 0x10) < x)) {
                y = *(s32 *)(fr + 0x44);
                b = ((y < 0x8F00) ? (y < 0x7101) : 1);
            }
        }
        if (b != 0) {
            hi = 0x910;
            lo = 0x6F0;
            if (func_00126698() == 0) {
                if (func_00126588() != 0) {
                    lo = 0x7F0;
                } else {
                    hi = 0x810;
                }
            }
            c = 1;
            if (*(s32 *)(fr + 0x58) > 0) {
                x = *(s32 *)(fr + 0x50);
                if ((x < (hi * 0x10)) && ((lo * 0x10) < x)) {
                    y = *(s32 *)(fr + 0x54);
                    c = ((y < 0x8F00) ? (y < 0x7101) : 1);
                }
            }
            if (c != 0) {
                return;
            }
        }
    }
    func_0013A070((s32)&fr[0x30], (s32)&fr[0x40], (s32)&fr[0x50], arg0 + 0x20,
                  arg0 + 0x50, arg0 + 0x80, (s32)&fr[0x60], (s32)&fr[0x70],
                  (s32)&fr[0x80], 0, arg1, arg2, 2);
}
