#include "common.h"

s32 Rand_Range();
s32 func_002B8280(s32 arg0, s32 arg1);
void func_002BBE48(s32 arg0, s32 arg1);
s32 func_002C1120(s32 arg0);
extern u8 D_00379DB0[] __attribute__((section(".data")));
extern u8 D_00379DE0[] __attribute__((section(".data")));

void func_002BB418(s32 arg0, s32 arg1) {
    u8 *s0;
    s32 temp_v0;
    s8 temp_v0_2;

    s0 = (u8 *)arg0;
    temp_v0 = func_002B8280(arg0, arg1);
    if (temp_v0 != 1) {
        Rand_Range((s32)D_00379DB0);
        return;
    }
    temp_v0_2 = *(s8 *)(s0 + 0x70);
    if (temp_v0_2 == temp_v0) {
        if (arg1 == 0) {
            *(s8 *)(s0 + 0x71) = temp_v0_2;
        }
    }
    if ((*(s8 *)(s0 + 0x70) == 0) && (arg1 == 1) && (func_002C1120(*(s32 *)(s0 + 0x3C)) != 0)) {
        Rand_Range((s32)D_00379DE0);
    }
    func_002BBE48(arg0 + 0x284, arg1);
    func_002BBE48(arg0 + 0x2A4, arg1);
    *(s8 *)(s0 + 0x70) = (s8)arg1;
}
