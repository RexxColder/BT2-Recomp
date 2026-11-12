#include "common.h"

void BtlAnim_SetBlend(f32 arg0, f32 arg1);
s32 func_002174B8(u8 *arg0);
s32 func_0023C710(u8 *arg0);
extern f32 D_003867FC;

s32 func_0022FEA0(u8 *arg0, f32 farg0, f32 farg1) {
    if ((*(s32 *)(arg0 + 0x8DC) & 1) == 0) {
        return -1;
    }
    BtlAnim_SetBlend(D_003867FC, farg1);
    if (func_002174B8(arg0) != -1) {
        return func_002174B8(arg0);
    }
    return func_0023C710(arg0);
}
