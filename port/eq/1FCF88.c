#include "common.h"

/* 0x001FCF88: the same nine range counters as func_001FCE88, into arg0 +0x14D4, +0x14E4, +0x14D8, +0x14F8,
 * +0x14F4, +0x14E8, +0x14DC, +0x14E0 and +0x14F0 (arg1 == 0x4A). */
void func_001FCF88(u8 *arg0, u32 arg1) {
    if (arg1 < 0xA) {
        *(s32 *)(arg0 + 0x14D4) += 1;
    }
    if (arg1 - 0xA < 6) {
        *(s32 *)(arg0 + 0x14E4) += 1;
    }
    if (arg1 - 0x11 < 0xF) {
        *(s32 *)(arg0 + 0x14D8) += 1;
    }
    if (arg1 - 0x20 < 3) {
        *(s32 *)(arg0 + 0x14F8) += 1;
    }
    if (arg1 - 0x23 < 3) {
        *(s32 *)(arg0 + 0x14F4) += 1;
    }
    if (arg1 - 0x26 < 3) {
        *(s32 *)(arg0 + 0x14E8) += 1;
    }
    if (arg1 - 0x3D < 3) {
        *(s32 *)(arg0 + 0x14DC) += 1;
    }
    if (arg1 - 0x40 < 3) {
        *(s32 *)(arg0 + 0x14E0) += 1;
    }
    if (arg1 == 0x4A) {
        *(s32 *)(arg0 + 0x14F0) += 1;
    }
}
