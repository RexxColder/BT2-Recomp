#include "common.h"

void func_002C0448(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

s32 func_002C0190(s32 arg0, s32 arg1, u8 *arg2, s32 arg3) {
    s32 sp[6];
    u8 *temp_a0;
    s32 temp_a0_2;

    *(s32 *)(arg2 + 4) = 0;
    *(s32 *)(arg2 + 0xC) = 0;
    temp_a0 = (u8 *)(arg0 + 0x1310 + arg1 * 0x74);
    *(s32 *)(arg2 + 0x14) = 0;
    *(s32 *)(arg2 + 0x18) = 0;
    *(s32 *)(arg2 + 0) = 0;
    *(s32 *)(arg2 + 8) = 0;
    *(s32 *)(arg2 + 0x10) = 0;
    temp_a0_2 = *(s32 *)(temp_a0 + 0x14);
    if ((*(s32 *)(temp_a0 + 4) == 0) || (temp_a0_2 == 0)) {
        return 0;
    }
    func_002C0448(temp_a0_2, arg3, (s32)sp, (s32)&sp[4]);
    *(s32 *)(arg2 + 0) = sp[0];
    *(s32 *)(arg2 + 0xC) = sp[5];
    *(s32 *)(arg2 + 4) = sp[1];
    *(s32 *)(arg2 + 8) = sp[4];
    return 0;
}
