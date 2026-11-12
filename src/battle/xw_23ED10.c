#include "common.h"

s32 Battle_GetSetup(s32 arg0);
s32 BtlObjAnim_QueryEvent(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

// Returns the setup word at +0x10 divided by BtlObjAnim_QueryEvent(arg0->+0x1530, 1, 0, 2) when that is positive.
s32 func_0023ED10(s32 arg0) {
    s32 setup = Battle_GetSetup(arg0);
    s32 num = *(s32 *)((u8 *)setup + 0x10);
    s32 v = BtlObjAnim_QueryEvent(*(s32 *)((u8 *)arg0 + 0x1530), 1, 0, 2);
    if (v > 0) {
        num = num / v;
    }
    return num;
}
