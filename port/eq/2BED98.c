#include "common.h"

void func_002D3298(s32 arg0, void *arg1, void *arg2, s32 *arg3);
s64 func_002D89B0(void);
s64 func_002D8B00(void);
s32 func_002F4590(s32 arg0);
void func_002F4910(s32 arg0, s32 *arg1, s32 *arg2);
extern s32 D_00346C0C __attribute__((section(".data")));

void func_002BED98(s32 arg0, s32 arg1, s32 *arg2, s32 *arg3) {
    s64 blk[4];
    s32 sp30;
    s32 sp34;
    s32 out[4];

    D_00346C0C = func_002F4590(arg1);
    func_002F4910(arg1, &sp30, &sp34);
    blk[0] = (s64)sp30;
    blk[1] = (s64)sp34;
    blk[2] = func_002D89B0();
    blk[3] = func_002D8B00();
    func_002D3298(arg0, blk, &blk[2], out);
    *arg2 = out[0];
    *arg3 = out[2];
}
