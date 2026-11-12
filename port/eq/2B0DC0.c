#include "common.h"

void func_00312650(s32 arg0, s32 arg1, s32 arg2);
void func_003126C8(s32 arg0, s32 arg1);
s32 func_00269A40(s32 arg0, s32 arg1);
void Quat_ToEuler(s32 arg0, s32 arg1);

void func_002B0DC0(s32 arg0) {
    s32 sp[4];
    s32 temp_v0;

    func_00312650(arg0 + 0xD0, *(s32 *)arg0 + 0x9C0, arg0 + 0xF0);
    func_003126C8(arg0 + 0xE0, *(s32 *)arg0 + 0x9B0);
    temp_v0 = func_00269A40(*(s32 *)arg0, 0);
    func_003126C8(arg0 + 0x100, temp_v0 + 0x80);
    func_003126C8((s32)sp, temp_v0 + 0x90);
    Quat_ToEuler(arg0 + 0x110, (s32)sp);
}
