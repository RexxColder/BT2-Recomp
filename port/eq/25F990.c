#include "common.h"

s32 func_0025EF60(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_0025E7A0(s32 arg0, s32 arg1);

void func_0025F990(s32 arg0, s16 arg1, s32 arg2) {
    s32 sp[4];
    s32 temp_v0;
    u8 *s0;
    u8 *base;
    f32 temp_f1;
    f32 temp_f2;
    s32 flag;

    base = (u8 *)arg0;
    flag = arg2 & 0xFF;
    temp_v0 = func_0025EF60(arg0, arg0 + 0x3580, arg1, (s32)sp);
    s0 = base + 0xBD0;
    *(s32 *)(s0 + 0x28) = temp_v0;
    if (temp_v0 != 0) {
        *(s16 *)(s0 + 4) = arg1;
        temp_f1 = (f32)*(u16 *)((u8 *)temp_v0 + 2);
        *(f32 *)(s0 + 8) = temp_f1;
        if (flag != 0) {
            *(f32 *)(s0 + 0x10) = 0.0f;
            *(f32 *)(s0 + 0x14) = 0.0f;
        } else {
            if (temp_f1 < *(f32 *)(s0 + 0x10)) {
                *(f32 *)(s0 + 0x10) = temp_f1;
            }
            temp_f2 = *(f32 *)(s0 + 8);
            if (temp_f2 < *(f32 *)(s0 + 0x14)) {
                *(f32 *)(s0 + 0x14) = temp_f2;
            }
        }
        memset(s0 + 0x30, 0, 0x8E);
        if (*(u8 *)(base + 0xE5C) != 0) {
            func_0025E7A0(arg0, *(s32 *)(s0 + 0x28));
        }
    }
}
