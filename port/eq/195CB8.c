#include "common.h"

s32 Vec4_Set(s32 arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3);
void func_00129C28();
void func_0014EAE8(s32 arg0, s32 arg1);
void func_001965E0(s32 arg0, s32 arg1, s32 arg2);
void func_001F3738(s32 arg0, s32 arg1);
s32 func_001F3758(s32 arg0);
s32 func_00208DE8(s32 arg0, s32 arg1, s32 arg2);
s32 memset(s32 arg0, s32 arg1, s32 arg2);

void func_00195CB8(s32 arg0, s32 arg1) {
    f32 sp[4];
    u8 *s2;
    u8 *s1;
    u8 *s0;
    u8 *v0;
    u8 *v1;
    s32 temp_s6;
    s32 *temp_s4;
    s32 temp_a0;
    s64 a2;
    s64 a3;
    s64 a1;
    s64 x0;
    s64 x8;
    s64 x16;
    s64 x24;

    s2 = *(u8 **)((u8 *)arg0 + 0x38);
    temp_s6 = *(s32 *)((u8 *)func_001F3758(arg0) + 0x38);
    temp_s4 = *(s32 **)((u8 *)arg1 + 0x20);
    memset((s32)s2, 0, 0xB80);
    v1 = s2 + 0xAD0;
    v0 = (u8 *)arg1;
    a2 = 0;
    a3 = 0;
    do {
        x0 = *(s64 *)(v0 + 0);
        x8 = *(s64 *)(v0 + 8);
        x16 = *(s64 *)(v0 + 0x10);
        x24 = *(s64 *)(v0 + 0x18);
        *(s64 *)(v1 + 0) = x0;
        *(s64 *)(v1 + 8) = x8;
        *(s64 *)(v1 + 0x10) = x16;
        *(s64 *)(v1 + 0x18) = x24;
        a2 = x8;
        a3 = x16;
        v0 += 0x20;
        v1 += 0x20;
    } while (v0 != (u8 *)arg1 + 0x40);
    *(s64 *)(v1 + 0) = *(s64 *)(v0 + 0);
    a1 = *(s64 *)(v0 + 8);
    s1 = s2 + 0xB30;
    s0 = s2 + 0xB40;
    *(s64 *)(v1 + 8) = a1;
    func_00129C28((s32)(s2 + 0xB20), arg1, a2, a3);
    func_00129C28((s32)s1, arg1);
    func_00208DE8(*temp_s4, (s32)sp, 0x11);
    Vec4_Set((s32)s0, sp[0], sp[1], sp[2], 1.0f);
    func_00129C28((s32)s0, (s32)sp);
    func_00129C28((s32)(s2 + 0xB50), arg1 + 0x10);
    func_00129C28((s32)(s2 + 0xB60), (s32)s1);
    *(f32 *)(s2 + 0xB6C) = 1.0f;
    temp_a0 = *(s32 *)(s2 + 0xAF4);
    *(s32 *)(s2 + 0xA00) = temp_a0;
    func_0014EAE8(temp_a0, (s32)s2);
    func_001965E0(temp_s6, (s32)s2, *(s32 *)(s2 + 0xB04));
    func_001F3738(arg0, (*temp_s4 != 0) ? 0x1000 : 0x800);
}
