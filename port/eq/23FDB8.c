#include "common.h"

s32 BtlObjXf_Update(s32 arg0);
extern f32 D_00386CB0;
extern f32 D_00386CB4;

s32 func_0023FDB8(s32 arg0) {
    u8 *p = (u8 *)arg0;
    f32 temp_f0;
    f32 temp_f0_2;
    s32 temp_v0;
    s32 var_v0;

    temp_v0 = BtlObjXf_Update(arg0);
    if (temp_v0 == 0x92) {
        goto block_38;
    }
    if (temp_v0 < 0x93) {
        var_v0 = 8;
        if (temp_v0 != 0x86) {
            if (temp_v0 < 0x87) {
                var_v0 = -1;
                if (temp_v0 >= 0x7D) {
                    var_v0 = 0;
                    if (temp_v0 >= 0x7F) {
                        if (temp_v0 < 0x83) {
                            return -1;
                        }
                        return 4;
                    }
                }
                return var_v0;
            }
            if (temp_v0 != 0x89) {
                var_v0 = 1;
                if (temp_v0 >= 0x89) {
                    if (temp_v0 < 0x90) {
                        return -1;
                    }
                    return 5;
                }
                return var_v0;
            }
            temp_f0 = *(f32 *)(p + 0xA1C);
            var_v0 = 1;
            if (!(temp_f0 < D_00386CB0)) {
                var_v0 = 3;
                if (temp_f0 < D_00386CB4) {
                    return 2;
                }
            }
            return var_v0;
        }
        return var_v0;
    }
    if (temp_v0 == 0x98) {
        goto block_38;
    }
    if (temp_v0 < 0x99) {
        if (temp_v0 == 0x95) {
block_38:
            var_v0 = 5;
            if (!(*(f32 *)(p + 0xA1C) < D_00386CB0)) {
                var_v0 = 7;
                if (*(f32 *)(p + 0xA1C) < D_00386CB4) {
                    return 6;
                }
            }
            return var_v0;
        }
        return 5;
    }
    if (temp_v0 != 0x9B) {
        var_v0 = 9;
        if (temp_v0 >= 0x9B) {
            var_v0 = 0xC;
            if (temp_v0 != 0x1AC) {
                var_v0 = 0xD;
                if (temp_v0 != 0x1AD) {
                    return -1;
                }
            }
        }
        return var_v0;
    }
    temp_f0_2 = *(f32 *)(p + 0xA1C);
    var_v0 = 9;
    if (!(temp_f0_2 < D_00386CB0)) {
        var_v0 = 0xB;
        if (temp_f0_2 < D_00386CB4) {
            var_v0 = 0xA;
        }
    }
    return var_v0;
}
