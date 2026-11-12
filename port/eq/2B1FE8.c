#include "common.h"

f32 Mathf_Asin(f32 farg0);
f32 atan2f(f32 farg0, f32 farg1);
u8 *func_002B1DD0(s32 arg0);
void func_00312650(void *arg0, void *arg1, void *arg2);
void sceVu0Normalize(f32 *arg0, f32 *arg1);
extern f32 D_00387658;
extern u8 *D_00387E18;

void func_002B1FE8(u8 *arg0) {
    f32 sp[4];
    f32 temp_f0;
    s32 var_s0;
    u8 *var_s2;

    var_s0 = 0;
    var_s2 = NULL;
    while (var_s0 < *(s32 *)(D_00387E18 + 4)) {
        if (*(s32 *)(func_002B1DD0(var_s0) + 0x10) != 3) {
            var_s0 += 1;
            continue;
        }
        var_s2 = func_002B1DD0(var_s0);
        break;
    }
    if (var_s2 != NULL) {
        func_00312650(sp, var_s2 + 0xD0, arg0 + 0xD0);
        sceVu0Normalize(sp, sp);
        *(f32 *)(arg0 + 0x70) = atan2f(sp[0], sp[2]);
        temp_f0 = Mathf_Asin(sp[1]) + D_00387658;
        *(f32 *)(arg0 + 0x15C) = *(f32 *)(arg0 + 0x70);
        *(f32 *)(arg0 + 0x74) = temp_f0;
    }
}
