#include "common.h"

s32 func_00325830(void *arg0, void *arg1, s32 arg2, s32);
s32 func_002E70B0(void *arg0, s32 arg1, void *arg2, void *arg3, void *arg4);
extern u8 D_0037BA80 __attribute__((section(".data")));
extern u16 D_00347BEC __attribute__((section(".data")));
extern u16 D_00347BEE __attribute__((section(".data")));
extern u16 D_00347BF0 __attribute__((section(".data")));

/* 0x002E7D68: outputs three halfwords (arg4, arg5, arg6). mode = arg1 & 0xFF < 4: all three 0. val = arg2 & 0xFF
 * >= 0x10: func_00325830(buf, &D_0037BA80, arg3) then func_002E70B0(buf, 8, arg4, arg5, arg6). val < 8: arg4 = 0,
 * arg5 = 0, arg6 = 0. Otherwise, when the words at arg0+0xA0 (word) and arg0+0xA4 (halfword) are both zero, the
 * halfwords at +0xA0/+0xA2/+0xA4 are loaded from D_00347BEC/EE/F0; then arg4/5/6 = halfwords at +0xA0/+0xA2/+0xA4.
 * Returns 0. */
s32 func_002E7D68(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, u16 *arg4, u16 *arg5, u16 *arg6) {
    u8 buf[0x10];
    u8 mode = (u8)arg1;
    u8 val = (u8)arg2;

    if (mode < 4) {
        *arg4 = 0;
        *arg5 = 0;
        *arg6 = 0;
        return 0;
    }
    if (val >= 0x10) {
        func_00325830(buf, &D_0037BA80, arg3, arg3);
        func_002E70B0(buf, 8, arg4, arg5, arg6);
        return 0;
    }
    if (val < 8) {
        *arg4 = 0;
        *arg5 = 0;
        *arg6 = 0;
        return 0;
    }
    if (*(s32 *)(arg0 + 0xA0) == 0 && *(s16 *)(arg0 + 0xA4) == 0) {
        *(u16 *)(arg0 + 0xA0) = D_00347BEC;
        *(u16 *)(arg0 + 0xA2) = D_00347BEE;
        *(u16 *)(arg0 + 0xA4) = D_00347BF0;
    }
    *arg4 = *(u16 *)(arg0 + 0xA0);
    *arg5 = *(u16 *)(arg0 + 0xA2);
    *arg6 = *(u16 *)(arg0 + 0xA4);
    return 0;
}
