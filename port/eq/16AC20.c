#include "common.h"

void func_00147FB8(s32 arg0);
void func_0014EEF8(s32 arg0, s32 arg1);
void func_0016A468(s32 arg0);
s32 func_001F3758(s32 arg0);

void func_0016AC20(s32 arg0) {
    u8 *temp_s1;
    u8 *temp_v1;
    s32 v;

    temp_v1 = *(u8 **)((u8 *)arg0 + 0x38);
    temp_s1 = *(u8 **)(temp_v1 + 0xB0);
    v = func_001F3758(arg0);
    func_0014EEF8(*(s32 *)((u8 *)v + 0x38), (s32)(temp_v1 + 0xB4));
    func_0016A468(arg0);
    if (*(s32 *)(*(u8 **)(temp_s1 + 0x20) + 4) != 0) {
        func_00147FB8(*(s32 *)temp_s1);
    }
}
