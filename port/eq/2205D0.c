#include "common.h"

s32 func_0023BDA8(s32 arg0, s32 arg1);
void BtlAnim_SetBlend(s32 arg0, s32 arg1, s32 arg2, f32 farg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2, f32 farg0);
s32 func_0023C710(s32 arg0);
extern f32 D_00385F20;
extern f32 D_00385F24;

s32 func_002205D0(s32 arg0) {
    s32 temp_v0;

    temp_v0 = func_0023BDA8(arg0, 0x200000);
    if (temp_v0 != -1) {
        BtlAnim_SetBlend(arg0, 2, 1, D_00385F20);
        return temp_v0;
    }
    if (func_00211310(arg0, 2, 1, D_00385F20) != 0) {
        /* GUESS arity: a1/a2 of this call are leftovers of func_00211310, passed as 2, 1 */
        BtlAnim_SetBlend(arg0, 2, 1, D_00385F24);
        return func_0023C710(arg0);
    }
    return -1;
}
