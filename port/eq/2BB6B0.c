#include "common.h"

void func_002B81A0(s32 arg0, s32 arg1, s32 arg2);
void func_002D2128(s32 arg0, s32 arg1);
s32 Rand_Range(s32 arg0);
s32 func_002B5B48(s32 arg0);
extern u8 D_00379E20[] __attribute__((section(".data")));

s32 func_002BB6B0(s32 arg0) {
    s32 sp[2];
    s32 temp_v0;

    func_002B81A0(arg0, 0x36, (s32)sp);
    func_002D2128(*(s32 *)((u8 *)arg0 + 0x3C), (s32)&sp[1]);
    if (sp[1] <= 0) {
        Rand_Range((s32)D_00379E20);
        *(s32 *)((u8 *)arg0 + 0x2FC) = sp[0];
        return -1;
    }
    temp_v0 = sp[0] - ((((func_002B5B48(arg0) * 0x3E8) / sp[1]) * 0xBB8) >> 1);
    *(s32 *)((u8 *)arg0 + 0x2FC) = temp_v0;
    return temp_v0;
}
