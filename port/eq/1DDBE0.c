#include "common.h"

s32 BtlTaskList_AddTail(s32 arg0, void *arg1, s64 *arg2, s64 arg3, s64 arg4, s64 arg5, s64 arg6, s64 arg7,
                        s64 arg8, s64 arg9, s64 arg10, s64 arg11, s64 arg12, s64 arg13, s64 arg14, s64 arg15);
extern u8 D_003431D8[];
extern s32 D_003878D8;

void func_001DDBE0(s64 *arg0) {
    s64 blk[8];

    blk[0] = arg0[0];
    blk[1] = arg0[1];
    blk[2] = arg0[2];
    blk[3] = arg0[3];
    blk[4] = arg0[4];
    blk[5] = arg0[5];
    blk[6] = arg0[6];
    blk[7] = arg0[7];
    /* a3 = 0x18, t0 = 0x20, t1 = 0x28, t2 = 0x30, t3 = 0x8; 9th..16th args = the eight doublewords in order */
    BtlTaskList_AddTail(D_003878D8, D_003431D8, blk, arg0[3], arg0[4], arg0[5], arg0[6], arg0[1],
                        blk[0], blk[1], blk[2], blk[3], blk[4], blk[5], blk[6], blk[7]);
}
