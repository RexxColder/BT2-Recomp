#include "common.h"

void BtlAnim_SetBlend(f32 farg0, u8 *arg1, s32 arg2);
s32 BtlPad_Test48(s32 arg0, s32 arg1);
s32 func_001FA288(u8 *arg0, s32 arg1);
s32 func_00211310(u8 *arg0, s32 arg1, s32 arg2);
s32 func_0023BDA8(u8 *arg0, s32 arg1);
s32 func_0023C710(u8 *arg0);
extern f32 D_00386158;
extern f32 D_0038615C;
extern f32 D_00386160;

s32 func_002247D8(u8 *arg0) {
    s32 temp_v0;

    if (func_00211310(arg0, 4, 0x2000) != 0) {
        return 0x9D;
    }
    temp_v0 = func_0023BDA8(arg0, 0x06000000);
    if (temp_v0 != -1) {
        BtlAnim_SetBlend(D_00386158, arg0, 0);
        return temp_v0;
    }
    if (*(s32 *)(arg0 + 0x8DC) & 1) {
        if ((func_00211310(arg0, 4, 0x100600) == 0) && (func_00211310(arg0, 2, 0x10) == 0)) {
            if (BtlPad_Test48((s32)(u32)arg0, 2) == 0) {
                BtlAnim_SetBlend(D_0038615C, arg0, 0);
                return func_0023C710(arg0);
            }
        }
    }
    if (func_001FA288(arg0, 0xFD) == 0) {
        return -1;
    }
    BtlAnim_SetBlend(D_00386160, arg0, 0);
    return 0x49;
}
