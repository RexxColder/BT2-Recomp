#include "common.h"

void DemoCam_SetAnim(s32 arg0, s32 arg1, s32 arg2);
void DemoCam_SetTime(f32 farg0);
void func_0025AC68(s32 arg0);
void func_0025ABF0(void);
extern s32 D_00387A40;

void func_0025ADD0(s32 arg0, s32 arg1) {
    s32 s0 = *(s32 *)D_00387A40 + arg0 * 0x18580;
    s32 p = (arg1 << 2) + s0;
    s32 v0 = *(s32 *)(p + 0x748);

    if (v0 != 0) {
        DemoCam_SetAnim(v0, p, D_00387A40);
        func_0025AC68(s0);
        DemoCam_SetTime(0.0f);
        func_0025ABF0();
    }
}
