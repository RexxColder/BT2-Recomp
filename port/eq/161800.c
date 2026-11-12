#include "common.h"

void func_00129C28(s32 arg0, s32 arg1);

void func_00161800(s32 arg0, s32 arg1) {
    func_00129C28(arg1 + 0x40, *(s32 *)(arg0 + 0x38) + 0x40);
    *(s32 *)(arg1 + 0x50) = 0;
    *(s32 *)(arg1 + 0x54) = 0;
    *(f32 *)(arg1 + 0x38) = 1.0f;
    *(s32 *)(arg1 + 0x58) = 0;
    *(s32 *)(arg1 + 0x60) = 0;
    *(s32 *)(arg1 + 0x64) = 0;
    *(s32 *)(arg1 + 0x68) = 0;
}
