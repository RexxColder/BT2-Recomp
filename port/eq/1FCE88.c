#include "common.h"

/* 0x001FCE88: counts arg1 into one of nine s32 counters of arg0 (+0x14AC..+0x14C8). Each counter has a range:
 * arg1 < 0xA, arg1-0xA < 6, arg1-0x11 < 0xF, arg1-0x20 < 3, arg1-0x23 < 3, arg1-0x26 < 3, arg1-0x3D < 3,
 * arg1-0x40 < 3 (unsigned), and arg1 == 0x4A. */
void func_001FCE88(u8 *arg0, u32 arg1) {
    if (arg1 < 0xA) {
        *(s32 *)(arg0 + 0x14AC) += 1;
    }
    if (arg1 - 0xA < 6) {
        *(s32 *)(arg0 + 0x14BC) += 1;
    }
    if (arg1 - 0x11 < 0xF) {
        *(s32 *)(arg0 + 0x14B0) += 1;
    }
    if (arg1 - 0x20 < 3) {
        *(s32 *)(arg0 + 0x14D0) += 1;
    }
    if (arg1 - 0x23 < 3) {
        *(s32 *)(arg0 + 0x14CC) += 1;
    }
    if (arg1 - 0x26 < 3) {
        *(s32 *)(arg0 + 0x14C0) += 1;
    }
    if (arg1 - 0x3D < 3) {
        *(s32 *)(arg0 + 0x14B4) += 1;
    }
    if (arg1 - 0x40 < 3) {
        *(s32 *)(arg0 + 0x14B8) += 1;
    }
    if (arg1 == 0x4A) {
        *(s32 *)(arg0 + 0x14C8) += 1;
    }
}
