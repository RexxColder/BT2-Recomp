#include "common.h"

void BtlAnim_SetBlend(s32 arg0, f32 farg0);
s32 func_0023C710(s32 arg0);
extern f32 D_00386B4C;

s32 func_00239698(s32 arg0) {
    if (!(*(s32 *)((u8 *)arg0 + 0x8DC) & 1)) {
        return -1;
    }
    BtlAnim_SetBlend(arg0, D_00386B4C);
    return func_0023C710(arg0);
}
