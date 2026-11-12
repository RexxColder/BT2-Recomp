#include "common.h"

s32 func_0014EFA8(s32 a0, void *a1, void *a2, s32 a3, s32 t0, s32 t1, s32 t2, s32 t3);
s32 func_0014F2B8(void *a0, void *a1, s32 a2, s32 a3);
void func_001513D0(f32 farg0, s32 a0, void *a1, void *a2, void *a3, void *t0, void *t1, s32 t2, s32 t3,
                   s32 st0, s32 st8);

void func_0016F118(s32 arg0, void *arg1, u8 **arg2, s32 arg3, s32 st4, s32 st5, s32 st6, s32 t3) {
    s32 sp14;
    s32 sp18;
    s32 var_1c = 0;
    s32 var_s3;
    s32 var_s6 = 0;
    s32 var_v0;
    s32 v1;
    u8 type;
    s32 do_it;
    u8 *temp_s1;
    u8 *temp_s4;
    u8 *temp_s7;
    u8 *var_s2;

    temp_s1 = *(u8 **)((u8 *)arg1 + 0x38);
    sp14 = arg3 & 0xFF;
    sp18 = *(s32 *)(temp_s1 + 0xB0);
    do {
        temp_s4 = *arg2 + var_1c;
        var_s3 = 0;
        if (*temp_s4 != 0) {
            temp_s7 = temp_s1 + 0xB4;
            var_s2 = temp_s4 + 0x10;
            do {
                type = var_s2[1];
                do_it = 0;
                if (type != 1) {
                    if (type == 2) {
                        do_it = ((u32)((var_s2[0] + 0xFF) & 0xFF) >= 2U);
                    } else {
                        do_it = 1;
                    }
                }
                if (do_it) {
                    if (sp14 == 0) {
                        var_v0 = func_0014EFA8(arg0, arg2, temp_s7, var_s6, var_s3, *(s32 *)temp_s1 & 1,
                                               *(s32 *)temp_s1 & 4, t3);
                    } else {
                        var_v0 = func_0014F2B8(arg2, temp_s7, var_s6, var_s3);
                    }
                    v1 = ((*(s32 *)temp_s1 & 0x100) ? 2 : var_v0);
                    if (v1 != 0) {
                        func_001513D0(*(f32 *)(temp_s1 + 0x1C), sp18, arg2, temp_s7, temp_s1 + 0x860,
                                      temp_s1 + 0x80, temp_s1 + 0x30, var_s6, var_s3, var_s3, v1);
                    }
                }
                var_s3 += 1;
                var_s2 += 0x20;
            } while (var_s3 < (s32)*temp_s4);
        }
        var_s6 += 1;
        var_1c += 0x110;
    } while (var_s6 < 0x10);
}
