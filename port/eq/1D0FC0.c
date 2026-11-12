#include "common.h"

void Vec3_Normalize(s32 arg0, s32 arg1);
void func_001D8AE8(f32 farg0, s32 arg0, s32 arg1, f32 farg1);
extern f32 D_003853AC;
extern f32 D_003853B0;
extern u8 *D_00387E9C;

s32 func_001D0FC0(s32 arg0, s32 arg1, s32 arg2, f32 farg0) {
    s32 sp[4];
    s32 t;
    f32 f;

    t = arg2 & 0xFF;
    if (*(u8 *)(D_00387E9C + 0x1491) == 0) {
        return 0;
    }
    Vec3_Normalize((s32)sp, arg1);
    if (t == 0) {
        f = D_003853AC;
    } else if (t == 1) {
        f = D_003853B0;
    } else if (t == 2) {
        f = 1.0f;
    } else {
        return 1;
    }
    func_001D8AE8(f, arg0, (s32)sp, farg0);
    return 1;
}
