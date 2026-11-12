#include "common.h"

s32 func_00211310(u8 *arg0, s32 arg1, s32 arg2);
s32 func_00217488(u8 *arg0);
s32 func_0023F410(u8 *arg0);
s32 func_0023C798(u8 *arg0, s32 arg1);
s32 func_0023C710(u8 *arg0);
void BtlAnim_SetBlend(u8 *arg0, f32 farg0);
s32 BtlObjXf_Update(u8 *arg0);
extern f32 D_00386A44;

/* 0x002373E8: if func_00211310(obj,4,2) != 0: func_00217488 == 0x7E -> 0x85 or 0x7F by bit 0x200 of func_0023F410;
 * == 0x82 -> 0x83. Else func_00211310(obj,2,1) == 0 -> -1; blend, BtlObjXf_Update == 0x39 and obj+0x9C0 >= 0 ->
 * func_0023C798(obj, 0x200) unless it returns -1; otherwise tail func_0023C710(obj). */
s32 func_002373E8(u8 *arg0) {
    s32 v;
    s32 w;
    s32 x;

    if (func_00211310(arg0, 4, 2) != 0) {
        v = func_00217488(arg0);
        if (v == 0x7E) {
            x = func_0023F410(arg0);
            return (x & 0x200) ? 0x85 : 0x7F;
        }
        if (v == 0x82) {
            return 0x83;
        }
    }
    if (func_00211310(arg0, 2, 1) == 0) {
        return -1;
    }
    BtlAnim_SetBlend(arg0, D_00386A44);
    if (BtlObjXf_Update(arg0) == 0x39) {
        w = *(s32 *)(arg0 + 0x9C0);
        if (w >= 0) {
            x = func_0023C798(arg0, 0x200);
            if (x != -1) {
                return x;
            }
        }
    }
    return func_0023C710(arg0);
}
