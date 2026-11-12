#include "common.h"

s32 EftObj_UpdateMtx(s32 arg0);
s32 func_00126058(s32 arg0, s32 arg1, s32 arg2);
s32 func_001FA3A8(s32 arg0);

s32 func_0011F370(s32 arg0, s32 arg1) {
    s32 flags;

    flags = arg1 & 0xFFFF;
    if ((flags & 1) != 0) {
        if (func_00126058(arg0, 4, 8) != 0) {
            return 1;
        }
        if (func_00126058(arg0, 4, 4) != 0) {
            return 1;
        }
    }
    if ((flags & 2) != 0) {
        return 0;
    }
    if ((func_001FA3A8(EftObj_UpdateMtx(arg0)) & 0x10) != 0) {
        return 1;
    }
    return 0;
}
