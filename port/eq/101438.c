#include "common.h"

s32 func_001013B0(s32 arg0);
void func_002F52A8(s32 arg0, s32 arg1);
void func_002F7040(s32 arg0, s32 arg1, s32 arg2);
void func_002F6D90(s32 arg0);
extern void *D_00387F2C;
extern s32 gStgPanBlur;
extern s32 D_00387F20[];

void func_00101438(s32 arg0) {
    s32 temp_v1;

    func_002F52A8(gStgPanBlur, func_001013B0(arg0));
    temp_v1 = arg0 < 0x33B2;
    func_002F7040(gStgPanBlur, D_00387F20[temp_v1 != 0 ? 0 : 1], temp_v1 != 0 ? arg0 : arg0 - 0x33B2);
    func_002F6D90(*(s32 *)((u8 *)D_00387F2C + 0x10A4));
}
