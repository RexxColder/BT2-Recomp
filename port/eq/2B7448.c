#include "common.h"

s32 dpmul(s32 arg0, s64 arg1);
s32 dptoli(s32 arg0);
void func_002B81D8(void *arg0, s32 arg1, s32 arg2);
s32 litodp(s32 arg0);
extern s64 D_00378D50 __attribute__((section(".data")));

void func_002B7448(void *arg0) {
    s32 temp_s1;

    temp_s1 = *(s32 *)((u8 *)arg0 + 0x1C8);
    func_002B81D8(arg0, dptoli(dpmul(litodp(temp_s1), D_00378D50)), temp_s1);
}
