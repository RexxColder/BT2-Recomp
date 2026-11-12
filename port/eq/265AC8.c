#include "common.h"

/* 0x00265AC8: replaces the bit field 0xFF0000 of the word at arg0+0xAF0 with one bit chosen by arg1:
 * 0 -> 0x40000, 1 -> 0x80000, 2 -> 0x100000, 3 -> 0x200000, 4 -> 0x10000, 5 -> 0x20000, 6 -> 0x400000.
 * Any other arg1: 0x20000 when bit 0x1000000 of the word at *(arg0+0x44) is set, else 0x10000. */
void func_00265AC8(u8 *arg0, s32 arg1) {
    u32 c;

    switch (arg1) {
        case 0:
            c = 0x40000;
            break;
        case 1:
            c = 0x80000;
            break;
        case 2:
            c = 0x100000;
            break;
        case 3:
            c = 0x200000;
            break;
        case 4:
            c = 0x10000;
            break;
        case 5:
            c = 0x20000;
            break;
        case 6:
            c = 0x400000;
            break;
        default:
            if (*(s32 *)*(u8 **)(arg0 + 0x44) & 0x1000000) {
                c = 0x20000;
            } else {
                c = 0x10000;
            }
            break;
    }
    *(s32 *)(arg0 + 0xAF0) = (*(s32 *)(arg0 + 0xAF0) & 0xFF00FFFF) | c;
}
