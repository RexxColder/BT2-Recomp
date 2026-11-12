#include "common.h"

void BtlAnim_SetBlend(s32 arg0, f32 farg0);
s32 BtlPad_Test48(s32 arg0, s32 arg1);
s32 func_0023C710(s32 arg0);
extern f32 D_003865A8;

s32 func_0022C090(s32 arg0) {
    if (BtlPad_Test48(arg0, 4) == 0) {
        BtlAnim_SetBlend(arg0, D_003865A8);
        return func_0023C710(arg0);
    }
    return -1;
}
