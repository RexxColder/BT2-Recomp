#include "common.h"

s32 func_0024B210();
extern u8 *D_003879A0;

void func_0024CC48(void) {
    u8 *g;
    s32 var_t1;
    s32 temp_a1;
    u8 *temp_a0;
    u8 *temp_a3;
    s32 temp_v0;
    s32 temp_v1;
    s32 r1;
    s32 r2;
    s32 v;

    g = D_003879A0;
    var_t1 = 0;
    do {
        temp_a1 = var_t1 * 4;
        var_t1 += 1;
        temp_a3 = g + temp_a1;
        temp_a0 = g + 0xC + temp_a1;
        temp_v1 = *(s32 *)(temp_a0 + 0x3260);
        temp_v0 = *(s32 *)(temp_a0 + 0x3280);
        if (temp_v1 < temp_v0) {
            *(s32 *)(temp_a3 + 0x3240) = 3;
        } else if (temp_v0 < temp_v1) {
            *(s32 *)(temp_a3 + 0x3240) = 2;
        } else {
            *(s32 *)(temp_a3 + 0x3240) = 1;
        }
    } while (var_t1 < 8);

    r1 = func_0024B210(g + 0x326C, temp_a1, g, temp_a3);
    r2 = func_0024B210(g + 0x328C);
    if (r1 < r2) {
        v = 3;
    } else if (r2 < r1) {
        v = 2;
    } else {
        v = 1;
    }
    *(s32 *)(g + 0x3268) = v;
    *(s32 *)(g + 0x323C) = r2;
}
