#include "common.h"
#include "vu0_state.h"

/* 0x00128F78: vf16 = vf15, vf17 = vf14, vf18 = vf13 (vmove). */
void func_00128F78(void) {
    memcpy(gVu0.vf[16], gVu0.vf[15], 16);
    memcpy(gVu0.vf[17], gVu0.vf[14], 16);
    memcpy(gVu0.vf[18], gVu0.vf[13], 16);
}
