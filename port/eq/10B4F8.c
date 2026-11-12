#include "common.h"

u8 *func_0010B078(s32 arg0);
void func_00297FE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void *memset(void *arg0, s32 arg1, u32 arg2);
extern u8 *D_003876A0;
extern u8 func_00119630[] __attribute__((section(".data")));

void func_0010B4F8(s32 arg0) {
    u8 *var_s0;

    /* a0 is not written before the first call: the function's own parameter, passed through */
    var_s0 = func_0010B078(arg0);
    if (*(s32 *)(D_003876A0 + 0xB8) != 6) {
        memset(var_s0 + 0x78, 0, 0x3C);
        func_00297FE0(1, 0x2C, 0x7F, 0x40, 1);
        *(s32 *)(var_s0 + 0x1350) = (s32)func_00119630;
    }
}
