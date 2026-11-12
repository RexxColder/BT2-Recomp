#include "common.h"

u8 *Battle_GetSetup(u8 *arg0);
s32 func_001F9898(u8 *arg0);
s32 func_00211310(u8 *arg0, s32 arg1, s32 arg2);
s32 func_00218128(u8 *arg0, s32 arg1);
u32 func_0023E520(u8 *arg0);
s32 BtlObjAnim_QueryEvent(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);

/* 0x0023EBD8: damage-like value = setup[2] * pct / 100, reduced by 30 percent in one case, divided by an event count. */
s32 func_0023EBD8(u8 *obj) {
    f32 val;
    s32 ev;

    val = (f32)*(s32 *)(Battle_GetSetup(obj) + 8);
    val = (val * (f32)func_001F9898(obj)) / 100.0f;
    if (func_00211310(obj, 0, 0x800) != 0) {
        if (func_00218128(obj, 4) != 0 && func_0023E520(obj) < 10) {
            val = val - (val * 3.0f) / 10.0f;
        }
    }
    ev = BtlObjAnim_QueryEvent(*(u8 **)(obj + 0x1530), 1, 0, 2);
    if (ev > 0) {
        val = val / (f32)ev;
    }
    return (s32)val;
}
