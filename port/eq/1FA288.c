#include "common.h"

s32 BtlObjXf_Update(s32 arg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);

s32 func_001FA288(s32 arg0, s32 arg1) {
    if (BtlObjXf_Update(arg0) != arg1) {
        return 0;
    }
    if (func_00211310(arg0, 2, 1) != 0) {
        return 1;
    }
    return 0;
}
