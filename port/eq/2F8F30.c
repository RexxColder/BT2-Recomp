#include "common.h"

void func_002F8F20(void);
u32 func_00309AD0(s32 arg0, s32 arg1, s32 arg2, u8 *arg3, s32 t0, s32 t1, u8 *t2, s32 t3, s32 sp0);
u32 func_0030A3C0(s32 arg0, s32 arg1, s32 arg2, u8 *arg3, s32 t0, u8 *t1, s32 t2, s32 t3, u8 *sp0, s32 sp8, s32 sp10);

void func_002F8F30(u8 *arg0) {
    s32 var_v1;
    u32 temp_v0;

    var_v1 = *(s32 *)(arg0 + 0xC);
    if (var_v1 == 1) {
        var_v1 = 2;
        *(s32 *)(arg0 + 0xC) = 2;
    }
    if (var_v1 == 2) {
        if (*(s32 *)(arg0 + 0x14) != 1) {
            temp_v0 = func_0030A3C0(*(s32 *)(arg0 + 0x18), *(s32 *)(arg0 + 0x1C), *(s32 *)(arg0 + 0x20), arg0 + 0x28,
                                    *(s32 *)(arg0 + 0x24), arg0 + 0x2C, *(s16 *)(arg0 + 0x30), *(s16 *)(arg0 + 0x32),
                                    arg0 + 0x34, *(s16 *)(arg0 + 0x36), *(s16 *)(arg0 + 0x38));
            *(u32 *)(arg0 + 0x10) = temp_v0;
            if ((s32)temp_v0 % 2 == 1) {
                func_002F8F20();
            }
        } else {
            *(u32 *)(arg0 + 0x10) = func_00309AD0(*(s32 *)(arg0 + 0x18), *(s32 *)(arg0 + 0x1C), *(s32 *)(arg0 + 0x20),
                                                  arg0 + 0x28, *(s16 *)(arg0 + 0x30), *(s16 *)(arg0 + 0x32),
                                                  arg0 + 0x34, *(s16 *)(arg0 + 0x36), *(s16 *)(arg0 + 0x38));
        }
        *(s32 *)(arg0 + 0xC) = 3;
    }
}
