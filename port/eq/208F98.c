#include "common.h"

s32 BtlObjVis_GetView_207EA0(s32 arg0);
s32 func_00269A40(s32 arg0, s32 arg1);
s32 sceVu0CopyMatrix(s32 arg0, s32 arg1);
s32 sceVu0UnitMatrix(s32 arg0, s32 arg1);

void func_00208F98(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_a1;
    s32 temp_v0;
    s32 temp_v0_2;

    temp_v0 = BtlObjVis_GetView_207EA0(arg0);
    if (temp_v0 == 0) {
        sceVu0UnitMatrix(arg1, arg2);
        return;
    }
    temp_v0_2 = func_00269A40(temp_v0, arg2);
    temp_a1 = temp_v0_2 + 0x40;
    if (temp_v0_2 == 0) {
        sceVu0UnitMatrix(arg1, temp_a1);
        return;
    }
    sceVu0CopyMatrix(arg1, temp_a1);
}
