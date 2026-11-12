#include "common.h"

void Vu0Screen_StoreMtx(s32 arg0);
void func_00129C28(s32 arg0, s32 arg1);
void Vec3_Sub(s32 arg0, s32 arg1, s32 arg2);
void Vec3_Normalize(s32 arg0, s32 arg1);
f32 func_00129CD8(s32 arg0, s32 arg1);
void func_00144EE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 arg10, s64 arg11);
extern s32 gBtlCamView;
extern u8 *gEftBound;

void func_00145368(s32 arg0) {
    u8 sp20[0x40] __attribute__((aligned(16)));
    u8 sp60[0x10] __attribute__((aligned(16)));
    u8 sp70[0x10] __attribute__((aligned(16)));
    s64 sp80;
    s64 sp88;
    s32 temp_s0;
    s32 temp_s4;
    u8 *temp_s5;
    u8 *var_s1;
    s32 var_s6;
    s32 lo_a;
    s32 hi_a;
    s32 lo_b;
    s32 hi_b;
    u8 *temp_a0;

    temp_s5 = gEftBound + 0x10;
    var_s6 = 0;
    temp_s0 = arg0 + 0x30;
    temp_s4 = *(s32 *)(gEftBound + 0x218);
    Vu0Screen_StoreMtx((s32)sp20);
    func_00129C28((s32)sp60, gBtlCamView + 0x1F0);
    if (*(s16 *)(arg0 + 2) > 0) {
        var_s1 = (u8 *)arg0;
        do {
            sp80 = *(s64 *)(var_s1 + 0x630);
            sp88 = *(s64 *)(var_s1 + 0x638);
            lo_a = (s32)sp80;
            hi_a = (s32)(sp80 >> 32);
            lo_b = (s32)sp88;
            hi_b = (s32)(sp88 >> 32);
            Vec3_Sub((s32)sp70, temp_s0 + (hi_a << 6), (s32)sp60);
            Vec3_Normalize((s32)sp70, (s32)sp70);
            temp_a0 = var_s1 + 0x640;
            var_s1 += 0x20;
            if (func_00129CD8((s32)temp_a0, (s32)sp70) < 0.0f) {
                func_00144EE0((s32)sp20,
                              temp_s0 + (lo_a << 6),
                              temp_s0 + (hi_a << 6),
                              temp_s0 + (lo_b << 6),
                              temp_s0 + (lo_a << 6) + 0x20,
                              temp_s0 + (hi_a << 6) + 0x20,
                              temp_s0 + (lo_b << 6) + 0x20,
                              temp_s0 + (lo_a << 6) + 0x30,
                              temp_s0 + (hi_a << 6) + 0x30,
                              temp_s0 + (lo_b << 6) + 0x30,
                              *(s32 *)(temp_s4 + 0x38),
                              *(s64 *)temp_s5);
                func_00144EE0((s32)sp20,
                              temp_s0 + (lo_b << 6),
                              temp_s0 + (hi_a << 6),
                              temp_s0 + (hi_b << 6),
                              temp_s0 + (lo_b << 6) + 0x20,
                              temp_s0 + (hi_a << 6) + 0x20,
                              temp_s0 + (hi_b << 6) + 0x20,
                              temp_s0 + (lo_b << 6) + 0x30,
                              temp_s0 + (hi_a << 6) + 0x30,
                              temp_s0 + (hi_b << 6) + 0x30,
                              *(s32 *)(temp_s4 + 0x38),
                              *(s64 *)temp_s5);
            }
            var_s6 += 1;
        } while (var_s6 < *(s16 *)(arg0 + 2));
    }
}
