#include "common.h"

extern f32 D_003866C0;
extern f32 D_003866C4;
extern f32 D_003866C8;

s32 func_0023C798(u8 *arg0, s32 arg1);
void func_002174D8(u8 *arg0, s32 arg1);
s32 BtlPad_Test4C(u8 *arg0, s32 arg1);
s32 BtlPad_Test48(u8 *arg0, s32 arg1);
s32 func_0023F948(u8 *arg0, s32 arg1);
s32 func_00217518(s32 arg0, s32 arg1);
f32 func_001FA318(u8 *arg0);
s32 func_002174B8(u8 *arg0);
void BtlAnim_SetBlend(u8 *arg0, f32 farg0);
s32 func_0023C710(u8 *arg0);
s32 func_00211310(u8 *arg0, s32 arg1, s32 arg2);

s32 func_0022DB30(u8 *arg0) {
    s32 r1;
    s32 w;
    s32 v;
    f32 f;

    r1 = func_0023C798(arg0, 0x133);
    func_002174D8(arg0, r1);

    if (BtlPad_Test4C(arg0, 1) != 0 && BtlPad_Test48(arg0, 8) == 0) {
        w = func_0023F948(arg0, 0);
        if ((u32)w < 6) {
            switch (w) {
                case 0:
                    func_002174D8(arg0, 0x6C);
                    break;
                case 1:
                    func_002174D8(arg0, func_00217518(0x1B, 0x6C));
                    break;
                case 2:
                    func_002174D8(arg0, 0x6A);
                    break;
                case 3:
                    func_002174D8(arg0, func_00217518(0x1B, 0x6A));
                    break;
                case 4:
                    func_002174D8(arg0, 0x71);
                    break;
                case 5:
                    func_002174D8(arg0, func_00217518(0x1B, 0x71));
                    break;
            }
        }
    }

    f = func_001FA318(arg0);
    if (D_003866C0 < f) {
        v = func_002174B8(arg0);
        if (v != -1) {
            BtlAnim_SetBlend(arg0, D_003866C4);
            return func_002174B8(arg0);
        }
    }

    if (func_00211310(arg0, 2, 1) == 0) {
        return -1;
    }
    BtlAnim_SetBlend(arg0, D_003866C8);
    return func_0023C710(arg0);
}
