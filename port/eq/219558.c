#include "common.h"

extern f32 func_001FA318(s32 arg0);
extern s32 BtlObjXf_Update(s32 arg0);
extern s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
extern s32 BtlAnim_SetBlend(s32 arg0, f32 farg0);
extern s32 func_0023C710(s32 arg0);
extern s32 func_0023C798(s32 arg0, s32 arg1);
extern s32 func_0023E520(s32 arg0);
extern s32 func_00210E18(s32 arg0);
extern s32 BtlPad_Test4C(s32 arg0, s32 arg1);
extern s32 BtlPad_Test48(s32 arg0, s32 arg1);
extern void func_002174D8(s32 arg0, s32 arg1);
extern s32 func_002174B8(s32 arg0);
extern s32 func_0023F420(s32 arg0);
extern f32 D_00385B84;
extern f32 D_00385B88;
extern f32 D_00385B8C;
extern f32 D_00385B90;
extern f32 D_00385B94;
extern f32 D_00385B98;
extern f32 D_00385B9C;
extern f32 D_00385BA0;
extern f32 D_00385BA4;

/* Picks the next animation id for the move chain: state 0x39 (hold) and the finish states
   0x58/0x5B/0x5E/0x61/0x64/0x67 (jump table); every other state returns -1. */
s32 func_00219558(s32 obj) {
    f32 prog = func_001FA318(obj);
    s32 state = BtlObjXf_Update(obj);
    s32 n;
    s32 v;

    switch (state) {
    case 0x39:
        if (!func_00211310(obj, 2, 1)) {
            return -1;
        }
        BtlAnim_SetBlend(obj, D_00385B84);
        if (*(s32 *)((u8 *)obj + 0x9C0) >= 0) {
            v = func_0023C798(obj, 0x200);
            if (v != -1) {
                return v;
            }
        }
        return func_0023C710(obj);
    case 0x58:
    case 0x5B:
    case 0x5E:
    case 0x61:
    case 0x64:
    case 0x67:
        n = func_0023E520(obj);
        if (n >= 22 && n < 27) {
            if (func_00211310(obj, 4, 2) && func_00210E18(obj) == 0x9A) {
                if (BtlPad_Test4C(obj, 3)) {
                    func_002174D8(obj, 14);
                }
                if (D_00385B88 < prog && prog < D_00385B8C) {
                    if (func_002174B8(obj) == 14) {
                        BtlAnim_SetBlend(obj, D_00385B90);
                        return func_002174B8(obj);
                    }
                }
            }
        } else if (n >= 27 && n < 32) {
            if (func_00211310(obj, 4, 2) && func_00210E18(obj) == 0x99) {
                if ((func_0023F420(obj) & 0x80) && BtlPad_Test4C(obj, 3)) {
                    func_002174D8(obj, 16);
                }
                if (!BtlPad_Test48(obj, 7)) {
                    BtlPad_Test4C(obj, 2);
                    if (func_0023F420(obj) & 0x10) {
                        if (BtlPad_Test4C(obj, 1)) {
                            func_002174D8(obj, 0x70);
                        }
                    }
                }
                if (D_00385B94 < prog && prog < D_00385B98) {
                    v = func_002174B8(obj);
                    if (v == 0x70 || v == 16 || v == 0x8D) {
                        BtlAnim_SetBlend(obj, D_00385B9C);
                        return func_002174B8(obj);
                    }
                }
            }
        }
        func_002174D8(obj, func_0023C798(obj, 3));
        if (!func_00211310(obj, 2, 1)) {
            return -1;
        }
        BtlAnim_SetBlend(obj, D_00385BA0);
        v = func_002174B8(obj);
        if (v < 0x50 && v >= 0x49) {
            BtlAnim_SetBlend(obj, D_00385BA4);
            return func_002174B8(obj);
        }
        return func_0023C710(obj);
    default:
        return -1;
    }
}
