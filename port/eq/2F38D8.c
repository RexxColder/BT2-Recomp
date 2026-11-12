#include "common.h"

void func_00331710();
s32 func_00303AB8(s32 arg0, s32 arg1);
u8 *func_00303A78(s32 arg0, s32 arg1);
s32 func_00306798(s32 arg0, s32 arg1);
extern u8 D_0037C6B8[] __attribute__((section(".data")));
extern u8 D_0037C6D8[] __attribute__((section(".data")));
extern u8 D_0037C6F8[] __attribute__((section(".data")));

void func_002F38D8(u8 *arg0) {
    s32 temp_s0;
    s32 temp_s1;
    s32 temp_s0_2;
    s32 temp_s1_2;
    s32 temp_s2;
    s32 temp_s3;
    u8 *temp_v0;

    temp_s0 = *(s32 *)(arg0 + 0xC);
    temp_s1 = func_00303AB8(temp_s0, 0);
    temp_v0 = func_00303A78(temp_s0, 0);
    temp_s2 = ((s32 (*)(u8 *, s32))(*(void **)(*(u8 **)temp_v0 + 0x24)))(temp_v0, 1);
    temp_s3 = ((s32 (*)(u8 *, s32))(*(void **)(*(u8 **)temp_v0 + 0x24)))(temp_v0, 0);
    temp_s0_2 = func_00306798(temp_s1, 1);
    temp_s1_2 = func_00306798(temp_s1, 0);
    func_00331710(D_0037C6B8, temp_s2, temp_s3, temp_s2 + temp_s3);
    func_00331710(D_0037C6D8, temp_s0_2, temp_s1_2, temp_s0_2 + temp_s1_2);
    func_00331710(D_0037C6F8, *(s8 *)(arg0 + 1), (temp_s2 + temp_s1_2) + (temp_s0_2 + temp_s3));
}
