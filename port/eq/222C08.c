#include "common.h"

s32 BtlAnim_SetBlend(s32 arg0, f32 farg0);
s32 BtlObjXf_Update(s32 arg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 func_0023C780(s32 arg0);
extern f32 D_00386058;

s32 func_00222C08(s32 arg0) {
    s32 t;

    if (func_00211310(arg0, 2, 1) == 0) {
        return -1;
    }
    BtlAnim_SetBlend(arg0, D_00386058);
    t = BtlObjXf_Update(arg0);
    if (t == 0xD8 || t == 0xDA) {
        return func_0023C780(arg0);
    }
    if (t == 0xD7 || t == 0xD9) {
        return (func_00211310(arg0, 0, 0x100) == 0) ? 0x21 : 0x20;
    }
    return -1;
}
