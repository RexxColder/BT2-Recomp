#include "m2c_macros.h"

M2C_UNK func_00182BB0(s32);                         /* extern */
M2C_UNK func_00182B60(s32, s32);                    /* extern */

// Clears the table at obj->0x38 + 0xAA4 (count at +0xAA0, 4-byte entries), calling func_00182BB0 on each non-null entry.
void func_0015C980(void *arg0) {
    s32 *var_s0;
    s32 temp_v0;
    s32 var_s2;
    void *temp_s1;

    temp_s1 = M2C_FIELD(arg0, void **, 0x38);
    var_s2 = 0;
    if (M2C_FIELD(temp_s1, s32 *, 0xAA0) > 0) {
        var_s0 = (s32 *)((char *)temp_s1 + 0xAA4);
        do {
            temp_v0 = *var_s0;
            if (temp_v0 != 0) {
                func_00182BB0(temp_v0);
                *var_s0 = 0;
            }
            var_s2 += 1;
            var_s0 += 1;
        } while (var_s2 < M2C_FIELD(temp_s1, s32 *, 0xAA0));
    }
}

// Same table walk as func_0015C980 but calls func_00182B60(entry, 5*i) on each non-null entry (no clearing).
void func_0015C9F0(void *arg0) {
    s32 *var_s0;
    s32 temp_a0;
    s32 var_s2;
    s32 var_s3;
    void *temp_s1;

    temp_s1 = M2C_FIELD(arg0, void **, 0x38);
    var_s3 = 0;
    if (M2C_FIELD(temp_s1, s32 *, 0xAA0) > 0) {
        var_s2 = 0;
        var_s0 = (s32 *)((char *)temp_s1 + 0xAA4);
        do {
            temp_a0 = *var_s0;
            var_s0 += 1;
            if (temp_a0 != 0) {
                func_00182B60(temp_a0, var_s2);
            }
            var_s3 += 1;
            var_s2 += 5;
        } while (var_s3 < M2C_FIELD(temp_s1, s32 *, 0xAA0));
    }
}
