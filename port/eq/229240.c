#include "common.h"

s32 BtlObjXf_Update(s32 arg0);
s32 BtlChar_GetPos(s32 arg0);
s32 BtlPad_Test48(s32 arg0, s32 arg1);
s32 BtlAnim_SetBlend(s32 arg0, f32 farg0);
f32 func_00217330(s32 arg0);
f32 BtlCharApi_GetHeight(s32 arg0);
s32 func_00212878(void);
void func_00212DD8(s32 arg0, s32 arg1);
s32 func_0023C710(s32 arg0);
s32 func_0023C798(s32 arg0, s32 arg1);
s32 func_00218128(s32 arg0, s32 arg1);
s32 func_0023BDA8(s32 arg0, s32 arg1);
s32 func_001FA288(s32 arg0, s32 arg1);
extern f32 D_003863F8;
extern f32 D_003863FC;
extern f32 D_00386400;
extern f32 D_00386404;
extern f32 D_00386408;

s32 func_00229240(s32 arg0) {
    s32 v;
    s32 s2;
    s32 t;
    s32 s0v;
    f32 f20;
    f32 h;

    v = BtlObjXf_Update(arg0);
    if (v == 0x1A4) {
        if (*(s32 *)(BtlChar_GetPos(arg0) + 0xDC) >= 0x5B) {
            BtlAnim_SetBlend(arg0, D_003863F8);
            f20 = func_00217330(arg0);
            h = BtlCharApi_GetHeight(*(s32 *)(arg0 + 0x1534));
            if (!((h + h) < f20)) {
                if (func_00212878() == 0) {
                    return 0xA;
                }
                if ((*(s32 *)(*(u8 **)(arg0 + 0x1530) + 0xE80) & 0x80) != 0) {
                    return 0xA;
                }
            }
            func_00212DD8(arg0, 0);
            return 0x21;
        }
        if (BtlPad_Test48(arg0, 8) == 0) {
            BtlAnim_SetBlend(arg0, D_003863FC);
            return func_0023C710(arg0);
        }
    }

    /* block_17 */
    s2 = func_0023C798(arg0, 0x44F);
    if (s2 != -1) {
        BtlAnim_SetBlend(arg0, D_00386400);
        return s2;
    }
    v = BtlObjXf_Update(arg0);
    s0v = (((v ^ 0x1A4) != 0) ? 0x0192BFE3 : 0x0100BF83)
        | 0x40000 | 0x200000 | 0x400000 | 0x02000000 | 0x04000000;
    if (func_00218128(arg0, 3) != 0) {
        s0v |= 0x10000;
    }
    t = func_0023BDA8(arg0, s0v);
    if (t != s2) {
        BtlAnim_SetBlend(arg0, D_00386404);
        return t;
    }
    if (func_001FA288(arg0, 0xD) != 0 || func_001FA288(arg0, 0x10) != 0) {
        BtlAnim_SetBlend(arg0, D_00386408);
        return func_0023C710(arg0);
    }
    return -1;
}
