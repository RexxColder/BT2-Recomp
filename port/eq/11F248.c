#include "common.h"

s32 func_00126040(s32 arg0);
s32 func_00126058(s32 arg0, s32 arg1, s32 arg2);
s32 func_001FA3A8(s32 arg0);
s32 func_0023F430(s32 arg0);
s32 BtlMember_IsKiFull(s32 arg0);
s32 EftObj_UpdateMtx(s32 arg0);

s32 func_0011F248(s32 arg0, s32 arg1) {
    s32 flags = arg1 & 0xFFFF;

    if (flags & 4) {
        if (func_00126058(arg0, 0, 2) != 0) {
            return 1;
        }
    }
    if (flags & 8) {
        if (func_00126058(arg0, 0, 4) != 0) {
            return 1;
        }
    }
    if (flags & 0x20) {
        if ((func_001FA3A8(EftObj_UpdateMtx(arg0)) & 0x100010) == 0) {
            return 1;
        }
    }
    if (flags & 0x40) {
        if (func_00126058(arg0, 0, 0x800) != 0) {
            return 1;
        }
        if (func_00126058(arg0, 8, 1) != 0) {
            return 1;
        }
        if (func_0023F430(func_00126040(arg0)) & 0x80) {
            if (BtlMember_IsKiFull(func_00126040(arg0)) == 0) {
                return 1;
            }
        }
    }
    if (flags & 0x80) {
        return func_00126058(arg0, 0, 1) != 0;
    }
    return 0;
}
