#include "common.h"

void func_002C2FF0(s32 arg0, s32 arg1);
s32 func_002DA928(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

void func_002C53D8(s32 arg0, s32 *arg1, s32 arg2) {
    s32 sp[2];
    u8 *temp_s0;
    s32 temp_s1;
    s32 temp_s3;
    s32 temp_v1;

    temp_s0 = (u8 *)arg2 + 0x30;
    temp_s1 = *arg1;
    temp_s3 = func_002DA928(temp_s1, (s32)temp_s0, *(s32 *)(temp_s0 + 0x160), (s32)&sp[0], (s32)&sp[1]);
    temp_v1 = func_002DA928(temp_s1, arg2 + 0xE0, *(s32 *)(temp_s0 + 0x164), (s32)&sp[0], (s32)&sp[1]);
    if ((temp_s3 != 0) || (temp_v1 != 0)) {
        func_002C2FF0(arg0, 0xFF000D0D);
    }
}
