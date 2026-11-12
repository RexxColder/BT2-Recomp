#include "common.h"

void Vec3_Sub(s32 arg0, s32 arg1, s32 arg2);
void Vec3_Normalize(s32 arg0, s32 arg1);
f32 cosf(f32 arg0);
f32 sinf(f32 arg0);
s32 func_00126560(s32 arg0);
s32 func_001F42D8(s32 arg0);
void func_00208DE8(s32 arg0, s32 arg1, s32 arg2);
void func_002088F0(s32 arg0, s32 arg1, s32 arg2);
void func_002096C0(s32 arg0, s32 arg1, s32 arg2);
s32 func_0020A440(s32 arg0);

s32 func_0012D3A0(u8 *arg0, s32 arg1, s32 arg2) {
    s32 sp[4];
    s32 sp10[4];

    if (func_00126560((s32)arg0) != 0) {
        func_00208DE8(func_001F42D8(arg2), (s32)sp10, 0x11);
        Vec3_Sub((s32)arg0, (s32)sp10, arg1);
        Vec3_Normalize((s32)arg0, (s32)arg0);
    } else if (func_0020A440(arg2) != 0) {
        func_002096C0(arg2, (s32)arg0, arg1);
    } else {
        func_002088F0(arg2, (s32)sp, arg1);
        *(f32 *)(arg0 + 0x0) = sinf(*(f32 *)&sp[1]);
        *(s32 *)(arg0 + 0x4) = 0;
        *(f32 *)(arg0 + 0x8) = cosf(*(f32 *)&sp[1]);
        *(f32 *)(arg0 + 0xC) = 1.0f;
    }
    return 1;
}
