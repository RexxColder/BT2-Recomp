#include "common.h"

s32 func_002FCC58(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_002FCDF0(s32 arg0);
extern u8 D_00355E00[] __attribute__((section(".data")));
extern u8 D_00355F00[] __attribute__((section(".data")));

void *func_002FC998(u32 arg0, void *arg1, u32 arg2) {
    u8 *s0;
    s32 (*temp_v0_2)(s32, void *, u32);
    u32 temp_v0;
    s32 temp_v1;

    s0 = (u8 *)arg1;
    if (arg0 == 2) {
        *(s32 *)s0 = func_002FCC58(*(s32 *)(s0 + 0), *(s32 *)(s0 + 4), *(s32 *)(s0 + 8), *(s32 *)(s0 + 0xC));
    } else if (arg0 >= 2U) {
        temp_v0 = arg0 - 0x400;
        if (arg0 == 3) {
            func_002FCDF0(*(s32 *)s0);
        } else {
            temp_v1 = temp_v0 * 4;
            if (temp_v0 < 0x40U) {
                temp_v0_2 = *(s32 (**)(s32, void *, u32))(D_00355E00 + temp_v1);
                if (temp_v0_2 != NULL) {
                    temp_v0_2(*(s32 *)(D_00355F00 + temp_v1), arg1, arg2 >> 2);
                }
            }
        }
    }
    return arg1;
}
