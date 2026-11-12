#include "m2c_macros.h"

extern s32 BtlCharApi_IsHidden(s32 arg0);
extern s32 BtlStage_IsReady(void);
extern s32 func_0020A658(s32 arg0);
extern s32 func_0020A6A0(s32 arg0);

s32 func_001267E8(s32 arg0, s32 arg1) {
    s32 s0;
    s32 s1;
    s32 v0;

    s0 = arg1;
    s1 = 0;
    if (BtlCharApi_IsHidden(arg0) == 0) {
        return 0;
    }
    if (s0 == 1) {
        v0 = func_0020A658(arg0);
    } else if (s0 == 0) {
        v0 = func_0020A6A0(arg0);
    } else {
        if (s0 >= 2) {
            s1 = 1;
            if (s0 == 3) {
                return s1;
            }
        }
        s0 = 1;
        s1 = func_0020A658(arg0) != 0;
        s1 = (BtlStage_IsReady() == 0) ? 1 : s1;
        return s1;
    }
    if (v0 != 0) {
        s1 = 1;
    }
    return s1;
}
