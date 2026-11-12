#include "common.h"

extern s32 func_0023C798(s32 obj, s32 a1);
extern void func_002174D8(s32 obj, s32 a1);
extern f32 func_001FA318(s32 obj);
extern s32 func_00211310(s32 obj, s32 a1, s32 a2);
extern s32 func_0023BDA8(s32 obj, s32 a1);
extern s32 BtlPad_Test48(s32 obj, s32 a1);
extern s32 func_002174B8(s32 obj);
extern s32 func_00217560(s32 a0);
extern s32 BtlObjXf_Update(s32 obj);
extern s32 func_0023F410(s32 obj);
extern s32 BtlAnim_SetBlend(s32 obj, f32 blend);
extern void func_00211418(s32 obj, s32 a1);
extern s32 func_00217488(s32 obj);
extern f32 func_00207E88(s32 obj);
extern f32 func_00207E80(s32 obj);
extern s32 func_0023C710(s32 obj);
extern f32 D_00386680;
extern f32 D_00386684;
extern f32 D_00386688;
extern f32 D_0038668C;
extern f32 D_00386690;
extern f32 D_00386694;
extern f32 D_00386698;
extern f32 D_0038669C;
extern f32 D_003866A0;
extern f32 D_003866A4;

s32 func_0022D550(s32 obj) {
    s32 sel;
    f32 limit;
    f32 ax;

    func_002174D8(obj, func_0023C798(obj, 0xC3));
    if (D_00386680 < func_001FA318(obj)) {
        sel = 0x800;
        if (func_00211310(obj, 1, 1) != 0) {
            sel = 0x1800;
        } else if (BtlPad_Test48(obj, 8) == 0) {
            sel = 0x804;
        }
        func_002174D8(obj, func_0023BDA8(obj, sel));
    }

    if (func_00211310(obj, 0, 6) != 0 && func_00211310(obj, 0, 1) != 0) {
        if ((func_00217560(func_002174B8(obj)) & 0x800) != 0) {
            limit = D_00386684;
            if (BtlObjXf_Update(obj) == 0x28 && (func_0023F410(obj) & 0x20) != 0) {
                limit = D_00386688;
            }
            if (limit < func_001FA318(obj)) {
                BtlAnim_SetBlend(obj, D_0038668C);
                return func_002174B8(obj);
            }
        } else if ((func_00217560(func_002174B8(obj)) & 2) != 0) {
            if (*(s32 *)(obj + 0x998) > 0) {
                if (D_00386690 < func_001FA318(obj)) {
                    BtlAnim_SetBlend(obj, D_00386694);
                    return func_002174B8(obj);
                }
            }
        } else if (func_002174B8(obj) == 0xE) {
            if (D_00386698 < func_001FA318(obj)) {
                BtlAnim_SetBlend(obj, D_0038669C);
                return func_002174B8(obj);
            }
        }
    }

    if (func_00211310(obj, 2, 1) == 0) {
        return -1;
    }
    BtlAnim_SetBlend(obj, D_003866A0);
    func_00211418(obj, 0x1000000);
    if (func_00211310(obj, 0, 2) != 0) {
        if (func_00217488(obj) == 0x19 && BtlPad_Test48(obj, 4) != 0) {
            if ((func_0023F410(obj) & 0x1000) == 0) {
                return 0x11;
            }
            return 0xC;
        }
        if (func_00217488(obj) == 0x1A && BtlPad_Test48(obj, 5) != 0) {
            return 0x12;
        }
    }
    if (func_00217488(obj) == 0x18 && BtlPad_Test48(obj, 3) != 0 && BtlPad_Test48(obj, 0xD) != 0) {
        ax = __builtin_fabsf(func_00207E88(obj));
        if (__builtin_fabsf(func_00207E80(obj)) < ax) {
            return 0xD;
        }
    }
    if (func_002174B8(obj) == -1) {
        return func_0023C710(obj);
    }
    BtlAnim_SetBlend(obj, D_003866A4);
    return func_002174B8(obj);
}
