#include "common.h"

s32 func_001B0AF8(s32 arg0);
s32 func_001AEF80(s32 arg0, s32 arg1);
void func_001B0C00(s32 arg0);
void func_003126C8(s32 arg0, s32 arg1);

void func_001AE210(s32 arg0) {
    u8 fr[0x58];
    u8 *s0;
    u8 *s1;
    u8 *s2;
    f32 v;

    s0 = (u8 *)arg0;
    s1 = (u8 *)func_001B0AF8((s32)*(s16 *)(s0 + 0x12));
    if (s1 != NULL) {
        s2 = *(u8 **)(s1 + 0x38);
        func_003126C8((s32)(fr + 0x10), arg0);
        *(u8 *)(fr + 0x48) = *(u8 *)(s0 + 0x35);
        v = 15.0f;
        if (*(u8 *)(s2 + 0x5A) == 0) {
            v = -15.0f;
        }
        *(f32 *)(fr + 0x38) = v;
        *(s32 *)(fr + 0x4C) = arg0;
        *(s32 *)(fr + 0x50) = 0;
        *(f32 *)(fr + 0x3C) = *(f32 *)(s0 + 0x20);
        *(f32 *)(fr + 0x40) = *(f32 *)(s0 + 0x24);
        *(f32 *)(fr + 0x44) = (f32)*(s16 *)(s0 + 0x1C) * 30.0f;
        func_001AEF80((s32)s1, (s32)fr);
        if (*(s32 *)(s2 + 0x60) & 8) {
            func_001B0C00((s32)s1);
        }
        *(u8 *)(s1 + 1) = 2;
    }
}
