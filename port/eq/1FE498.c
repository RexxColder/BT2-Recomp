#include "common.h"

s32 BattleResult_GetFlags(s32 arg0, s32 arg1);
s32 BtlObjXf_Update(s32 arg0);
s32 func_001FA3A8(s32 arg0);
s32 func_00211288(s32 arg0);

s32 func_001FE498(s32 arg0, s32 arg1) {
    s32 flags;
    s32 ret = 1;

    flags = func_001FA3A8(BtlObjXf_Update(func_00211288(arg1))) & 0x40000;
    if (flags != 0) {
        ret = (BattleResult_GetFlags(arg0, flags) & 2) == 0;
    }
    return ret;
}
