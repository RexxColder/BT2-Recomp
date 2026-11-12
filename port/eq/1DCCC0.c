#include "common.h"

void EftPtcl3_SetDir(s32 arg0, s32 *arg1);
void EftPtcl3_SetPos(s32 arg0, u8 *arg1);
void func_00129BD0(void *arg1, void *arg2, f32 farg0);
void func_00129C38(void *arg0, void *arg1);

void func_001DCCC0(u8 *arg0) {
    s32 sp[4];
    u8 *var_fp;
    u8 *var_s0;
    u8 *var_s1;
    u8 *var_s2;
    u8 *var_s4;
    u8 *var_s5;
    u8 *var_s7;
    s32 var_s3;
    s32 var_s6;

    var_s6 = 0;
    var_s4 = *(u8 **)(arg0 + 0x38);
    var_s5 = var_s4;
    var_fp = *(u8 **)var_s4 + 9;
    do {
        var_s3 = 0;
        var_s7 = var_fp + var_s6;
        var_s2 = var_s4;
        var_s1 = var_s5 + 0x10;
        do {
            if (*(s32 *)(var_s4 + 0x240) != var_s3) {
                var_s0 = var_s2 + 0x140;
                EftPtcl3_SetPos(*(s32 *)var_s1, var_s2 + 0x50);
                func_00129C38(sp, var_s0);
                if (*var_s7 == 0) {
                    func_00129BD0(sp, var_s0, -1.0f);
                }
                EftPtcl3_SetDir(*(s32 *)var_s1, sp);
            }
            var_s3 += 1;
            var_s2 += 0x10;
            var_s1 += 4;
        } while (var_s3 < 9);
        var_s6 += 1;
        var_s5 += 4;
    } while (var_s6 <= 0);
}
