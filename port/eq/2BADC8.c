#include "common.h"

s32 func_002B8280(s32 arg0);
s32 Rand_Range(s32 arg0, s32 arg1);
void func_002B74F8(s32 arg0, s32 arg1);
void func_002FFF90(s32 arg0);
void func_002BAC08(s32 arg0, s32 arg1);
void func_002BACC8(s32 arg0);
void func_002BAD68(s32 arg0, s32 arg1);
extern u8 D_00379B88[] __attribute__((section(".data")));
extern u8 D_00379BB8[] __attribute__((section(".data")));

void func_002BADC8(s32 arg0, s32 arg1) {
    s32 temp_v0;

    temp_v0 = func_002B8280(arg0);
    if (temp_v0 != 1) {
        /* a1 is not set on this path: the callee's leftover is not reproduced (GUESS) */
        Rand_Range((s32)D_00379B88, 0);
        return;
    }
    if (arg1 == 0) {
        Rand_Range((s32)D_00379BB8, arg1);
        return;
    }
    func_002B74F8(arg0, arg1);
    func_002FFF90(*(s32 *)(arg0 + 0x48));
    func_002BAC08(arg0, *(s32 *)(arg0 + 0x1A4));
    func_002BAD68(arg0, 1);
    func_002BACC8(arg0);
    *(s32 *)(arg0 + 0x2E4) = temp_v0;
    *(s32 *)(arg0 + 0x2DC) = temp_v0;
    if (*(s32 *)(arg0 + 0x2E0) == 0) {
        *(s32 *)(arg0 + 0x2E8) = temp_v0;
    }
}
