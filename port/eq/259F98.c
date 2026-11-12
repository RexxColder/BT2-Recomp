#include "common.h"

void func_0026EA88(s32 arg0);
void func_0026EAE0(s32 arg0, s32 arg1);
void func_00298460(s32 arg0, s32 arg1, s32 arg2);
void func_002984E0(s32 arg0);
extern u8 *D_00387A10;

void func_00259F98(s32 arg0, s32 arg1) {
    s32 temp_a1;

    *(s32 *)(D_00387A10 + 0xBC) = arg0;
    *(s32 *)(D_00387A10 + 0xC0) = arg1;
    func_0026EAE0((s32)(D_00387A10 + 0x54), 0x1E);
    func_0026EA88((s32)(D_00387A10 + 0x54));
    temp_a1 = arg0 * 0x30;
    if (arg0 == 0x3E8) {
        func_002984E0(arg1);
        return;
    }
    func_00298460(arg0, *(s32 *)((u8 *)(temp_a1 + *(s32 *)(D_00387A10 + 0xC4)) + 0x10), 1);
}
