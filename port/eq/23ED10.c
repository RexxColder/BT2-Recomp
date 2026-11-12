#include "common.h"

extern u8 *Battle_GetSetup(s32 arg0);
extern s32 BtlObjAnim_QueryEvent(s32 obj, s32 a1, s32 a2, s32 a3);

s32 func_0023ED10(u8 *self) {
    s32 value;
    s32 divisor;

    value = *(s32 *)(Battle_GetSetup((s32)self) + 0x10);
    divisor = BtlObjAnim_QueryEvent(*(s32 *)(self + 0x1530), 1, 0, 2);
    if (divisor > 0) {
        value = value / divisor;
    }
    return value;
}
