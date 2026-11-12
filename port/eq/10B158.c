#include "common.h"

s32 func_001017F0(s32 arg0, s32 arg1, s32 arg2);
u8 *func_0010B078(s32 arg0);
void memset(void *arg0, s32 arg1, u32 arg2);
extern u8 *D_003876A0;
extern u8 *D_00387F2C;
extern u8 func_00117820[] __attribute__((section(".data")));

void DemoCam_AddShake(s32 arg0) {
    u8 *s0;
    s32 a0;

    s0 = func_0010B078(arg0);
    if (*(s32 *)(D_003876A0 + 0xB8) != 6 && *(s32 *)(s0 + 0x1354) == 0) {
        a0 = *(s32 *)(D_003876A0 + 0xC4) * 7;
        func_001017F0(!(*(s32 *)(D_00387F2C + 0x1008) & 1) ? (a0 + 0x37D9) : (a0 + 0x3BF2), 0, (s32)D_00387F2C);
        memset(s0 + 0x3C, 0, 0x3C);
        *(s32 *)(s0 + 0x1354) = (s32)func_00117820;
    }
}
