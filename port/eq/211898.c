#include "common.h"

extern s32 func_003126C8();

/* 0x00211898: three calls on obj+0x950/0x960/0x970 with second arg a1 (pass-through), a2, a3. */
s32 func_00211898(u8 *obj, s32 a1, s32 a2, s32 a3) {
    func_003126C8(obj + 0x950, a1);
    func_003126C8(obj + 0x960, a2);
    return func_003126C8(obj + 0x970, a3);
}
