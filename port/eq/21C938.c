#include "common.h"

void BtlAnim_SetBlend(f32 farg0, s32 arg0);
s32 BtlObjXf_Update(s32 arg0);
s32 BtlPad_Test4C(s32 arg0, s32 arg1);
void func_002174D8(s32 arg0, s32 arg1);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 func_002174B8(s32 arg0);
f32 func_001FA318(s32 arg0);
s32 func_0023F420(s32 arg0);
s32 func_0023C710(s32 arg0);
void *BtlChar_GetPos(s32 arg0);
extern f32 D_00385D5C;
extern f32 D_00385D60;
extern f32 D_00385D64;
extern f32 D_00385D68;
extern f32 D_00385D6C;
extern f32 D_00385D70;
extern f32 D_00385D74;

s32 func_0021C938(s32 arg0) {
    u8 *p;

    p = (u8 *)arg0;
    if (*(s32 *)(p + 0x8DC) & 2) {
        BtlAnim_SetBlend(D_00385D5C, arg0);
        return 0xA;
    }
    if (func_0023F420(arg0) & 0x80000) {
        if (BtlObjXf_Update(arg0) == 0x7C) {
            if (BtlPad_Test4C(arg0, 1) != 0) {
                func_002174D8(arg0, 0x57);
            }
            if (func_00211310(arg0, 0, 4) != 0) {
                if (func_002174B8(arg0) != -1) {
                    if (D_00385D60 < func_001FA318(arg0)) {
                        BtlAnim_SetBlend(D_00385D64, arg0);
                        *(f32 *)((u8 *)BtlChar_GetPos(arg0) + 0xC0) = D_00385D68;
                        return func_002174B8(arg0);
                    }
                }
            }
        }
    }
    if (func_00211310(arg0, 4, 2) != 0) {
        if (BtlPad_Test4C(arg0, 0) != 0) {
            func_002174D8(arg0, 0x49);
        }
        if (D_00385D6C < func_001FA318(arg0)) {
            if (func_002174B8(arg0) != -1) {
                BtlAnim_SetBlend(D_00385D70, arg0);
                return func_002174B8(arg0);
            }
        }
    }
    if (func_00211310(arg0, 2, 1) == 0) {
        return -1;
    }
    BtlAnim_SetBlend(D_00385D74, arg0);
    return func_0023C710(arg0);
}
