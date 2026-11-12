#include "common.h"

u8 *func_002CADD8(s32 arg0, s32 arg1, s32 arg2);
void func_002CA4A0(s32 arg0, s32 arg1, s32 arg2);
s32 func_002CB270(s32 arg0);
s32 func_002D2230(s32 arg0, s32 arg1, s32 arg2);

s32 func_002CA3E0(s32 arg0, s32 arg1, s32 arg2) {
    u8 *temp_s3;
    u8 *temp_s2;
    u8 *temp_v0;
    s32 temp_a2;
    s32 r;

    temp_s3 = (u8 *)arg0 + 0xD30;
    temp_s2 = func_002CADD8(arg0, arg1, arg2);
    if (temp_s2 == 0) {
        *(s32 *)arg1 = 0;
        return 0;
    }
    func_002CA4A0(arg0, (s32)temp_s2, arg1);
    temp_v0 = *(u8 **)arg1;
    temp_a2 = *(s32 *)(temp_v0 + 0x14);
    *(s32 *)(temp_s3 + 0x27C) = temp_a2;
    *(s32 *)(temp_s3 + 0x280) = *(s32 *)(temp_v0 + 0x18);
    if (func_002D2230(arg0, (s32)temp_v0, temp_a2) == 0) {
        *(s32 *)arg1 = 0;
        return 0;
    }
    if (*(s32 *)((u8 *)arg0 + 0x58) == 2) {
        r = func_002CB270(arg0);
        *(s32 *)(temp_s2 + 0x58) = r;
        *(s32 *)arg2 = r;
    }
    return 0;
}
