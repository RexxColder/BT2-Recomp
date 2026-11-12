#include "common.h"

void EftBurst_SetTexture(s32 arg0, s32 arg1, s32 arg2);
void func_00134BA0(s32 arg0, s32 arg1);
extern s32 gEftBurst;
extern u8 gEftBurstRes[] __attribute__((section(".data")));

void func_00135DA0(void) {
    s32 var_s1;
    s32 var_s0;

    if (*(s32 *) ((s32) gEftBurstRes + 0x14) == 0) {
        var_s1 = 0x15D;
        func_00134BA0(*(s32 *) ((s32) gEftBurstRes + 0xC), 0);
        EftBurst_SetTexture(0, 0, 0);
        var_s0 = gEftBurst + 0x240;
        do {
            if (*(s32 *) (var_s0 + 0x64) != 0) {
                ((void (*)(s32)) *(s32 *) (var_s0 + 0x58))(var_s0);
            }
            var_s1 -= 1;
            var_s0 += 0x70;
        } while (var_s1 >= 0);
    }
}
