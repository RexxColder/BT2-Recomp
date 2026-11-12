#include "common.h"

void *memset(void *arg0, s32 arg1, u32 arg2);
void func_002088F0(s32 arg0, s32 *arg1);
void func_001A1A28(void *arg0, void *arg1, void *arg2);
void func_001A1C80(void *arg0, void *arg1, void *arg2);
f32 sinf(f32 arg0);
f32 cosf(f32 arg0);
extern u8 D_0036E9E0[];
extern s32 D_00387818;

void func_001A18A8(void *arg0, void *arg1) {
    s32 sp[4];
    s64 sp10[2];
    f32 temp_f0;
    f32 temp_f1;
    s32 temp_s2;
    u8 *temp_s0;
    u8 *temp_s3;

    temp_s0 = *(u8 **)((u8 *)arg0 + 0x38);
    temp_s2 = D_00387818 + 8;
    temp_s3 = temp_s0 + 0x20;
    memset(temp_s0, 0, 0x340);
    *(s64 *)(temp_s0 + 0x10) = *(s64 *)((u8 *)arg1 + 0x0);
    *(s64 *)(temp_s0 + 0x18) = *(s64 *)((u8 *)arg1 + 0x8);
    *(s64 *)(temp_s0 + 0x20) = *(s64 *)((u8 *)arg1 + 0x10);
    *(s32 *)(temp_s0 + 0x330) = temp_s2;
    *(s64 *)(temp_s0 + 0x28) = *(s64 *)((u8 *)arg1 + 0x18);
    sp10[1] = *(s64 *)(D_0036E9E0 + 0x8);
    sp10[0] = *(s64 *)(D_0036E9E0 + 0x0);
    func_002088F0(*(s32 *)(temp_s0 + 0x10), sp);
    temp_f1 = *(f32 *)&sp[1];
    temp_f0 = -sinf(temp_f1);
    *((s32 *)sp10 + 1) = 0;
    *(f32 *)sp10 = temp_f0;
    temp_f1 = *(f32 *)&sp[1];
    *(f32 *)&sp10[1] = -cosf(temp_f1);
    func_001A1A28(temp_s0, temp_s3, sp10);
    func_001A1C80(temp_s0, temp_s3, sp10);
}
