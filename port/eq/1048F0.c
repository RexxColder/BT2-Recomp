#include "common.h"

s32 func_002A86E8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
void func_00104790(s32 arg0);
extern u8 *D_00387F2C;

s32 func_001048F0(s32 arg0, s32 arg1) {
    s32 buf[8];
    s32 q;
    s32 a3;

    q = arg1 / 9;
    buf[0] = 0;
    buf[1] = arg1 + 0xACBB;
    buf[2] = 0xACC1 + q * 9;
    buf[3] = 0xACC2 + q * 9;
    if ((*(u32 *)(D_00387F2C + 0x1008) & 1) == 0) {
        a3 = 0xABA3 + q;
    } else {
        a3 = 0xAC2F + q;
    }
    buf[4] = a3;
    buf[5] = 0;
    buf[6] = arg0;
    return func_002A86E8((s32)buf, (s32)func_00104790, 0, a3, a3, arg0);
}
