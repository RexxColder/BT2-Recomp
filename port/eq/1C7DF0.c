#include "common.h"

void Mtx_InverseRT(void *arg0, s32 arg1);
void Vec3_Cross(void *arg0, void *arg1, void *arg2);
void Vec3_Normalize(void *arg0, void *arg1);
void func_00129B28(void *arg0, void *arg1, void *arg2);
void func_00129B58(void *arg0, void *arg1, void *arg2);
void func_00129BD0(void *arg0, void *arg1, f32 farg0);
extern s32 gBtlCamView;

void func_001C7DF0(u8 *arg0) {
    s32 sp[16] __attribute__((aligned(16)));
    s32 sp30[4] __attribute__((aligned(16)));
    s32 sp40[4] __attribute__((aligned(16)));
    s32 sp50[4] __attribute__((aligned(16)));
    s32 sp60[4] __attribute__((aligned(16)));
    u8 *s3;
    u8 *fp;
    u8 *s0;
    u8 *s1;
    u8 *s2;
    u8 *s4;
    u8 *s6;
    u8 *s7;
    s32 s5;

    s5 = 0;
    s3 = *(u8 **)(arg0 + 0x38);
    Mtx_InverseRT(sp, gBtlCamView);
    fp = s3 + 0x330;
    if (*(s32 *)(s3 + 0x390) > 0) {
        s7 = (u8 *)sp40;
        s6 = (u8 *)sp50;
        s4 = (u8 *)sp60;
        s2 = s3;
        s1 = s2 + 0x50;
        do {
            func_00129B58(s7, s2, s1);
            func_00129B58(s6, sp30, s2);
            s0 = s2 + 0x20;
            Vec3_Cross(s0, s7, s6);
            s5 += 1;
            Vec3_Normalize(s0, s0);
            func_00129BD0(s0, s0, *(f32 *)(fp + 0x48));
            func_00129BD0(s4, s0, 0.5f);
            func_00129B28(s2 + 0x30, s2, s4);
            {
                u8 *dst = s2 + 0x40;
                u8 *src = s2;
                s2 = s1;
                func_00129B58(dst, src, s4);
            }
            s1 = s2 + 0x50;
        } while (s5 < *(s32 *)(s3 + 0x390));
    }
}
