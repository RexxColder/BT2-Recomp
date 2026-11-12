#include "common.h"

s32 func_0011ED28(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_t0;
    s32 temp_t0_2;
    s32 temp_t8;
    s32 temp_t8_10;
    s32 temp_t8_11;
    s32 temp_t8_12;
    s32 temp_t8_2;
    s32 temp_t8_3;
    s32 temp_t8_4;
    s32 temp_t8_5;
    s32 temp_t8_6;
    s32 temp_t8_7;
    s32 temp_t8_8;
    s32 temp_t8_9;
    s32 var_t8;
    u16 temp_a3;
    u16 temp_t9;
    u16 temp_t9_2;

    temp_t0 = 7 - arg3;
    temp_t0_2 = (temp_t0 < 3) ? 3 : temp_t0;
    temp_a3 = (*(u16 *)((u8 *)arg0 + 0));
    temp_t9 = (*(u16 *)((u8 *)arg0 + 2));
    temp_t8 = (temp_a3 & 1) << 0xD;
    temp_t8_2 = (temp_a3 & 2) ? (temp_t8 | 0x4000) : temp_t8;
    temp_t8_3 = (temp_a3 & 4) ? (temp_t8_2 | 0x1000) : temp_t8_2;
    temp_t8_4 = (temp_a3 & 0x10) | ((temp_a3 & 8) ? (temp_t8_3 | 0x8000) : temp_t8_3);
    temp_t8_5 = (temp_a3 & 0x20) ? (temp_t8_4 | 0x40) : temp_t8_4;
    temp_t8_6 = (temp_a3 & 0x40) ? (temp_t8_5 | 0x80) : temp_t8_5;
    temp_t8_7 = (temp_a3 & 0x80) ? (temp_t8_6 | 0x20) : temp_t8_6;
    temp_t8_8 = (temp_a3 & 0x100) ? (temp_t8_7 | 0x400) : temp_t8_7;
    temp_t9_2 = (arg2 < temp_t0_2) ? (temp_t9 | (*(u16 *)((u8 *)arg0 + 4))) : temp_t9;
    temp_t8_9 = (temp_a3 & 0x200) ? (temp_t8_8 | 0x100) : temp_t8_8;
    temp_t8_10 = (temp_a3 & 0x400) ? (temp_t8_9 | 2) : temp_t8_9;
    temp_t8_11 = (temp_a3 & 0x800) ? (temp_t8_10 | 0x800) : temp_t8_10;
    temp_t8_12 = (temp_a3 & 0x1000) ? (temp_t8_11 | 0x200) : temp_t8_11;
    var_t8 = (temp_a3 & 0x2000) ? (temp_t8_12 | 4) : temp_t8_12;
    if ((arg2 % temp_t0_2) == 1) {
        if (temp_t9_2 & 1) {
            var_t8 |= arg1 ^ 0x2000;
        }
        if (temp_t9_2 & 2) {
            var_t8 |= arg1 ^ 0x4000;
        }
        if (temp_t9_2 & 4) {
            var_t8 |= arg1 ^ 0x1000;
        }
        if (temp_t9_2 & 8) {
            var_t8 |= arg1 ^ 0x8000;
        }
        if (temp_t9_2 & 0x10) {
            var_t8 |= arg1 ^ 0x10;
        }
        if (temp_t9_2 & 0x20) {
            var_t8 |= arg1 ^ 0x40;
        }
        if (temp_t9_2 & 0x40) {
            var_t8 |= arg1 ^ 0x80;
        }
        if (temp_t9_2 & 0x80) {
            var_t8 |= arg1 ^ 0x20;
        }
        if (temp_t9_2 & 0x100) {
            var_t8 |= arg1 ^ 0x400;
        }
        if (temp_t9_2 & 0x200) {
            var_t8 |= arg1 ^ 0x100;
        }
        if (temp_t9_2 & 0x400) {
            var_t8 |= arg1 ^ 2;
        }
        if (temp_t9_2 & 0x800) {
            var_t8 |= arg1 ^ 0x800;
        }
        if (temp_t9_2 & 0x1000) {
            var_t8 |= arg1 ^ 0x200;
        }
        if (temp_t9_2 & 0x2000) {
            var_t8 |= arg1 ^ 4;
        }
    }
    return var_t8;
}
