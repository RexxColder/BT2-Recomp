#include "common.h"

void func_00129C28(void *a0, void *a1);
s32 func_0014EFA8(s32 a0, void *a1, void *a2, s32 a3, s32 t0, s32 t1, s32 t2);
void func_001513D0(f32 f12, s32 a0, void *a1, void *a2, void *a3, void *t0, void *t1,
                   s32 t2, s32 t3, s32 st0, s32 st1);
void func_00208DE8(s32 a0, void *a1, s32 a2);

void func_00152AF0(s32 arg0, void *arg1, s32 *arg2) {
    s32 sp10[4];
    s32 sp20[4];
    s32 sp30;
    s32 sp34;
    s32 sp38;
    s32 sp3C;
    u8 *temp_s1;
    u8 *temp_s4;
    u8 *var_s0;
    s32 var_fp;
    s32 var_s2;
    s32 var_s6;
    s32 s3;
    s32 t2;
    s32 flags;
    s32 temp_v1_2;
    void *s5;
    f32 var_f12;

    var_fp = 0;
    temp_s1 = *(u8 **)((u8 *)arg1 + 0x38);
    sp30 = arg0;
    sp34 = *(s32 *)(temp_s1 + 0xB0);
    func_00129C28(sp20, temp_s1 + 0x80);
    flags = *(s32 *)temp_s1;
    sp38 = 0;
    s3 = flags & 1;
    if (flags & 0x200) {
        if (flags & 0x800) {
            var_fp = 1;
            func_00208DE8(*(s32 *)(temp_s1 + 0x8), sp10, 3);
            func_00129C28(sp20, sp10);
            s3 = *(s32 *)temp_s1 & 0x100;
            sp38 = s3;
        } else {
            *(s32 *)temp_s1 = flags | 0x800;
        }
    }

    sp3C = 0;
    var_s6 = 0;
    do {
        temp_s4 = (u8 *)(*arg2 + sp3C);
        var_s2 = 0;
        if (*temp_s4 != 0) {
            s5 = temp_s1 + 0xB4;
            var_s0 = temp_s4 + 0x10;
            do {
                t2 = *(s32 *)temp_s1 & 4;
                if (var_fp != 0) {
                    s3 = sp38;
                    if ((*(u8 *)(var_s0 + 2) == 0) && (*(f32 *)(var_s0 + 8) > 0.0f)) {
                        s3 = 0;
                        t2 = 0;
                    }
                }
                temp_v1_2 = func_0014EFA8(sp30, arg2, s5, var_s6, var_s2, s3, t2);
                var_f12 = *(f32 *)(temp_s1 + 0x1C);
                if ((var_fp != 0) && (*(u8 *)var_s0 == 2)) {
                    var_f12 = *(f32 *)(temp_s1 + 0x20);
                }
                if (temp_v1_2 != 0) {
                    func_001513D0(var_f12, sp34, arg2, s5, temp_s1 + 0x860, sp20, temp_s1 + 0x30,
                                  var_s6, var_s2, var_s2, temp_v1_2);
                }
                var_s2 += 1;
                var_s0 += 0x20;
            } while (var_s2 < *temp_s4);
        }
        var_s6 += 1;
        sp3C += 0x110;
    } while (var_s6 < 0x10);
}
