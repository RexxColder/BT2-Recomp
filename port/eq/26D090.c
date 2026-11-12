#include "common.h"

void Flash_CxformIdentity(s32 arg0);
void func_0026FBD0(s32 arg0);
void func_0026C4F8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_0026C578(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_0026C5F0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
void func_0026CF60(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_0026CFE0(s32 arg0, s32 arg1, s32 arg2);
extern u8 D_00387A70[] __attribute__((section(".data")));

void func_0026D090(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp[8];
    s32 sp20[8];
    s8 sp40;
    s8 sp41;
    u8 sp42;
    s8 sp44;
    s8 sp45;
    s32 temp_v1;
    s32 temp_a0;
    s32 temp_a1;
    u16 w40;
    u16 w44;

    func_0026FBD0((s32)sp);
    Flash_CxformIdentity((s32)sp20);
    temp_v1 = *(s32 *)arg2;
    temp_a0 = temp_v1 + 2;
    sp40 = *(s8 *)(arg1 + temp_v1);
    sp41 = *(s8 *)(arg1 + temp_v1 + 1);
    *(s32 *)arg2 = temp_a0;
    temp_a1 = temp_v1 + 3;
    sp42 = *(u8 *)(arg1 + temp_a0);
    *(s32 *)arg2 = temp_a1;
    sp44 = *(s8 *)(arg1 + temp_a1);
    sp45 = *(s8 *)(arg1 + temp_a1 + 1);
    *(s32 *)arg2 = temp_v1 + 5;
    w40 = (u16)((u8)sp40 | ((u8)sp41 << 8));
    w44 = (u16)((u8)sp44 | ((u8)sp45 << 8));

    if (sp42 == 2) {
        func_0026C578(*(s32 *)(arg0 + 0x14) + (12 * w40) - 12, w44, *(s32 *)arg0, 2);
        return;
    }
    if (sp42 < 3) {
        if (sp42 == 1) {
            func_0026CF60((s32)sp, arg1, arg2, 2);
            func_0026CFE0((s32)sp20, arg1, arg2);
            func_0026C4F8(*(s32 *)(arg0 + 0x14) + (12 * w40) - 12, w44, (s32)sp, (s32)sp20, *(s32 *)arg0);
        }
        return;
    }
    if (sp42 == 3) {
        func_0026CF60((s32)sp, arg1, arg2, 2);
        func_0026CFE0((s32)sp20, arg1, arg2);
        func_0026C5F0(*(s32 *)(arg0 + 0x14) + (12 * w40) - 12, w44, (s32)D_00387A70, (s32)sp, (s32)sp20, *(s32 *)arg0);
    }
}
