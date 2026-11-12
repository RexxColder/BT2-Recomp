#include "common.h"

void BtlAnim_SetBlend(s32 arg0, f32 farg0);
s32 func_0023C780(s32 arg0);
extern f32 D_00386098;

s32 func_002231A0(s32 arg0) {
    if (*(s32 *)((u8 *)arg0 + 0xB74) > 0) {
        return -1;
    }
    BtlAnim_SetBlend(arg0, D_00386098);
    return func_0023C780(arg0);
}
