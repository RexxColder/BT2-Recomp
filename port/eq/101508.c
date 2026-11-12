#include "common.h"

void func_002F52A8(s32 arg0, s32 arg1);
void func_002F7040(s32 arg0, s32 arg1, s32 arg2);
void func_002F6D90(s32 arg0);
extern s32 D_00387F1C;
extern u8 *D_00387F2C;
extern s32 D_00387F20;
extern s32 D_00387F24;

void func_00101508(s32 arg0) {
    s32 temp_v1;

    func_002F52A8(D_00387F1C, -0x3C0);
    temp_v1 = arg0 < 0x33B2;
    func_002F7040(D_00387F1C, temp_v1 != 0 ? D_00387F20 : D_00387F24,
                  temp_v1 != 0 ? arg0 : arg0 - 0x33B2);
    func_002F6D90(*(s32 *)(D_00387F2C + 0x10A4));
}
