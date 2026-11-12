#include "common.h"

s32 BtlTaskList_AddTail(s32 arg0, void *arg1, void *arg2);
void EftPart10_LinkGroup(u8 *arg0, u8 *arg1, s32 arg2);
s32 func_0019B448(s32 arg0, s32 arg1);
void memset(void *arg0, s32 arg1, u32 arg2);
extern s32 D_00342198 __attribute__((section(".data")));
extern u8 *D_003877E8;

void func_0019B4A0(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3) {
    u8 sp[0x38];
    s32 temp_v0;

    memset(sp + 0x10, 0, 0x10);
    memset(sp + 0x20, 0, 0x10);
    *(s32 *)(sp + 0x30) = arg2;
    *(s32 *)(sp + 0x34) = arg3;
    *(s32 *)sp = 0;
    if (D_003877E8 != NULL) {
        *(f32 *)(sp + 0x10) = *(f32 *)(arg0 + 0);
        *(f32 *)(sp + 0x14) = *(f32 *)(arg0 + 4);
        *(f32 *)(sp + 0x18) = *(f32 *)(arg0 + 8);
        *(f32 *)(sp + 0x1C) = *(f32 *)(arg0 + 0xC);
        *(f32 *)(sp + 0x20) = *(f32 *)(arg1 + 0);
        *(f32 *)(sp + 0x24) = *(f32 *)(arg1 + 4);
        *(f32 *)(sp + 0x28) = *(f32 *)(arg1 + 8);
        *(f32 *)(sp + 0x2C) = *(f32 *)(arg1 + 0xC);
        *(s32 *)sp = *(s32 *)D_003877E8;
        temp_v0 = func_0019B448(BtlTaskList_AddTail(*(s32 *)(D_003877E8 + 0x27C), &D_00342198, sp), arg3);
        if (temp_v0 != 0) {
            EftPart10_LinkGroup(D_003877E8 + 0x238, D_003877E8 + 0x23C, temp_v0);
        }
    }
}
