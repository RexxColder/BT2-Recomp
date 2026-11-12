#include "common.h"

void func_002C22F0(void *arg0);
void func_002D0DD8(void *arg0, s32 arg1);

void func_002CF760(u8 *arg0) {
    u8 *temp_s1;
    u8 *temp_s2;
    u8 *temp_s3;

    temp_s1 = arg0 + 0x8A0;
    temp_s2 = arg0 + 0xD0C;
    temp_s3 = arg0 + 0xAD0;
    *(s32 *)(arg0 + 0) = 0;
    *(s32 *)(arg0 + 4) = 0;
    *(s32 *)(arg0 + 8) = 0;
    func_002C22F0(arg0 + 0xC);
    *(s32 *)(temp_s1 + 0) = 0;
    *(s32 *)(temp_s1 + 0x2C) = 0;
    *(s32 *)(temp_s1 + 4) = 0;
    *(s32 *)(temp_s1 + 8) = 0;
    *(s32 *)(temp_s1 + 0xC) = 0;
    *(s32 *)(temp_s1 + 0x10) = 0;
    *(s32 *)(temp_s1 + 0x28) = 0;
    *(s64 *)(temp_s1 + 0x18) = 0;
    *(s32 *)(temp_s3 + 8) = 0;
    *(s64 *)(temp_s1 + 0x20) = 0;
    *(s32 *)(temp_s3 + 0) = 0;
    *(s32 *)(temp_s3 + 4) = 0;
    func_002D0DD8(arg0 + 0xADC, 0x7FFFFFFF);
    *(s32 *)(temp_s2 + 0) = 0;
    *(s32 *)(temp_s2 + 4) = 0;
    *(s32 *)(temp_s2 + 8) = 1;
    *(s32 *)(temp_s2 + 0xC) = 0;
    *(s32 *)(temp_s2 + 0x10) = 0;
    *(s32 *)(temp_s2 + 0x14) = 0;
}
