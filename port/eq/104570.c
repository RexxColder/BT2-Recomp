#include "common.h"

s32 func_002085C8(void *a0);
void *func_00211288(void *a0);
s32 func_00211310(void *a0, s32 a1, s32 a2);
void func_002113C0(void *a0, s32 a1, s32 a2, s32 a3);
void func_002A86E8(void *a0, void *a1, s32 a2, s32 a3, s32 t0, s32 t1);
void func_001038F0(void);

void func_00104570(s32 arg0) {
    u8 frame[0x20];
    s32 x;

    if (func_00211310(func_00211288((void *)arg0), 0xC, 0x1000) != 0) {
        x = func_002085C8((void *)arg0);
        *(s32 *)(frame + 0) = 0;
        if (x < 0x8C) {
            *(s32 *)(frame + 0xC) = x * 9 + 0xACBB;
        } else {
            *(s32 *)(frame + 0xC) = x * 2 + 0x3B16;
        }
        *(s32 *)(frame + 0x10) = -1;
        *(s32 *)(frame + 0x14) = -1;
        *(s32 *)(frame + 0x18) = arg0;
        func_002A86E8(frame, (void *)func_001038F0, 0, x < 0x8C, x * 2 + 0x3B16, -1);
        func_002113C0(func_00211288((void *)arg0), 0xC, 0x1000, 0);
    }
}
