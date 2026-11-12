#include "common.h"

void Quat_FromEuler(s32 arg0, s32 arg1);
s32 func_00269A40(s32 arg0, s32 arg1);
void func_003126C8(s32 arg0, s32 arg1);

void func_00260BA0(s32 arg0, s32 arg1) {
    s32 sp[4];
    u8 *temp_v0;

    Quat_FromEuler((s32)sp, arg1);
    temp_v0 = (u8 *)func_00269A40(arg0, 1);
    func_003126C8((s32)(temp_v0 + 0x90), (s32)sp);
    *(s32 *)(temp_v0 + 0xD0) = *(s32 *)(temp_v0 + 0xD0) & ~1;
}
