#include "common.h"

void func_00129C28(s32 arg0, s32 arg1);
extern f32 D_00384844;
extern f32 D_00384848;

void func_0016A488(s32 arg0, s32 arg1) {
    s32 t = *(s32 *)(arg0 + 0x38);
    s32 s0 = *(s32 *)(t + 0xB0);
    f32 val;

    func_00129C28(arg1 + 0x40, t + 0x40);
    *(s32 *)(arg1 + 0x50) = 0;
    if (**(s32 **)(s0 + 0x20) == 0x68) {
        val = D_00384844;
    } else {
        val = D_00384848;
    }
    *(f32 *)(arg1 + 0x38) = val;
    *(s32 *)(arg1 + 0x54) = 0;
    *(s32 *)(arg1 + 0x58) = 0;
    *(s32 *)(arg1 + 0x60) = 0;
    *(s32 *)(arg1 + 0x64) = 0;
    *(s32 *)(arg1 + 0x68) = 0;
}
