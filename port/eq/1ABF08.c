#include "common.h"

s32 BtlTaskList_AddTail(s32 arg0, void *arg1, s64 *arg2, s64 arg3, s64 arg4, s64 arg5, s64 arg6, s64 arg7,
                        s64 arg8, s64 arg9, s64 arg10, s64 arg11, s64 arg12, s64 arg13, s64 arg14, s64 arg15);
extern u8 D_00342728[];
extern s32 *D_00387848;

void func_001ABF08(s64 *arg0) {
    s64 blk[8];

    /* the call stores its 9th..16th args in the caller frame: blk, which is also passed as the pointer */
    blk[0] = arg0[0];
    blk[1] = arg0[1];
    blk[2] = arg0[2];
    blk[3] = arg0[3];
    blk[4] = arg0[4];
    blk[5] = arg0[5];
    blk[6] = arg0[6];
    blk[7] = arg0[7];
    BtlTaskList_AddTail(*D_00387848, D_00342728, blk, arg0[4], arg0[5], arg0[6], arg0[1], arg0[0],
                        blk[0], blk[1], blk[2], blk[3], blk[4], blk[5], blk[6], blk[7]);
}
