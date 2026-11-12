#include "common.h"

s32 func_0014EFA8(s32 a0, void *a1, void *a2, s32 a3, s32 t0, s32 t1, s32 t2, s32 t3);
s32 func_0014F2B8(void *a0, void *a1, s32 a2, s32 a3);
void func_001513D0(f32 farg0, s32 a0, void *a1, void *a2, void *a3, void *t0, void *t1, s32 t2, s32 t3,
                   s32 st0, s32 st8);
void func_00208DE8(s32 a0, void *a1, s32 a2);

void func_0014A6D0(s32 arg0, u8 *arg1, u8 **arg2, s32 arg3, s32 st4, s32 st5, s32 st6, s32 t3) {
    s32 sp14;
    s32 var_s1;
    s32 var_s6;
    s32 var_v0;
    s32 v1;
    s32 st8;
    s32 *temp_s7;
    u8 *temp_s0;
    u8 *temp_s3;
    u8 *temp_s4;
    u8 *var_s2;

    var_s6 = 0;
    temp_s0 = *(u8 **)(arg1 + 0x38);
    sp14 = 0;
    temp_s7 = *(s32 **)(temp_s0 + 0xB0);
    *(s32 *)(temp_s0 + 0x860) = *(s32 *)(temp_s0 + 0x860) | 0x80;
    func_00208DE8(*temp_s7, temp_s0 + 0x940, 0x1F);
    func_00208DE8(*temp_s7, temp_s0 + 0x960, 0x2D);
    do {
        temp_s4 = *arg2 + sp14;
        var_s1 = 0;
        if (*temp_s4 != 0) {
            temp_s3 = temp_s0 + 0xB4;
            var_s2 = temp_s4 + 0x11;
            do {
                if (arg3 & 0xFF) {
                    var_v0 = func_0014F2B8(arg2, temp_s3, var_s6, var_s1);
                } else {
                    var_v0 = func_0014EFA8(arg0, arg2, temp_s3, var_s6, var_s1, *(s32 *)temp_s0 & 1,
                                           *(s32 *)temp_s0 & 4, t3);
                }
                v1 = ((*(s32 *)temp_s0 & 0x100) ? 2 : var_v0);
                if (v1 != 0) {
                    st8 = (var_s2[0] == 4) ? (v1 | 0x80) : v1;
                    func_001513D0(*(f32 *)(temp_s0 + 0x18), (s32)temp_s7, arg2, temp_s3, temp_s0 + 0x860,
                                  temp_s0 + 0x80, temp_s0 + 0x30, var_s6, var_s1, var_s1, st8);
                }
                var_s1 += 1;
                var_s2 += 0x20;
            } while (var_s1 < (s32)*temp_s4);
        }
        var_s6 += 1;
        sp14 += 0x110;
    } while (var_s6 < 0x10);
}
