#include "common.h"

s32 BtlObjVis_GetView_207EA0(s32 arg0);
void func_0026A2B0(s32 arg0, s32 arg1, f32 farg0);

void func_0020D3B0(s32 arg0, f32 farg0, s32 arg1) {
    s32 temp_v0;

    temp_v0 = BtlObjVis_GetView_207EA0(arg0);
    if (temp_v0 != 0) {
        func_0026A2B0(temp_v0, arg1, farg0);
    }
}
