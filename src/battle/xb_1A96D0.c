#include "m2c_macros.h"

M2C_UNK FlashShapePool_Term(s32);                   /* extern */
s32 func_00126560(s32);                             /* extern */
extern void *D_00387840;

// Frees two FlashShape pool slots (table at obj->0x38 + 0x4C, 4-byte entries) and clears two fields of the globals block (guess)
void func_001A96D0(void *arg0) {
    s32 *temp_s2;
    s32 var_a0;
    s32 var_s0;
    s32 var_s1;

    var_s1 = 1;
    temp_s2 = M2C_FIELD(arg0, s32 **, 0x38);
    var_s0 = (s32)temp_s2 + 0x4C;
    var_a0 = var_s0;
    do {
        var_s0 += 4;
        var_s1 -= 1;
        FlashShapePool_Term(var_a0);
        var_a0 = var_s0;
    } while (var_s1 >= 0);
    if (func_00126560(var_a0) == 0) {
        M2C_FIELD((D_00387840 + *temp_s2), s8 *, 4) = 0;
    }
    M2C_FIELD(D_00387840, s16 *, 0x1090) = 0;
}
