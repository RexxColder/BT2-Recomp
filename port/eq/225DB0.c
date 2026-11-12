#include "common.h"

void BtlAnim_SetBlend(s32 arg0, f32 farg0);
s32 BtlPad_Test48(s32 arg0, s32 arg1);
s32 func_0023C710(s32 arg0);
extern f32 D_0038622C;

s32 func_00225DB0(s32 arg0) {
    if (BtlPad_Test48(arg0, 2) == 0) {
        BtlAnim_SetBlend(arg0, D_0038622C);
        return func_0023C710(arg0);
    }
    return -1;
}
