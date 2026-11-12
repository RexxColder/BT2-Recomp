#include "common.h"

s32 BtlChar_GetPos(s32 arg0);
f32 BtlUtil_WrapAngle(f32 farg0);
f32 atan2f(f32 farg0, f32 farg1);
void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00312650(s32 arg0, s32 arg1, s32 arg2);
extern f32 D_0038585C;

void func_001FCD80(s32 arg0) {
    f32 sp[4];
    f32 f20;
    f32 var;
    u8 *p;

    p = (u8 *)arg0;
    if (*(s32 *)(p + 0x2A0) & 4) {
        func_002113C0(arg0, 0xE, 0x40, 1);
    }
    if (*(s32 *)(p + 0x2A0) & 0x20) {
        func_002113C0(arg0, 0xE, 0x400, 1);
    }
    if (*(s32 *)(p + 0x2A0) & 0x100) {
        func_00312650((s32)sp, BtlChar_GetPos(arg0), arg0 + 0x180);
        if ((D_0038585C < (sp[0] < 0.0f ? -sp[0] : sp[0])) ||
            (D_0038585C < (sp[2] < 0.0f ? -sp[2] : sp[2]))) {
            f20 = *(f32 *)(p + 0x15C);
            var = -BtlUtil_WrapAngle(atan2f(sp[0], sp[2]) - *(f32 *)(p + 0x150));
            if (f20 < (var < 0.0f ? -var : var)) {
                var = (var > 0.0f) ? f20 : -f20;
            }
            *(f32 *)(p + 0x158) = var;
        }
    }
    *(s32 *)(p + 0x2A0) = 0;
    *(s32 *)(p + 0x298) = 0;
}
