#include "common.h"

s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 func_00210E18(s32 arg0);
s32 func_0023F420(s32 arg0);
s32 BtlPad_Test4C(s32 arg0, s32 arg1);
s32 BtlPad_Test48(s32 arg0, s32 arg1);
void func_002174D8(s32 arg0, s32 arg1);
f32 func_001FA318(s32 arg0);
s32 func_002174B8(s32 arg0);
void BtlAnim_SetBlend(f32 farg0, s32 arg0);
s32 BtlObjXf_Update(s32 arg0);
s32 func_0023C798(s32 arg0, s32 arg1);
s32 func_0023C710(s32 arg0);
extern f32 D_00385C20;

s32 func_0021A730(u8 *arg0) {
    s32 r;

    if (func_00211310((s32)arg0, 4, 2) != 0) {
        if (func_00210E18((s32)arg0) == 0x96) {
            if ((func_0023F420((s32)arg0) & 0x2000) && (BtlPad_Test4C((s32)arg0, 1) != 0)) {
                if (BtlPad_Test48((s32)arg0, 8) == 0) {
                    func_002174D8((s32)arg0, 0x78);
                }
            }
            if (BtlPad_Test4C((s32)arg0, 0) != 0) {
                func_002174D8((s32)arg0, 0x49);
            }
        }
        if (func_001FA318((s32)arg0) > 0.5f) {
            if (func_002174B8((s32)arg0) != -1) {
                return func_002174B8((s32)arg0);
            }
        }
    }

    if (func_00211310((s32)arg0, 2, 1) == 0) {
        return -1;
    }
    BtlAnim_SetBlend(D_00385C20, (s32)arg0);
    if (BtlObjXf_Update((s32)arg0) == 0x39) {
        if (*(s32 *)(arg0 + 0x9C0) >= 0) {
            r = func_0023C798((s32)arg0, 0x200);
            if (r != -1) {
                return r;
            }
        }
    }
    return func_0023C710((s32)arg0);
}
