#include "common.h"

u8 *BtlMember_GetActiveGauge(s32 arg0);
s32 BtlMember_HasBlast(s32 arg0, s32 arg1);
s32 func_00208738(s32 arg0, s32 arg1);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 func_00241C50(s32 arg0, s32 arg1);
s32 func_00241C70(s32 arg0, s32 arg1);
s32 func_00241F80(s32 arg0, s32 arg1);

s32 func_0023D740(s32 arg0, s32 arg1) {
    u8 *p = (u8 *)arg0;
    s32 temp_v0;
    s32 var_v0;

    var_v0 = func_00208738(*(s32 *)(p + 0x1534), arg1);
    if (var_v0 != 0) {
        var_v0 = 0;
        if (*(u8 *)(BtlMember_GetActiveGauge(arg0) + 0x2C) == 0) {
            var_v0 = BtlMember_HasBlast(arg0, func_00241C70(arg0, arg1));
            if (var_v0 != 0) {
                if (func_00211310(arg0, 0, 1) == 0) {
                    var_v0 = 0;
                    if (!(func_00241F80(arg0, arg1) & 1)) {
                        goto block_6;
                    }
                    goto block_24;
                }
block_6:
                if (!(func_00241F80(arg0, arg1) & 0x10) ||
                    (var_v0 = 0, (*(s32 *)(BtlMember_GetActiveGauge(arg0) + arg1 * 4 + 0x30) <= 0))) {
                    temp_v0 = func_00241C50(arg0, arg1);
                    if (temp_v0 != 0xC0) {
                        if (temp_v0 < 0xC1) {
                            if ((temp_v0 != 0xA) && (var_v0 = 1, (temp_v0 != 0xBF))) {
                                /* returns 1 */
                            } else if (*(s32 *)(p + 0xAC8) > 0) {
                                var_v0 = 0;
                            } else {
                                goto block_23;
                            }
                            goto block_24;
                        }
                        if (temp_v0 != 0xC4) {
                            var_v0 = 1;
                            if (temp_v0 == 0xD2) {
                                if (*(f32 *)(p + 0xAC4) >= 3.0f) {
                                    return 0;
                                }
                                return var_v0;
                            }
                            goto block_24;
                        }
                        var_v0 = 0;
                        if (*(s32 *)(p + 0xACC) <= 0) {
                            goto block_23;
                        }
                        goto block_24;
                    }
                    if (*(s32 *)(p + 0xAC8) >= 3) {
                        var_v0 = 0;
                    } else {
block_23:
                        var_v0 = 1;
                    }
                    goto block_24;
                }
                goto block_24;
            }
        }
    }
block_24:
    return var_v0;
}
