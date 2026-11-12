#include "common.h"

void BtlAnim_SetBlend(void *arg0, f32 farg1);
s32 BtlObjXf_Update(s32 arg0);
s32 BtlPad_Test4C(void *arg0, s32 arg1);
s32 func_00211310(void *arg0, s32 arg1, s32 arg2);
s32 func_002174B8(void *arg0);
void func_002174D8(void *arg0, s32 arg1);
s32 func_0023C710(void *arg0);
s32 func_0023C798(void *arg0, s32 arg1);
extern f32 D_00385EF0;
extern f32 D_00385EF4;

s32 func_0021F8F0(void *arg0) {
    s32 temp_v0;

    if ((func_00211310(arg0, 4, 2) != 0) && (BtlPad_Test4C(arg0, 0) != 0)) {
        func_002174D8(arg0, 0x49);
    }
    if (func_00211310(arg0, 2, 1) == 0) {
        return -1;
    }
    if ((BtlObjXf_Update((s32)arg0) != 0x39) || (*(s32 *)((u8 *)arg0 + 0x9C0) < 0)
        || (temp_v0 = func_0023C798(arg0, 0x200), (temp_v0 == -1))) {
        if (func_002174B8(arg0) != -1) {
            BtlAnim_SetBlend(arg0, D_00385EF0);
            return func_002174B8(arg0);
        }
        BtlAnim_SetBlend(arg0, D_00385EF4);
        return func_0023C710(arg0);
    }
    return temp_v0;
}
