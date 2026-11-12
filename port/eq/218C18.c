#include "common.h"

extern f32 D_00385B50;
extern f32 D_00385B54;
extern f32 D_00385B58;
extern f32 D_00385B5C;
extern f32 D_00385B60;
extern f32 D_00385B64;
extern f32 D_00385B68;
extern f32 D_00385B6C;

s32 func_0023BDA8(s32 arg0, s32 arg1);
void func_002174D8(s32 arg0, s32 arg1);
s32 func_0023C798(s32 arg0, s32 arg1);
s32 BtlPad_Test4C(s32 arg0, s32 arg1);
s32 BtlPad_Test48(s32 arg0, s32 arg1);
s32 func_0023F918(s32 arg0);
s32 BtlObjXf_Update(s32 arg0);
s32 func_0023F420(s32 arg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 func_002174B8(s32 arg0);
s32 func_0023C710(s32 arg0);
f32 func_001FA318(s32 arg0);
s32 BtlAnim_SetBlend(s32 arg0, f32 farg0);

/* Chooses the next animation for a character state (arg0 = object): starts with two default
   animation requests and a pad-driven one, then picks per BtlObjXf_Update state. Returns the
   animation id or -1. */
s32 func_00218C18(s32 arg0) {
    s32 state;
    s32 anim;
    s32 first;
    u8 *obj = (u8 *)arg0;

    func_002174D8(arg0, func_0023BDA8(arg0, 0x1A800));
    func_002174D8(arg0, func_0023C798(arg0, 0x4F3));

    if (BtlPad_Test4C(arg0, 1) != 0 && BtlPad_Test48(arg0, 8) == 0 &&
        (u32)((*(s32 *)(obj + 0x998) - 1) % 5) < 4) {
        s32 kind = func_0023F918(arg0);

        anim = -1;
        if (kind == 1) {
            anim = 0x6A;
        } else if (kind < 2) {
            if (kind == 0) {
                anim = 0x6C;
            }
        } else if (kind == 2) {
            anim = 0x71;
        }
        if (anim >= 0) {
            func_002174D8(arg0, anim);
        }
    }

    state = BtlObjXf_Update(arg0);
    if (state == 0x47) {
        if ((func_0023F420(arg0) & 0x20) != 0 && func_00211310(arg0, 4, 2) != 0) {
            if (BtlPad_Test4C(arg0, 3) != 0) {
                func_002174D8(arg0, 0x17);
            }
            if (func_001FA318(arg0) > 0.5f && func_002174B8(arg0) == 0x17) {
                BtlAnim_SetBlend(arg0, D_00385B54);
                return func_002174B8(arg0);
            }
        }
        if (func_00211310(arg0, 2, 1) != 0) {
            BtlAnim_SetBlend(arg0, D_00385B58);
            return func_0023C710(arg0);
        }
        return -1;
    }
    if (state < 0x48) {
        if (state == 0 || state == 0x32) {
            first = func_002174B8(arg0);
            if (first != -1) {
                BtlAnim_SetBlend(arg0, D_00385B64);
                return func_002174B8(arg0);
            }
            anim = func_0023BDA8(arg0, 0x718);
            if (anim != first) {
                BtlAnim_SetBlend(arg0, D_00385B68);
                return anim;
            }
            if (func_00211310(arg0, 2, 0x200) != 0) {
                return -1;
            }
            BtlAnim_SetBlend(arg0, D_00385B6C);
            return func_0023C710(arg0);
        }
    } else if (state == 0x4C) {
        if ((func_0023F420(arg0) & 0x40) != 0 && func_00211310(arg0, 4, 2) != 0) {
            if (BtlPad_Test48(arg0, 0xC) != 0 && BtlPad_Test4C(arg0, 2) != 0) {
                func_002174D8(arg0, 0x1E);
            }
            if (func_001FA318(arg0) > 0.5f && func_002174B8(arg0) == 0x1E) {
                BtlAnim_SetBlend(arg0, D_00385B5C);
                return func_002174B8(arg0);
            }
        }
        if (func_00211310(arg0, 2, 1) != 0) {
            BtlAnim_SetBlend(arg0, D_00385B60);
            return func_0023C710(arg0);
        }
        return -1;
    }

    if (func_00211310(arg0, 2, 1) == 0) {
        return -1;
    }
    if (func_002174B8(arg0) == -1) {
        return -1;
    }
    switch (func_002174B8(arg0)) {
    case 0x4A:
    case 0x4B:
    case 0x4C:
    case 0x4D:
    case 0x4E:
    case 0x4F:
        *(s32 *)(obj + 0x147C) += 1;
        break;
    case 0x56:
        *(s32 *)(obj + 0x1480) += 1;
        break;
    case 0x57:
        *(s32 *)(obj + 0x1484) += 1;
        break;
    case 0x66:
    case 0x67:
    case 0x68:
        *(s32 *)(obj + 0x1498) += 1;
        break;
    case 0x6A:
        *(s32 *)(obj + 0x148C) += 1;
        break;
    case 0x6C:
        *(s32 *)(obj + 0x1488) += 1;
        break;
    case 0x71:
        *(s32 *)(obj + 0x1490) += 1;
        break;
    case 0x7F:
        *(s32 *)(obj + 0x1494) += 1;
        break;
    default:
        break;
    }
    BtlAnim_SetBlend(arg0, D_00385B50);
    return func_002174B8(arg0);
}
