#include "common.h"

void func_002BBC08(u8 *arg0);
s32 func_002BC1A0(u8 *arg0);
void func_002C33D8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

void func_002BBFF8(u8 *arg0, s32 arg1) {
    s32 temp_s2;
    s32 temp_s3;
    void **temp_s1;
    u8 *temp_s0;

    temp_s0 = arg0 + (arg1 << 5) + 0x284;
    temp_s3 = *(s32 *)(arg0 + 0x3C);
    temp_s1 = *(void ***)(temp_s0 + 0x14);
    temp_s2 = *(s32 *)(temp_s0 + 0x18);
    if (func_002BC1A0(temp_s0) == 1) {
        func_002BBC08(temp_s0);
        (*(void (**)(void *))((u8 *)(*temp_s1) + 0x14))(temp_s1);
        func_002C33D8(temp_s3, temp_s2 + 0xC0, (s32)temp_s1, 0, 0);
    }
}
