#include "common.h"

void BtlAnim_SetBlend(f32 farg0, u8 *arg1);
s32 BtlPad_Test4C(u8 *arg0, s32 arg1);
s32 func_001FA1D0(f32 farg0, u8 *arg1);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 func_00217488(u8 *arg0);
s32 func_002174B8(u8 *arg0);
void func_002174D8(u8 *arg0, s32 arg1);
s32 func_0023C710(u8 *arg0);
extern f32 D_00385ED0;
extern f32 D_00385ED4;
extern f32 D_00385ED8;

s32 func_0021F490(u8 *arg0) {
    if (*(s32 *)(arg0 + 0x8DC) & 1) {
        if (func_00211310((s32)arg0, 4, 2) == 0) {
            goto block_15;
        }
        if ((func_00217488(arg0) == 0x79) && (BtlPad_Test4C(arg0, 0) != 0)) {
            func_002174D8(arg0, 0x7A);
        }
        if (func_001FA1D0(D_00385ED0, arg0) == 0) {
            goto block_15;
        }
        if (func_002174B8(arg0) == -1) {
block_15:
            if (func_00211310((s32)arg0, 2, 1) != 0) {
                BtlAnim_SetBlend(D_00385ED8, arg0);
                return func_0023C710(arg0);
            }
            return -1;
        }
        BtlAnim_SetBlend(D_00385ED4, arg0);
        return func_002174B8(arg0);
    }
    return -1;
}
