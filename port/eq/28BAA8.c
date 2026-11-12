#include "common.h"

u8 *func_00324448(s32 arg0, s32 arg1);
extern s32 D_00387D4C;
extern u8 *D_00387D50;
extern u8 *D_00387D54;

u8 *func_0028BAA8(s32 arg0) {
    s32 var_s0;
    u8 *var_v0;

    var_s0 = arg0;
    if (var_s0 & 0x3F) {
        if (var_s0 < 0) {
            var_s0 += 0x3F;
        }
        var_s0 = ((var_s0 >> 6) << 6) + 0x40;
    }
    var_v0 = func_00324448(0x40, var_s0 + 0x40);
    if (var_v0 != NULL) {
        var_s0 += 0x80;
        D_00387D4C += var_s0;
        if (D_00387D54 != NULL) {
            *(u8 **)(D_00387D54 + 0xC) = var_v0;
            *(s32 *)(var_v0 + 0) = var_s0;
            *(s32 *)(var_v0 + 0xC) = 0;
            *(u8 **)(var_v0 + 8) = D_00387D54;
            D_00387D54 = var_v0;
        } else {
            *(s32 *)(var_v0 + 0) = var_s0;
            *(u8 **)(var_v0 + 8) = NULL;
            *(s32 *)(var_v0 + 0xC) = 0;
            D_00387D54 = var_v0;
            D_00387D50 = var_v0;
        }
        *(u8 **)(D_00387D54 + 4) = var_v0 + 0x40;
        var_v0 = *(u8 **)(D_00387D54 + 4);
    }
    return var_v0;
}
