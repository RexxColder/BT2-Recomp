#include "common.h"

s32 func_0025DF98(s32 arg0, s32 arg1, s32 arg2, s32 *arg3);
s32 func_0025E0B8(s32 arg0, s32 arg1, void *arg2, s32 arg3);
extern u8 *D_00387A40;
extern u8 D_00388A48[] __attribute__((section(".data")));
extern s32 D_00388D4C __attribute__((section(".data")));

void func_00262330(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_a3;
    s32 temp_t0;
    s32 temp_v1;

    temp_a3 = arg0 & 0xFFFF;
    temp_t0 = arg1 & 0xFFFF;
    temp_v1 = arg2 & 0xFFFF;
    if (temp_a3 == 0) {
        /* a3 = %hi(D_00388D4C) only (lui without addiu): the callee gets 0x00390000 */
        func_0025DF98(temp_t0, *(s32 *)(D_00387A40 + 0) + (temp_t0 * 0x18580), D_00388D4C + (temp_v1 * 0x30), (s32 *)0x00390000);
        return;
    }
    if (temp_a3 == 1) {
        func_0025E0B8(temp_t0, *(s32 *)(D_00387A40 + 8) + (temp_t0 * 0x1520), D_00388A48 + (temp_v1 * 0x30), temp_a3);
        return;
    }
}
