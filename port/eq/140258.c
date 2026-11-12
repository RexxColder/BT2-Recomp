#include "common.h"

extern f32 D_003844F4;

f32 EftMath_WrapAngle(f32 farg0);
f32 func_0012A3F8(f32 farg0);
f32 Mathf_Cos(f32 farg0);
void func_00312680(s32 arg0, s32 arg1, f32 farg0);
void func_00312638(s32 arg0, s32 arg1, s32 arg2);

s32 func_00140258(u8 *arg0) {
    u8 sp[0x20];
    u8 *s0;
    f32 f0;
    f32 f20;
    f32 wrap;
    f32 cosv;
    f32 o68;
    f32 o6c;
    f32 o64;
    f32 t2;
    f32 sp10;
    f32 sp14;
    f32 sp18;
    f32 o20;
    f32 o28;
    f32 o30;
    f32 o34;
    f32 o38;
    f32 o50;
    f32 o54;
    f32 o4c;
    f32 o44;
    f32 o48;
    f32 o74;
    f32 o80;
    f32 o84;
    f32 o58;
    f32 o5c;
    f32 o60;
    s32 b8f;
    s32 b94;
    s32 b90;
    s32 cond;

    b8f = *(u8 *)(arg0 + 0x8F);
    if (b8f == 0) {
        f0 = *(f32 *)(arg0 + 0x88) - 1.0f;
        *(f32 *)(arg0 + 0x88) = f0;
        if (f0 <= 0.0f) {
            *(f32 *)(arg0 + 0x88) = 0.0f;
            *(u8 *)(arg0 + 0x94) = 1;
            *(u8 *)(arg0 + 0x8F) = 2;
        }
    } else if (b8f == 1) {
        *(u8 *)(arg0 + 0x8F) = 2;
    }
    b94 = *(u8 *)(arg0 + 0x94);
    if (b94 == 0) {
        return 0;
    }

    s0 = arg0 + 0x20;
    wrap = EftMath_WrapAngle(*(f32 *)(arg0 + 0x64) / 180.0f * D_003844F4);
    f20 = wrap;
    f0 = func_0012A3F8(f20);
    *(s32 *)(arg0 + 0x24) = 0;
    *(f32 *)(arg0 + 0x20) = f0;
    cosv = Mathf_Cos(f20);
    *(f32 *)(arg0 + 0x2C) = 1.0f;

    o68 = *(f32 *)(arg0 + 0x68);
    o6c = *(f32 *)(arg0 + 0x6C);
    o64 = *(f32 *)(arg0 + 0x64);
    t2 = o68 * o6c;
    *(f32 *)(arg0 + 0x28) = cosv;
    *(f32 *)(arg0 + 0x64) = o64 + o68;
    *(f32 *)(arg0 + 0x68) = o68 + t2;
    func_00312680((s32)sp, (s32)s0, *(f32 *)(arg0 + 0x40));
    func_00312638((s32)(sp + 0x10), (s32)(arg0 + 0x10), (s32)sp);

    sp10 = *(f32 *)(sp + 0x10);
    sp14 = *(f32 *)(sp + 0x14);
    sp18 = *(f32 *)(sp + 0x18);
    *(f32 *)(sp + 0x1C) = 1.0f;
    o20 = *(f32 *)(arg0 + 0x20);
    o30 = *(f32 *)(arg0 + 0x30);
    o80 = *(f32 *)(arg0 + 0x80);
    o34 = *(f32 *)(arg0 + 0x34);
    o74 = *(f32 *)(arg0 + 0x74);
    o38 = *(f32 *)(arg0 + 0x38);
    o28 = *(f32 *)(arg0 + 0x28);
    o50 = *(f32 *)(arg0 + 0x50);
    o54 = *(f32 *)(arg0 + 0x54);
    o4c = *(f32 *)(arg0 + 0x4C);
    o44 = *(f32 *)(arg0 + 0x44);
    o48 = *(f32 *)(arg0 + 0x48);
    o84 = *(f32 *)(arg0 + 0x84);
    *(f32 *)(arg0 + 0x00) = sp10 + (o20 * o30) * o80;
    *(f32 *)(arg0 + 0x04) = (sp14 + o34 * o80) + (o74 * o80) * o80;
    *(f32 *)(arg0 + 0x08) = sp18 + (o28 * o38) * o80;
    *(f32 *)(arg0 + 0x50) = o50 + o50 * o54;
    *(f32 *)(arg0 + 0x4C) = o4c + o50;
    *(f32 *)(arg0 + 0x44) = o44 + o48;
    *(f32 *)(arg0 + 0x80) = o80 + o84;

    b90 = *(u8 *)(arg0 + 0x90);
    if ((b90 & 1) == 0) {
        return 1;
    }
    o58 = *(f32 *)(arg0 + 0x58);
    o5c = *(f32 *)(arg0 + 0x5C);
    o60 = *(f32 *)(arg0 + 0x60);
    f0 = o58 + o5c;
    *(f32 *)(arg0 + 0x58) = f0;
    if (0.0f < o5c) {
        cond = (o60 < f0);
    } else {
        cond = (f0 < o60);
    }
    if (cond) {
        *(f32 *)(arg0 + 0x58) = o60;
        *(u8 *)(arg0 + 0x90) = (u8)(b90 & 0xFE);
        return 1;
    }
    return 0;
}
