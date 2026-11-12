#include "common.h"

void BtlAnim_SetBlend(f32 farg0, s32 arg1);
s32 BtlPad_Test4C(s32 arg0, s32 arg1);
s32 func_001FA288(s32 arg0, s32 arg1);
s32 func_0023C710(s32 arg0);
extern f32 D_003864A4;

s32 func_0022A2D8(s32 arg0) {
    if (BtlPad_Test4C(arg0, 0) != 0) {
        return 0x59;
    }
    if (BtlPad_Test4C(arg0, 3) != 0) {
        return 0x7E;
    }
    if (BtlPad_Test4C(arg0, 1) != 0) {
        return 0x6D;
    }
    if (func_001FA288(arg0, 0x31) == 0) {
        return -1;
    }
    BtlAnim_SetBlend(D_003864A4, arg0);
    return func_0023C710(arg0);
}
