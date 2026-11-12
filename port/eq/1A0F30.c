#include "common.h"

s32 BtlTask_SetDead(s32 arg0);
void func_00151FB0(s32 arg0);
s32 func_00152200(s32 arg0, s32 arg1);
void func_001A0CA8(s32 arg0, s32 arg1);
void func_00208798(s32 arg0, s32 arg1);
s32 func_0020A0A8(s32 arg0);
f32 sinf(f32 farg0);
extern f32 D_00384E10;
extern f32 D_00384E14;
extern f32 D_00384E18;
extern u8 *D_003876A0;

void func_001A0F30(u8 *arg0) {
    u8 *s0;
    u8 *s2;
    s32 varA0;
    s32 v1;
    f32 f4;

    varA0 = 0;
    s0 = *(u8 **)(arg0 + 0x38);

    if (!(*(s64 *)(D_003876A0 + 0x4D8) & 0x100)) {
        if (func_0020A0A8(*(s32 *)s0) != 0 && !(*(s32 *)(s0 + 0x40) & 0x20)) {
            func_00208798(*(s32 *)s0, (s32)(s0 + 0x10));
            *(s32 *)(s0 + 0x40) = *(s32 *)(s0 + 0x40) | 0x20;
            *(f32 *)(s0 + 0x14) = *(f32 *)(s0 + 0x14) - ((*(f32 *)(s0 + 0x48) * 6.0f) + 20.0f);
        }
        s2 = s0 + 0x70;
        func_00151FB0((s32)s2);
        f4 = *(f32 *)(s0 + 0x50) + D_00384E10;
        *(f32 *)(s0 + 0x64) = sinf(*(f32 *)(s0 + 0x50)) * *(f32 *)(s0 + 0x48);
        *(f32 *)(s0 + 0x50) = f4;
        if (D_00384E14 < f4) {
            *(f32 *)(s0 + 0x50) = f4 - D_00384E18;
        }
        func_001A0CA8(*(s32 *)s0, (s32)arg0);
        varA0 = func_00152200(*(s32 *)(s0 + 0x34), (s32)s2) != 0;
    }

    v1 = *(s32 *)(s0 + 0x40);
    if (varA0 == 0 && (v1 & 8)) {
        BtlTask_SetDead((s32)arg0);
        return;
    }
    if (v1 & 2) {
        *(s32 *)(s0 + 0x40) = v1 | 8;
    }
}
