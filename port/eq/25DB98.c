#include "common.h"

extern u8 *D_003876A0;
extern u8 *D_00387F2C;

void func_0025DB98(u8 *arg0) {
    u8 *t0;
    u8 *t3;
    u8 *a2;
    s32 t1;
    s32 t2;

    t0 = arg0 + 0x780;
    t3 = arg0 + 0x1C;
    a2 = D_003876A0 + 0x70;
    t2 = 0x63;
    t1 = ((*(u32 *)(D_00387F2C + 0x1008) & 1) ? 0x64 : 0) * 4 + 0x14;
    do {
        u8 *a3 = *(u8 **)(a2 + 8);
        u8 *v1 = a3 + t1;
        u32 a0v;
        u32 a1v;

        t1 += 4;
        a0v = *(u32 *)v1;
        a1v = *(u32 *)(v1 + 4);
        if (a1v != a0v) {
            *(s32 *)t0 = (s32)(a3 + ((a0v >> 2) * 4));
        } else {
            *(s32 *)t0 = 0;
        }
        t2 -= 1;
        t0 += 4;
    } while (t2 >= 0);

    a2 = *(u8 **)(a2 + 8);
    {
        u32 v1_2 = *(u32 *)(a2 + 0xC);
        if (*(s32 *)(a2 + 0x10) != (s32)v1_2) {
            *(s32 *)(t3 + 0x730) = (s32)(a2 + ((v1_2 >> 2) * 4));
            return;
        }
    }
    *(s32 *)(t3 + 0x730) = 0;
}
