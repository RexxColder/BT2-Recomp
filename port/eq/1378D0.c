#include "common.h"

void func_00129A50(void *a0, void *a1, s32 a2, s32 a3);
s32 func_00126588();
s32 func_00126698();
void EftSurf_PutTri(void *a0, void *a1, void *a2, void *a3, void *t0, void *t1, void *t2, void *t3, void *st0, s64 st1);

void EftSurf_DrawTri(s32 arg0, s64 arg1) {
    s32 fr[0x70 / 4];
    u8 *fb;
    s32 var_s1;
    s32 var_s3;
    s32 var_s0;
    s32 var_s1_2;
    s32 var_s0_2;
    s32 var_s1_3;
    s32 var_a0;
    s32 var_a0_2;
    s32 var_a0_3;
    s32 need_put;
    s32 temp_v1;
    s32 temp_v1_2;

    fb = (u8 *)fr;
    var_s1 = 0x910;
    var_s3 = 0x6F0;
    func_00129A50(fb + 0x10, fb + 0x40, arg0, 3);
    if (func_00126698() == 0) {
        if (func_00126588() != 0) {
            var_s3 = 0x7F0;
        } else {
            var_s1 = 0x810;
        }
    }
    need_put = 0;
    var_a0 = 1;
    if (*(s32 *)(fb + 0x18) > 0) {
        temp_v1 = *(s32 *)(fb + 0x10);
        if ((temp_v1 < (var_s1 * 0x10)) && ((var_s3 * 0x10) < temp_v1)) {
            temp_v1_2 = *(s32 *)(fb + 0x14);
            var_a0 = (temp_v1_2 < 0x8F00) ? (temp_v1_2 < 0x7101) : 1;
        }
    }
    var_s1_2 = 0x6F0;
    if (var_a0 == 0) {
        need_put = 1;
    } else {
        var_s0 = 0x910;
        if (func_00126698(var_a0) == 0) {
            if (func_00126588() != 0) {
                var_s1_2 = 0x7F0;
            } else {
                var_s0 = 0x810;
            }
        }
        var_a0_2 = 1;
        if ((*(s32 *)(fb + 0x28) > 0) && (*(s32 *)(fb + 0x20) < (var_s0 * 0x10)) && ((var_s1_2 * 0x10) < *(s32 *)(fb + 0x20))) {
            var_a0_2 = (*(s32 *)(fb + 0x24) < 0x8F00) ? (*(s32 *)(fb + 0x24) < 0x7101) : 1;
        }
        if (var_a0_2 == 0) {
            need_put = 1;
        } else {
            var_s1_3 = 0x6F0;
            var_s0_2 = 0x910;
            if (func_00126698(var_a0_2) == 0) {
                if (func_00126588() != 0) {
                    var_s1_3 = 0x7F0;
                } else {
                    var_s0_2 = 0x810;
                }
            }
            var_a0_3 = 1;
            if ((*(s32 *)(fb + 0x38) > 0) && (*(s32 *)(fb + 0x30) < (var_s0_2 * 0x10)) && ((var_s1_3 * 0x10) < *(s32 *)(fb + 0x30))) {
                var_a0_3 = (*(s32 *)(fb + 0x34) < 0x8F00) ? (*(s32 *)(fb + 0x34) < 0x7101) : 1;
            }
            if (var_a0_3 == 0) {
                need_put = 1;
            }
        }
    }
    if (need_put) {
        EftSurf_PutTri(fb + 0x10, fb + 0x20, fb + 0x30, fb + 0x40,
                       fb + 0x50, fb + 0x60, (void *)(arg0 + 0x20), (void *)(arg0 + 0x50),
                       (void *)(arg0 + 0x80), arg1);
    }
}
