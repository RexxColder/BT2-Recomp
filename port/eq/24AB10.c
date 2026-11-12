#include "common.h"

void func_0026EC48(u8 *arg0, u8 *arg1, u8 *arg2);
void func_0026EFC8(u8 *arg0, u8 *arg1, s32 arg2);
void func_0026EEC8(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3);

/* 0x0024AB10 (Num_DrawDigits, BT3 C as guide): for each digit until 0xFF: digit 10 -> hide (prop 8), else
 * Flash clip UV = cells + 20*digit and show (prop 4); then set the offset (arg2, arg3). Refs step 8 bytes. */
void Num_DrawDigits(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3, u8 *arg4, u8 *arg5) {
    u8 *r;
    u8 *d;

    r = arg1;
    d = arg5;
    while (*d != 0xFF) {
        if (*d != 10) {
            func_0026EC48(arg0, r, arg4 + 20 * (*d));
            func_0026EFC8(arg0, r, 4);
        } else {
            func_0026EFC8(arg0, r, 8);
        }
        func_0026EEC8(arg0, r, arg2, arg3);
        r += 8;
        d++;
    }
}
