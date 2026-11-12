#include "common.h"

void func_001AC178(void *arg0, s32 arg1, u8 arg2, s32 arg3);
void func_001AC388(void *arg0, s32 arg1, u8 arg2, s32 arg3);
void func_001F3738(void *arg0, s32 arg1);
void *memset(void *arg0, s32 arg1, u32 arg2);

void func_001AC530(void *arg0, void *arg1) {
    s32 var_v0;
    u8 temp_a2;
    u8 *temp_s1;

    temp_s1 = *(u8 **)((u8 *)arg0 + 0x38);
    memset(temp_s1, 0, 0x1D0);
    *(s64 *)(temp_s1 + 0x0) = *(s64 *)((u8 *)arg1 + 0x0);
    *(s64 *)(temp_s1 + 0x8) = *(s64 *)((u8 *)arg1 + 0x8);
    *(s64 *)(temp_s1 + 0x10) = *(s64 *)((u8 *)arg1 + 0x10);
    *(s64 *)(temp_s1 + 0x18) = *(s64 *)((u8 *)arg1 + 0x18);
    temp_a2 = temp_s1[0x1A];
    *(s64 *)(temp_s1 + 0x20) = *(s64 *)((u8 *)arg1 + 0x20);
    *(s64 *)(temp_s1 + 0x28) = *(s64 *)((u8 *)arg1 + 0x28);
    *(s64 *)(temp_s1 + 0x30) = *(s64 *)((u8 *)arg1 + 0x30);
    *(s64 *)(temp_s1 + 0x38) = *(s64 *)((u8 *)arg1 + 0x38);
    *(u16 *)(temp_s1 + 0x10) = *(u16 *)((u8 *)arg1 + 0x12);
    if (temp_a2 == 14) {
        func_001AC388(arg0, 0xE, temp_a2, 0xF);
        var_v0 = *(s32 *)(temp_s1 + 0xC0) | 0x2000;
        *(s32 *)(temp_s1 + 0xC0) = var_v0;
    } else if (temp_a2 == 15) {
        func_001AC178(arg0, 0xE, temp_a2, 0xF);
        var_v0 = *(s32 *)(temp_s1 + 0xC0) | 0x1000;
        *(s32 *)(temp_s1 + 0xC0) = var_v0;
    }
    *(s32 *)(temp_s1 + 0xC0) = *(s32 *)(temp_s1 + 0xC0) | 0xC0;
    func_001F3738(arg0, 0x2000);
}
