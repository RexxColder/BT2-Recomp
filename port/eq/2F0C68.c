#include "common.h"

s32 func_002E7AB8(s32 a0);
s32 func_002E7AC8(s32 a0);
s32 func_002E7B90(s32 a0);
void func_002E7F50(s32 a0, s32 a1, s32 a2, s32 a3);
s32 func_002E7F90(s32 a0);
s32 func_002E7F98(s32 a0);
s32 func_002F17A8(void *a0);
void func_003061A8(void *a0, s32 a1, void *a2, void *a3);

void func_002F0C68(void *arg0) {
    u8 *s0;
    s32 sp[4];
    s32 sp10[4];
    u8 *temp_s5;
    u8 *var_s1;
    u8 *var_s3;
    u8 *temp_a0;
    u8 *temp_a0_2;
    void *fn;
    s32 temp_s6;
    s32 temp_s3;
    s32 temp_fp;
    s32 var_s2;
    s32 var_s4;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_a1_2;
    s32 temp_a2;
    s32 temp_a3_2;
    s32 temp_a1;

    s0 = (u8 *)arg0;
    temp_s6 = *(s32 *)(s0 + 0x4);
    temp_s5 = *(u8 **)(s0 + 0x8);
    temp_s3 = func_002E7B90(temp_s6);
    temp_fp = func_002E7F90(temp_s6);
    var_s2 = func_002E7F98(temp_s6);
    temp_v0 = func_002E7AB8(temp_s6);
    if ((temp_v0 != 1) || (func_002F17A8(arg0) != temp_v0)) {
        temp_v0_2 = temp_s3 - *(s32 *)(s0 + 0x34);
        var_s2 = (var_s2 >= temp_v0_2) ? temp_v0_2 : var_s2;
    }
    var_s4 = 0;
    func_003061A8(s0 + 0x14, temp_fp, sp, sp10);

    fn = *(void **)(*(u8 **)temp_s5 + 0x20);
    var_s1 = s0 + 0xC;
    var_s3 = s0 + 0x1C;
    ((void (*)(void *, s32, void *, void *))fn)(temp_s5, 0, sp, fn);

    fn = *(void **)(*(u8 **)temp_s5 + 0x1C);
    ((void (*)(void *, s32, void *))fn)(temp_s5, 1, sp10);

    for (;;) {
        if (!(var_s4 < func_002E7AC8(temp_s6))) {
            break;
        }
        func_003061A8(var_s3, var_s2 * 2, sp, sp10);
        fn = *(void **)(s0 + 0x50);
        temp_a1 = var_s4;
        var_s4 += 1;
        if (fn != NULL) {
            ((void (*)(s32, s32, s32, s32))fn)(*(s32 *)(s0 + 0x54), temp_a1, sp[0], sp[1]);
        }
        temp_a0 = *(u8 **)var_s1;
        var_s3 += 8;
        fn = *(void **)(*(u8 **)temp_a0 + 0x20);
        ((void (*)(void *, s32, void *))fn)(temp_a0, 1, sp);
        temp_a0_2 = *(u8 **)var_s1;
        fn = *(void **)(*(u8 **)temp_a0_2 + 0x1C);
        var_s1 += 4;
        ((void (*)(void *, s32, void *))fn)(temp_a0_2, 0, sp10);
    }

    temp_a1_2 = *(s32 *)(s0 + 0x30) + temp_fp;
    temp_a3_2 = *(s32 *)(s0 + 0x34) + var_s2;
    temp_a2 = *(s32 *)(s0 + 0x40) + var_s2;
    *(s32 *)(s0 + 0x2C) = *(s32 *)(s0 + 0x2C) + var_s2;
    *(s32 *)(s0 + 0x30) = temp_a1_2;
    *(s32 *)(s0 + 0x44) = *(s32 *)(s0 + 0x44) + temp_fp;
    *(s32 *)(s0 + 0x34) = temp_a3_2;
    *(s32 *)(s0 + 0x40) = temp_a2;
    func_002E7F50(temp_s6, temp_a1_2, temp_a2, temp_a3_2);
}
