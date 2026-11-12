#include "common.h"

s32 func_002C2FF0(s32 arg0, s32 arg1);
s32 func_002C3210(s32 arg0);

s32 func_002D0898(u8 *arg0, u8 *arg1) {
    u8 *var_a0;
    u8 *var_a1;
    s64 t0;
    s64 t1;
    s64 t2;
    s64 t3;

    if (func_002C3210((s32)arg0) != 0) {
        return func_002C2FF0(0, 0xFF000119);
    }
    var_a1 = arg1;
    var_a0 = arg0 + 0x950;
    do {
        t0 = *(s64 *)(var_a0 + 0x00);
        t1 = *(s64 *)(var_a0 + 0x08);
        t2 = *(s64 *)(var_a0 + 0x10);
        t3 = *(s64 *)(var_a0 + 0x18);
        *(s64 *)(var_a1 + 0x00) = t0;
        *(s64 *)(var_a1 + 0x08) = t1;
        *(s64 *)(var_a1 + 0x10) = t2;
        *(s64 *)(var_a1 + 0x18) = t3;
        var_a0 += 0x20;
        var_a1 += 0x20;
    } while (var_a0 != arg0 + 0x9F0);
    *(s64 *)var_a1 = *(s64 *)var_a0;
    return 0;
}
