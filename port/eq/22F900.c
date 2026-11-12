#include "common.h"

s32 func_00211310(u8 *arg0, s32 arg1, s32 arg2);
s32 func_00217488(u8 *arg0);
f32 func_001FA318(u8 *arg0);
void BtlAnim_SetBlend(u8 *arg0, f32 farg0);
s32 func_0023C710(u8 *arg0);
extern f32 D_003867CC;
extern f32 D_003867D0;
extern f32 D_003867D4;

/* 0x0022F900: v = func_00217488(obj). v == 0x28 and D_003867CC < func_001FA318(obj): blend D_003867D0, then the common tail.
 * Else func_00211310(obj, 2, 1) == 0 -> -1; blend D_003867D4; switch on v-0x27: 0/2/3 -> func_0023C710(obj); 1 -> the
 * common tail; 4/5 -> 16; else -1. Common tail: func_00211310(obj, 0, 1) == 0 ? 13 : 14. */
s32 func_0022F900(u8 *arg0) {
    s32 v;
    s32 r;
    f32 f;

    v = func_00217488(arg0);
    if (v == 0x28) {
        f = func_001FA318(arg0);
        if (D_003867CC < f) {
            BtlAnim_SetBlend(arg0, D_003867D0);
            goto common_tail;
        }
    }
    if (func_00211310(arg0, 2, 1) == 0) {
        return -1;
    }
    BtlAnim_SetBlend(arg0, D_003867D4);
    v = func_00217488(arg0);
    if ((u32)(v - 0x27) < 6) {
        switch (v - 0x27) {
        case 0:
        case 2:
        case 3:
            return func_0023C710(arg0);
        case 1:
            goto common_tail;
        case 4:
        case 5:
            return 16;
        }
    }
    return -1;
common_tail:
    r = func_00211310(arg0, 0, 1);
    return (r == 0) ? 13 : 14;
}
