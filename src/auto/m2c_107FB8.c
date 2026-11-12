#include "m2c_macros.h"

extern void *gObjOutline;

void BtlMenu_Reset(void *arg0) {
    s32 temp_a0;
    s32 var_s1;
    void *temp_v1;

    if (arg0 != NULL) {
        M2C_FIELD(arg0, s32 *, 0x14) = -1;
        var_s1 = 0;
        M2C_FIELD(arg0, s32 *, 0x18) = 0;
        M2C_FIELD(arg0, s32 *, 0x1C) = 0;
        if (M2C_FIELD(arg0, s32 *, 4) > 0) {
            do {
                temp_a0 = var_s1 << 5;
                var_s1 += 1;
                M2C_FIELD((temp_a0 + M2C_FIELD(arg0, s32 *, 0)), s8 *, 0x1A) = 0;
                M2C_FIELD((temp_a0 + M2C_FIELD(arg0, s32 *, 0)), s8 *, 0x18) = 0;
                M2C_FIELD((temp_a0 + M2C_FIELD(arg0, s32 *, 0)), s8 *, 0x1D) = 0;
                temp_v1 = M2C_FIELD((temp_a0 + M2C_FIELD(arg0, s32 *, 0)), void **, 8);
                if (temp_v1 != NULL) {
                    BtlMenu_Reset(temp_v1);
                }
            } while (var_s1 < M2C_FIELD(arg0, s32 *, 4));
        }
        M2C_FIELD(gObjOutline, s8 *, 4) = 0;
    }
}
