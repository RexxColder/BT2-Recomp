#include "common.h"

void *func_0028BAA8(s32 arg0);
void *memset(void *arg0, s32 arg1, u32 arg2);
void func_00126DE0(void *arg0);
void func_00126E80(s32 arg0);
extern u8 *gEftBurst;
extern u8 gEftBurstRes[];

void func_00135C78(void) {
    s32 var_s0;
    s32 var_s1;
    u8 *temp_a0;

    var_s0 = 0x15D;
    var_s1 = 0;
    gEftBurst = (u8 *)func_0028BAA8(0x9B70);
    memset(gEftBurst, 0, 0x9B70);
    *(s32 *)(gEftBurstRes + 0x14) = 0;
    do {
        var_s0 -= 1;
        temp_a0 = gEftBurst + var_s1;
        var_s1 += 0x70;
        memset(temp_a0 + 0x240, 0, 0x70);
    } while (var_s0 >= 0);
    *(f32 *)(gEftBurst + 0x8) = 8.0f;
    *(f32 *)(gEftBurst + 0xC) = 20.0f;
    *(s32 *)(gEftBurst + 0x4) = 0;
    *(s32 *)(gEftBurst + 0x9B60) = 0x3C;
    *(s32 *)(gEftBurst + 0x18) = *(s32 *)(gEftBurstRes + 0x8);
    *(s32 *)(gEftBurst + 0x1C) = -1;
    *(s32 *)(gEftBurst + 0x20) = -1;
    func_00126DE0(gEftBurst + 0x18);
    func_00126E80(1);
}
