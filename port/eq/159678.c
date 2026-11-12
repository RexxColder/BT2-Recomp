#include "common.h"

void *func_0011E310(void);
void func_00129C28(void *arg0, void *arg1);
f32 func_00152958(void *arg0);
void func_00129BD0(f32 *arg1, f32 *arg2, f32 arg0);
void Vec3_Sub(f32 *arg0, void *arg1, void *arg2);
void Vec3_Add(void *arg0, void *arg1, f32 *arg2);
void Vec3_Normalize(f32 *arg0, f32 *arg1);
void func_00274338(s32 arg0, f32 *arg1);

void func_00159678(u8 *arg0) {
    u8 *s2, *s4, *s0, *s1, *s5;
    s32 v1;
    f32 f20;
    f32 sp[4];
    f32 v10[4];

    s2 = *(u8 **)(arg0 + 0x38);
    s4 = (u8 *)func_0011E310();
    s0 = s2 + 0xAB0;
    s1 = s2 + 0xAC0;
    for (v1 = 0; v1 < 0xF; v1++, s0 += 0x20, s1 += 0x20) {
        if (*(s32 *)s0 == 0) {
            *(f32 *)(s0 + 4) = 15.0f;
            *(s32 *)s0 = 1;
            s5 = s2 + 0x40;
            func_00129C28(s1, s4 + 0x10);
            f20 = *(f32 *)(s2 + 0x14) * func_00152958(s2 + 0xA4);
            Vec3_Sub(v10, s5, s1);
            Vec3_Normalize(v10, v10);
            func_00129BD0(v10, v10, f20 * 0.5f);
            Vec3_Add(s1, s1, v10);
            *(f32 *)(s0 + 0x1C) = 1.0f;
            func_00129C28(s2 + 0x70, s1);
            if (*(s32 *)(s4 + 0x40) >= 0) {
                Vec3_Sub(sp, s2 + 0x70, s5);
                Vec3_Normalize(sp, sp);
                sp[3] = 1.0f;
                func_00274338(*(s32 *)(s4 + 0x40), sp);
            }
            return;
        }
    }
}
