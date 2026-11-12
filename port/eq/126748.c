#include "common.h"

s32 BtlScene_IsTimeStopped(void);
s32 BtlScene_IsCharStopped(s32 arg0);
s32 func_00126528(s32 arg0);

s32 BtlScene_IsEffectStopped(s32 arg0, s32 arg1) {
    s32 r;

    r = 0;
    if (arg1 == 1) {
        if (BtlScene_IsCharStopped(arg0) != 0) {
            r = 1;
        }
    } else if (arg1 == 0) {
        if (func_00126528(arg0) != 0) {
            r = 1;
        }
    } else if (arg1 == 3) {
        if (BtlScene_IsTimeStopped() != 0) {
            r = 1;
        }
    } else {
        r = BtlScene_IsTimeStopped() != 0;
    }
    return r;
}
