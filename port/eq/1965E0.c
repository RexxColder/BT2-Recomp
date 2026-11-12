#include "common.h"

void *memset(void *arg0, s32 arg1, u32 arg2);
void func_001966D0(s32 arg0, s32 arg1, s32 arg2, f32 farg3, f32 farg4, f32 farg5, f32 farg6, f32 farg7);
extern f32 D_00384C90;

void func_001965E0(s32 arg0, s32 arg1, s32 arg2) {
    f32 var_f12;
    f32 var_f13;

    memset((void *)(arg1 + 0xA10), 0, 0xC0);
    var_f12 = 1.0f;
    var_f13 = 1.0f;
    switch (arg2) {
    case 0:
        var_f12 = 2.0f;
        var_f13 = 4.0f;
        break;
    case 1:
        var_f12 = 1.5f;
        var_f13 = 3.0f;
        break;
    case 2:
        var_f12 = 1.0f;
        var_f13 = 2.0f;
        break;
    }
    func_001966D0(arg0, arg1, 0x4880, var_f12, var_f13, 128.0f, D_00384C90, 0.0f);
}
