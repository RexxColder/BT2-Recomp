#include "common.h"

s32 func_00126560(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_001F42D8(s32 arg0);
void func_00208DE8(s32 arg0, s32 arg1, s32 arg2);
void Vec3_Sub(s32 arg0, s32 arg1, s32 arg2);
void Vec3_Normalize(s32 arg0, s32 arg1);
s32 func_0020A440(s32 arg0);
void func_002088F0(s32 arg0, s32 arg1);
f32 sinf(f32 farg0);
f32 cosf(f32 farg0);
void func_002096C0(s32 arg0, s32 arg1, s32 arg2);
void func_00129C28(s32 arg0, s32 arg1);

s32 func_0012D488(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3) {
    f32 sp[8];
    s32 v;

    if (func_00126560((s32)arg0, (s32)arg1, arg2, arg3) != 0) {
        v = func_001F42D8(arg3);
        func_00208DE8(v, (s32)&sp[4], 0x11);
        Vec3_Sub((s32)arg1, (s32)&sp[4], arg2);
        Vec3_Normalize((s32)arg1, (s32)arg1);
    } else if (func_0020A440(arg3) == 0) {
        func_002088F0(arg3, (s32)sp);
        *(f32 *)(arg1 + 0) = sinf(sp[1]);
        *(s32 *)(arg1 + 4) = 0;
        *(f32 *)(arg1 + 8) = cosf(sp[1]);
        *(f32 *)(arg1 + 0xC) = 1.0f;
    } else if (arg0 != NULL) {
        if (*(s16 *)(*(u8 **)(arg0 + 0x20) + 0x4A) != 0) {
            if (!(*(s32 *)(arg0 + 0x40) & 2)) {
                func_002096C0(arg3, (s32)arg1, arg2);
                func_00129C28((s32)(arg0 + 0x30), (s32)arg1);
                *(s32 *)(arg0 + 0x40) = *(s32 *)(arg0 + 0x40) | 2;
            } else {
                func_00129C28((s32)arg1, (s32)(arg0 + 0x30));
            }
        } else {
            func_002096C0(arg3, (s32)arg1, arg2);
        }
    }
    return 1;
}
