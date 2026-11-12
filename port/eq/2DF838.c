#include "common.h"

s32 func_002DCE50(u8 *arg0);
s32 func_002DFA00(u8 *arg0, u8 *arg1, s32 arg2);
void *memcpy(void *arg0, void *arg1, s32 arg2);

typedef void (*VtFn4)(void *obj, s32 a1, s32 a2, void *a3);
typedef void (*VtFn3)(void *obj, s32 a1, void *a2);
typedef void (*VtFn2)(s32 a0, s32 a1);

s32 func_002DF838(u8 *arg0, u8 *arg1, s32 arg2) {
    u8 fr[0x18];
    s32 var_s2;
    s32 var_fp;
    s32 var_s7;
    s32 temp_s0;
    s32 temp_s6;
    s32 temp_s4;
    s32 v1;
    s32 temp_a2;
    s32 temp_a2_2;
    u8 *temp_s1;
    u8 *temp_a0;
    VtFn2 fn;

    var_s2 = 4;
    var_fp = 0;
    temp_s6 = *(s32 *)(arg0 + 0x3B8);
    temp_s0 = arg2 - 3;

    for (;;) {
        if (var_s2 < temp_s0) {
            if (func_002DCE50(arg1 + var_s2) == 0) {
                var_s2 += 1;
                continue;
            }
        }
        break;
    }

    v1 = var_s2 ^ temp_s0;
    var_s7 = (v1 != 0) ? 0 : -1;
    if (temp_s6 == 1) {
        var_fp = func_002DFA00(arg0, arg1, var_s2);
    }

    temp_s4 = (temp_s6 * 12) + 0x3B0;
    temp_s1 = *(u8 **)(arg0 + temp_s4 + 0xC);
    if (temp_s1 != NULL) {
        ((VtFn4)(*(void **)(*(u8 **)temp_s1 + 0x18)))(temp_s1, 0, var_s2, fr);
        memcpy(*(void **)(fr + 0), arg1, *(s32 *)(fr + 4));
        ((VtFn3)(*(void **)(*(u8 **)temp_s1 + 0x20)))(temp_s1, 1, fr);
        if (*(s32 *)(fr + 4) < var_s2) {
            ((VtFn4)(*(void **)(*(u8 **)temp_s1 + 0x18)))(temp_s1, 0, var_s2 - *(s32 *)(fr + 4), fr + 0x10);
            memcpy(*(void **)(fr + 0x10), arg1 + *(s32 *)(fr + 4), *(s32 *)(fr + 0x14));
            ((VtFn3)(*(void **)(*(u8 **)temp_s1 + 0x20)))(temp_s1, 1, fr + 0x10);
        }
        fn = *(VtFn2 *)(arg0 + temp_s4 + 0x10);
        if (fn != NULL) {
            fn(*(s32 *)(arg0 + temp_s4 + 0x14), temp_s6);
        }
    }

    if (temp_s6 == 3) {
        temp_a0 = *(u8 **)(arg0 + 0x3EC);
        if (temp_a0 != NULL) {
            temp_a2 = *(s32 *)(arg0 + 0x3F0);
            temp_a2_2 = (var_s2 < temp_a2) ? var_s2 : temp_a2;
            *(s32 *)(arg0 + 0x3F4) = temp_a2_2;
            memcpy(temp_a0, arg1, temp_a2_2);
        }
    }
    return (var_fp == 0) ? var_s7 : var_fp;
}
