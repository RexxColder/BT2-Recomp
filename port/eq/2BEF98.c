#include "common.h"

void func_002BF0D8(void *arg0, s32 arg1);
s32 func_002BE878(s32 arg0);
void func_002BF160(void *arg0, s32 *arg1, s64 arg2);
void func_002D3240(void *arg0, s64 *arg1);
s64 func_002F4D68(s32 arg0);
s32 func_002F6620(s32 arg0, s32 arg1);

s32 func_002BEF98(void *arg0, s32 arg1) {
    s64 buf[2];
    s32 sp10;
    s32 temp_s0;
    s64 temp_s1;
    s32 temp_s2;
    u8 *temp_s3;
    s32 var_a1;

    var_a1 = arg1;
    temp_s3 = *(u8 **)((u8 *)arg0 + 0x2004);
    temp_s2 = *(s32 *)temp_s3;
    switch (var_a1) {
    case 0:
        *(s32 *)(temp_s3 + 0x30) = 0;
        var_a1 = 0;
        func_002BF0D8(arg0, var_a1);
        break;
    case 1:
        func_002BF0D8(arg0, var_a1);
        break;
    case 2:
        if (func_002BE878(temp_s2) != 0) {
            temp_s1 = func_002F4D68(temp_s2);
            func_002BF160(arg0, &sp10, temp_s1);
            temp_s0 = sp10 + *(s32 *)(temp_s3 + 0x30);
            *(s32 *)(temp_s3 + 0x30) = temp_s0 - func_002F6620(temp_s2, temp_s0);
            buf[0] = (s64)sp10;
            buf[1] = temp_s1;
            func_002D3240((u8 *)arg0 + 0x1020, buf);
        }
        break;
    }
    return 0;
}
