#include "common.h"

s32 func_0011FD98(u8 *arg0);
s32 func_0011FFD0(u8 *arg0, s32 arg1, s32 arg2);

s32 func_00120CC8(u8 *arg0) {
    u8 *var_s3;
    u8 *a3;
    u8 *s1;
    u8 *base;
    u8 temp_v1;
    s32 temp_v0;
    s32 var_s2;
    s32 var_s5;
    s32 var_s6;
    s32 var_s0;
    s32 idx;
    s32 eq0;
    s32 c;

    var_s2 = 0;
    var_s3 = NULL;
    if ((*(u8 **)(arg0 + 0x11D0) == NULL) || (*(s32 *)(arg0 + 0x11D4) == 0)) {
        return -1;
    }
    temp_v0 = func_0011FD98(arg0);
    if (temp_v0 == 0) {
        return -1;
    }
    var_s6 = *(s32 *)(*(u8 **)(arg0 + 0x11D0));
    var_s5 = 0;
    if (var_s6 <= 0) {
        return -1;
    }

L_D40:
    a3 = var_s3;
    base = *(u8 **)(arg0 + 0x11D4);
    var_s3 = base + (var_s5 << 5);
    temp_v1 = var_s3[0x18];
    if (!(temp_v0 & ((u32)1 << (temp_v1 & 31)))) {
        var_s5 += 1;
        goto L_E58;
    }
    if (a3 == NULL) {
        goto L_E0C;
    }
    if (temp_v1 != a3[0x18]) {
        var_s2 = 0;
        goto L_E0C;
    }
    if ((var_s3[var_s2 * 2] == a3[var_s2 * 2]) && (var_s3[var_s2 * 2 + 1] == a3[var_s2 * 2 + 1])) {
        var_s5 += 1;
        goto L_E58;
    }

L_DAC:
    if (var_s2 <= 0) {
        goto L_E0C;
    }
    var_s0 = var_s2 - 1;
    for (;;) {
        idx = var_s0 * 2;
        eq0 = (var_s3[idx] == a3[idx]);
        var_s0 -= 1;
        if (eq0 && (var_s3[idx + 1] == a3[idx + 1])) {
            goto L_E0C;
        }
        var_s2 -= 1;
        if (var_s0 < 0) {
            goto L_E0C;
        }
    }

L_E0C:
    var_s0 = var_s2;
    s1 = var_s3 + (var_s2 * 2);
    for (;;) {
        if (!(var_s0 < 8)) {
            break;
        }
        var_s0 += 1;
        c = func_0011FFD0(arg0, s1[0], s1[1]);
        s1 += 2;
        if (c == 0) {
            break;
        }
        var_s2 += 1;
    }
    if (var_s2 == 8) {
        return var_s5;
    }
    var_s5 += 1;

L_E58:
    if (var_s5 < var_s6) {
        goto L_D40;
    }
    return -1;
}
