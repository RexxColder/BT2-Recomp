#include "common.h"

extern f32 D_00386C54;

s32 BtlPad_Test48(s32 arg0, s32 arg1);
f32 func_00207E88(s32 arg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);

/* 0x0023D380(i): 0xD unless func_00211310(i, 0, 1) is set and BtlPad_Test48(i, 8) is set; then 0xE when
 * func_00207E88(i) < D_00386C54 and func_00211310(i, 1, 4) is clear, else 0xD. */
s32 func_0023D380(s32 arg0) {
    if (func_00211310(arg0, 0, 1) == 0) {
        return 0xD;
    }
    if (BtlPad_Test48(arg0, 8) == 0) {
        return 0xE;
    }
    if (func_00207E88(arg0) < D_00386C54) {
        if (func_00211310(arg0, 1, 4) == 0) {
            return 0xE;
        }
    }
    return 0xD;
}
