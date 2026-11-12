#include "common.h"

s32 BtlObjXf_Update(s32 arg0);
s32 func_001FA3A8(s32 arg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);

s32  func_00218838(u8 *arg0, s32 arg1) {
    u8 v1;

    v1 = 1;
    if (func_00211310((s32)arg0, 2, 0x1000) == 0) {
        v1 = 0;
        if (func_00211310((s32)arg0, 2, 0x800) == 0) {
            if (arg1 & 0xFF) {
                v1 = arg0[0xB54];
            } else {
                v1 = (func_001FA3A8(BtlObjXf_Update((s32)arg0)) & 0x01000000) != 0;
            }
        }
    }
    return (u8)(v1);
}
