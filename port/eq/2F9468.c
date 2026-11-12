#include "common.h"

void func_002F9300(s32 arg0);
s32 func_002F94F0(s32 arg0, s32 arg1);
extern u8 D_0037D0F8[] __attribute__((section(".data")));
extern u8 D_0037D120[] __attribute__((section(".data")));
extern u8 D_0037D148[] __attribute__((section(".data")));
extern u8 _sceCd_Poff_Intr[] __attribute__((section(".data")));

void func_002F9468(s32 arg0, s32 arg1) {
    s32 temp_v0;
    s32 temp_v0_2;

    if (arg0 == 0) {
        func_002F9300((s32) D_0037D0F8);
        return;
    }
    if (arg1 == 0) {
        func_002F9300((s32) D_0037D120);
        return;
    }
    temp_v0 = func_002F94F0(arg0, arg1);
    if (temp_v0 == 0) {
        func_002F9300((s32) D_0037D148);
        return;
    }
    temp_v0_2 = *(s32 *) (temp_v0 + 4);
    if (temp_v0_2 != 0) {
        ((void (*)(s32, s32)) temp_v0_2)((s32) _sceCd_Poff_Intr, 0);
    }
}
