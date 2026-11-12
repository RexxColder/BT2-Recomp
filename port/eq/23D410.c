#include "common.h"

s32 func_00240FC8(s32 arg0, s32 arg1);

s32 func_0023D410(s32 arg0, s32 arg1, s32 arg2) {
    s32 s0 = arg2 & 0xFF;
    s32 v;
    s32 a0 = -1;

    v = func_00240FC8(arg0, arg1);
    if ((u32)v < 10) {
        switch (v) {
        case 0:
            a0 = arg1 + 0xAA;
            break;
        case 1:
            if (s0 == 0) {
                a0 = arg1 + 0xB0;
            }
            break;
        case 2:
        case 8:
            if (s0 == 0) {
                a0 = arg1 + 0xAA;
            }
            break;
        case 3:
            a0 = arg1 + 0xAD;
            break;
        case 4:
            if (s0 == 0) {
                a0 = arg1 + 0xB3;
            }
            break;
        case 5:
            if (s0 == 0) {
                a0 = arg1 + 0xB6;
            }
            break;
        case 6:
            if (s0 == 0) {
                a0 = arg1 + 0xB9;
            }
            break;
        case 7:
            if (s0 == 0) {
                a0 = arg1 + 0xBC;
            }
            break;
        case 9:
            if (s0 == 0) {
                a0 = arg1 + 0xC8;
            }
            break;
        default:
            break;
        }
    }
    return a0;
}
