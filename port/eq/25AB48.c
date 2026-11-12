#include "common.h"

s32 func_0025A310(s32 arg0);
extern u8 *D_00387A30;

s32 func_0025AB48(void) {
    s32 ret;
    s32 f;

    ret = 1;
    if (*(u8 *)(D_00387A30 + 0x31C) == 0) {
        ret = 0;
        if (*(s32 *)(D_00387A30 + 0x2B0) != 0) {
            f = *(s32 *)(D_00387A30 + 0x2F8);
            if (f & 2) {
                func_0025A310((s32)D_00387A30);
                return 0;
            }
            ret = 1;
            if (!(f & 1)) {
                ret = 0;
            }
        }
    }
    return ret;
}
