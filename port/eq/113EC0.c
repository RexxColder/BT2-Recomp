#include "common.h"

/* 0x00113EC0: the four 16-bit arguments are sign-extended (sll/sra 16). Each one that is > 0 is stored as an s32
 * into two fields of the struct at arg0: arg1 -> +0x20, +0x40 and (only when arg3 > 0) +0x50, +0x30 with arg1
 * itself; arg2 -> +0x34, +0x24; arg4 -> +0x54, +0x44. arg3 gates the +0x50/+0x30 pair. */
void func_00113EC0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 a1 = (s16)arg1;
    s32 a2 = (s16)arg2;
    s32 a3 = (s16)arg3;
    s32 t0 = (s16)arg4;

    if (a1 > 0) {
        *(s32 *)(arg0 + 0x20) = a1;
        *(s32 *)(arg0 + 0x40) = a1;
    }
    if (a3 > 0) {
        *(s32 *)(arg0 + 0x50) = a1;
        *(s32 *)(arg0 + 0x30) = a1;
    }
    if (a2 > 0) {
        *(s32 *)(arg0 + 0x34) = a2;
        *(s32 *)(arg0 + 0x24) = a2;
    }
    if (t0 > 0) {
        *(s32 *)(arg0 + 0x54) = t0;
        *(s32 *)(arg0 + 0x44) = t0;
    }
}
