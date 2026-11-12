#include "common.h"

void EftPtcl3_SetPos(s32 arg0, void *arg1);
void EftPtcl3_SetDir(s32 arg0, void *arg1);
void func_00129BD0(void *arg0, void *arg1, f32 farg0);
void func_00129C38(void *arg0, void *arg1);

void func_001C9108(void *arg0) {
    s32 sp[4];
    u8 *temp_s5;
    s32 temp_s0;
    u8 *var_s0;
    u8 *var_s1;
    u8 *var_s2;
    u8 *var_s4;
    void *temp_s6;
    void *temp_a1;
    s32 var_s3;
    s32 var_s7;
    s32 temp_a0;

    var_s7 = 0;
    temp_s5 = *(u8 **)((u8 *)arg0 + 0x38);
    temp_s0 = *(s32 *)temp_s5;
    temp_s6 = temp_s5 + 0x80;
    var_s4 = temp_s5;
    func_00129C38(sp, temp_s6);
    var_s2 = (u8 *)temp_s0 + 0x1B;
    do {
        var_s1 = temp_s5 + 0x60;
        var_s0 = var_s4 + 0x10;
        var_s3 = 1;
loop_2:
        temp_a1 = var_s1;
        var_s1 += 0x10;
        EftPtcl3_SetPos(*(s32 *)var_s0, temp_a1);
        if (*var_s2 == 0) {
            func_00129BD0(sp, temp_s6, -1.0f);
        }
        temp_a0 = *(s32 *)var_s0;
        var_s0 += 0xC;
        var_s3 -= 1;
        EftPtcl3_SetDir(temp_a0, sp);
        if (var_s3 >= 0) {
            goto loop_2;
        }
        var_s7 += 1;
        var_s2 += 1;
        var_s4 += 4;
    } while (var_s7 < 3);
}
