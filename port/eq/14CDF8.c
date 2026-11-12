#include "common.h"

s32 func_001F3758(s32 arg0);
void func_0014C508(s32 arg0);
void func_0014EEF8(s32 arg0, s32 arg1);
void func_00147FB8(s32 arg0);

void func_0014CDF8(s32 arg0) {
    s32 temp_v0;
    s32 temp_s1;
    s32 temp_s2;
    s32 temp_s0;

    temp_v0 = func_001F3758(arg0);
    temp_s2 = *(s32 *)(arg0 + 0x38);
    temp_s1 = *(s32 *)(temp_v0 + 0x38);
    temp_s0 = *(s32 *)(temp_s2 + 0xB0);
    func_0014C508(arg0);
    func_0014EEF8(temp_s1, temp_s2 + 0xB4);
    if (*(s32 *)(*(s32 *)(temp_s0 + 0x20) + 4) != 0) {
        func_00147FB8(*(s32 *)temp_s0);
    }
}
