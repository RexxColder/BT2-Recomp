#include "common.h"

void func_00312638(s32 arg0, s32 arg1, s32 arg2);
s32 func_00312FB0(s32 arg0, s32 arg1, f32 farg0);
void sceVu0ClampVector(s32 arg0, s32 arg1, f32 farg0, f32 farg1);

void func_001E1F08(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 farg0) {
    u8 sp[0x150];
    s32 i;
    s32 s0;

    for (i = 0; i < 0x130; i++) {
        sp[i] = ((u8 *)arg1)[i];
    }
    func_00312FB0((s32)&sp[0x130], arg2, 1.0f);
    func_00312FB0((s32)&sp[0x140], arg3, 1.0f);
    s0 = arg0 + 0x30;
    func_00312638(s0, s0, (s32)&sp[0x130]);
    func_00312638(arg0 + 0x20, arg0 + 0x20, (s32)&sp[0x140]);
    *(f32 *)(arg0 + 0x44) = *(f32 *)(arg0 + 0x44) + farg0;
    sceVu0ClampVector(s0, s0, 0.0f, 255.0f);
}
