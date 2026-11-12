#include "common.h"

void func_003126C8(s32 arg0, s32 arg1);
void *memset(void *s, s32 c, u32 n);

void func_00123CD8(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_s1;

    temp_s1 = arg0 + 0x160;
    func_003126C8(temp_s1, arg1);
    func_003126C8(arg0 + 0x170, arg2);
    *(s32 *)(temp_s1 + 0x28) = 0;
    *(s32 *)(temp_s1 + 0x2C) = 0;
    memset((void *)(arg0 + 0xA9C), 0, 0x100);
    *(s32 *)(arg0 + 0xBE0 + 4) = 0;
    *(s32 *)(temp_s1 + 0x30) = 0;
    *(s32 *)(temp_s1 + 0x34) = 1;
}
