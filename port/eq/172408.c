#include "common.h"

s32 func_0011E310(s32 arg0);
s32 func_00129C28(s32 arg0, s32 arg1);
void func_00129BD0(s32 arg0, s32 arg1, f32 farg0);
void Vec3_Add(s32 arg0, s32 arg1, s32 arg2);
void Vec3_Sub(s32 arg0, s32 arg1, s32 arg2);
void Vec3_Normalize(s32 arg0, s32 arg1);

void func_00172408(u8 *arg0) {
    f32 frame[8];
    u8 *s0;
    u8 *s1;
    u8 *s2;
    u8 *s4;
    u8 *s5;
    s32 v1;

    s2 = *(u8 **)(arg0 + 0x38);
    s5 = (u8 *)func_0011E310((s32)arg0);
    v1 = 0;
    s0 = s2 + 0xAE0;
    s1 = s2 + 0xAF0;

    for (;;) {
        if (*(s32 *)s0 == 0) {
            break;
        }
        v1++;
        s0 += 0x20;
        s1 += 0x20;
        if (v1 >= 5) {
            return;
        }
    }

    *(s32 *)(s0 + 4) = 0;
    *(s32 *)s0 = 1;
    s4 = s2 + 0x40;
    func_00129C28((s32)s1, (s32)(s5 + 0x10));
    Vec3_Sub((s32)&frame[4], (s32)s4, (s32)s1);
    Vec3_Normalize((s32)&frame[4], (s32)&frame[4]);
    func_00129BD0((s32)&frame[4], (s32)&frame[4], 0.0f);
    s2 += 0x70;
    Vec3_Add((s32)s1, (s32)s1, (s32)&frame[4]);
    *(f32 *)(s0 + 0x1C) = 1.0f;
    func_00129C28((s32)s2, (s32)s1);
    if (*(s32 *)(s5 + 0x40) >= 0) {
        Vec3_Sub((s32)&frame[0], (s32)s2, (s32)s4);
        Vec3_Normalize((s32)&frame[0], (s32)&frame[0]);
        frame[3] = 1.0f;
    }
}
