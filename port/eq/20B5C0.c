#include "common.h"

void *func_00211288(s32 arg0);
extern s32 D_00387930;

void func_0020B5C0(u32 arg0, f32 *arg1, f32 *arg2) {
    u8 *temp_v0;

    if ((D_00387930 != 0) && (arg0 < 2U)) {
        temp_v0 = (u8 *)func_00211288((s32)arg0);
        if (arg1 != NULL) {
            *arg1 = *(f32 *)(temp_v0 + 0x8);
        }
        if (arg2 != NULL) {
            *arg2 = *(f32 *)(temp_v0 + 0xC);
        }
    }
}
