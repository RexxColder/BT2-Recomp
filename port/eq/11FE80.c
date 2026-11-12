#include "common.h"

extern u8 *D_003876A0;

void func_0011FD48(u8 *arg0);
void func_00124098(u8 *arg0);
void func_0011FAE0(u8 *arg0, s32 arg1, s32 arg2);
s32 func_00120CC8(u8 *arg0);
void func_00120E98(u8 *arg0, s32 arg1);

void func_0011FE80(u8 *arg0) {
    s32 temp_v0;

    if (*(s32 *)(arg0 + 0x11D0) != 0) {
        if (*(s32 *)(D_003876A0 + 0xB8) == 5) {
            if (*(u8 *)(D_003876A0 + (*(s32 *)arg0 * 0x1D0) + 0x2A5) == 0) {
                *(u8 *)(arg0 + 0x11EC) = 0;
                goto block_11;
            }
            if (*(u8 *)(arg0 + 0x11EC) == 0) {
                func_0011FD48(arg0);
                func_00124098(arg0);
            }
            *(u8 *)(arg0 + 0x11EC) = 1;
            if ((*(u8 *)(arg0 + 0x158) == 0) && (*(s32 *)(arg0 + 0x11B0) == 0x52)) {
                func_0011FAE0(arg0, 0x77, 0);
                func_0011FAE0(arg0, 0x77, 0);
                func_0011FAE0(arg0, 0xB0, 0);
            }
        } else {
block_11:
            temp_v0 = func_00120CC8(arg0);
            if (temp_v0 >= 0) {
                func_00120E98(arg0, temp_v0);
            }
        }
    }
}
