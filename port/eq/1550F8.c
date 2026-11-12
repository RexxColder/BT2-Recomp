#include "common.h"

void func_00147FB8(s32 arg0);
void func_0014EEF8(s32 arg0, s32 arg1);
s32 func_001F3758(s32 arg0);

void func_001550F8(s32 arg0) {
    s32 temp_a1;
    s32 temp_s0;

    temp_a1 = *(s32 *)(arg0 + 0x38);
    temp_s0 = *(s32 *)(temp_a1 + 0xB0);
    func_0014EEF8(*(s32 *)(func_001F3758(arg0) + 0x38), temp_a1 + 0xB4);
    if (*(s32 *)(*(s32 *)(temp_s0 + 0x20) + 4) != 0) {
        func_00147FB8(*(s32 *)temp_s0);
    }
}
