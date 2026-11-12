#include "common.h"

#define PTR(p, off) (*(u8 **)((u8 *)(p) + (off)))
#define W32(p, off) (*(s32 *)((u8 *)(p) + (off)))

extern f32 D_003863B4;
extern f32 D_003863B8;
extern f32 D_003863BC;
extern f32 D_003863C0;

s32 BtlObjXf_Update(u8 *obj);
u8 *BtlChar_GetPos(u8 *obj);
s32 BtlAnim_SetBlend(u8 *obj, f32 farg0);
f32 func_00217330(u8 *obj);
f32 BtlCharApi_GetHeight(s32 arg0);
s32 func_00212878(u8 *obj);
s32 func_00212DD8(u8 *obj, s32 arg1);
s32 func_0023C798(u8 *obj, s32 arg1);
s32 func_00218128(u8 *obj, s32 arg1);
s32 func_0023BDA8(u8 *obj, s32 arg1);
s32 BtlPad_Test48(u8 *obj, s32 arg1);
s32 func_0023C710(u8 *obj);

s32 func_002287F8(u8 *obj) {
    u8 *pos;
    f32 f20;
    f32 h;
    s32 s0;
    s32 s2;

    if (BtlObjXf_Update(obj) == 0x1A4) {
        pos = BtlChar_GetPos(obj);
        if (W32(pos, 0xDC) >= 0x5B) {
            BtlAnim_SetBlend(obj, D_003863B4);
            f20 = func_00217330(obj);
            h = BtlCharApi_GetHeight(W32(obj, 0x1534));
            if (h + h < f20) {
                func_00212DD8(obj, 0);
                return 0x21;
            }
            if (func_00212878(obj) == 0) {
                return 0xA;
            }
            if (W32(PTR(obj, 0x1530), 0xE80) & 0x80) {
                return 0xA;
            }
            func_00212DD8(obj, 0);
            return 0x21;
        }
    }

    s2 = func_0023C798(obj, 0x4F);
    if (s2 != -1) {
        BtlAnim_SetBlend(obj, D_003863B8);
        return s2;
    }

    s0 = (BtlObjXf_Update(obj) != 0x1A4) ? 0x19A07FF : 0x108079F;
    s0 |= 0x40000;
    s0 |= 0x200000;
    s0 |= 0x400000;
    s0 |= 0x2000000;
    s0 |= 0x4000000;
    if (func_00218128(obj, 3) != 0) {
        s0 |= 0x10000;
    }
    s0 = func_0023BDA8(obj, s0);
    if (s0 != s2) {
        BtlAnim_SetBlend(obj, D_003863BC);
        return s0;
    }
    if (BtlPad_Test48(obj, 8) != 0) {
        return -1;
    }
    BtlAnim_SetBlend(obj, D_003863C0);
    return func_0023C710(obj);
}
