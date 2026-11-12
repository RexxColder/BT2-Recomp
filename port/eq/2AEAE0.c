#include "common.h"

/* GUESS arity: func_002B0DB0 gets (arg0, 0x200) and (arg0, 0x05000000); ctx.h says 0 */
s32 func_002B0DB0(s32 arg0, s32 arg1);
void BtlMenu_EndDraw(f32 arg0, s32 arg1);
extern f32 D_003873DC;

s32 func_002AEAE0(s32 arg0) {
    if (func_002B0DB0(arg0, 0x200) == 0) {
        BtlMenu_EndDraw(D_003873DC, arg0);
        return (func_002B0DB0(arg0, 0x05000000) == 0) ? 1 : 2;
    }
    return -1;
}
