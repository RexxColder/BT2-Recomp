#include "common.h"

s32 BtlObj_Get(s32 arg0, s32 arg1);
void DemoCam_SetAnim(s32 arg0, s32 arg1);
void DemoCam_SetTime(s32 arg0, f32 farg0);
void func_0025ABF0(s32 arg0, s32 arg1);
void DemoCam_StartAutoOnce(s32 arg0, s32 arg1);

void func_0025B8A8(s32 arg0, s32 arg1) {
    s32 obj = BtlObj_Get(arg0, arg1);

    DemoCam_SetAnim(obj, arg1);
    DemoCam_SetTime(obj, 0.0f);
    if (arg1 != 0) {
        func_0025ABF0(obj, arg1);
    } else {
        DemoCam_StartAutoOnce(obj, arg1);
    }
}
