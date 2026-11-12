#include "common.h"

void func_002EA050(u8 *arg0);
s32 func_002F1328(s32 arg0);
s32 func_002F15B8(s32 arg0);
s32 func_002F1600(s32 arg0, s32 arg1);
extern u8 D_0037CCB8[] __attribute__((section(".data")));

void func_002F5FC0(u8 *arg0, s32 arg1) {
    u8 *a0;
    u8 *vt;
    s32 s0;
    s32 s2;
    s32 tv0;
    s32 tv0_2;
    s32 tv_a1;
    s32 v3;
    s32 tv1;
    s32 tv1_2;

    if (arg0 == NULL) {
        func_002EA050(D_0037CCB8);
        return;
    }

    a0 = *(u8 **)(arg0 + 0x14);
    s0 = 0;
    if (a0 != NULL) {
        vt = *(u8 **)a0;
        s0 = ((s32 (*)(u8 *, s32))(*(void **)(vt + 0x24)))(a0, 1);
    }

    if (*(s8 *)(arg0 + 0x2) != 4 && *(s8 *)(arg0 + 0x6C) == 1 && arg1 == 0) {
        s2 = func_002F1328(*(s32 *)(arg0 + 0x4)) + s0;
        tv0 = func_002F15B8(*(s32 *)(arg0 + 0x4));
        tv0_2 = tv0 + 0x7FF;
        tv_a1 = tv0 + 0xFFE;
        s0 = (((tv0_2 < 0) ? tv_a1 : tv0_2) >> 11) << 11;
        v3 = func_002F1600(*(s32 *)(arg0 + 0x4), tv_a1);
        tv1 = v3 + 0x7FF;
        tv1_2 = (((tv1 < 0) ? (v3 + 0xFFE) : tv1) >> 11) << 11;
        tv1_2 = tv1_2 - s0;
        if (tv1_2 <= 0) {
            *(s32 *)(arg0 + 0xC4) = 0;
        } else {
            *(s32 *)(arg0 + 0xC4) = (((s2 - s0) / tv1_2) * tv1_2) + s0;
        }
    }
    *(u8 *)(arg0 + 0x6C) = (u8)arg1;
}
