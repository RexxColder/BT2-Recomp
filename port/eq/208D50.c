#include "common.h"

u8 *BtlChar_GetPos(s32 arg0);
s32 func_00211288(s32 arg0);
u8 *func_002B1DD0(u32 arg0, s32 arg1);
extern s32 D_00387930;
extern s32 D_00387E18;

f32 func_00208D50(u32 arg0) {
    s32 a1 = arg0 < 2U;

    if (D_00387930 != 0 && a1 != 0) {
        return *(f32 *)(BtlChar_GetPos(func_00211288((s32)arg0)) + 0xC4);
    }
    if (D_00387E18 != 0 && arg0 < 3U) {
        return *(f32 *)(func_002B1DD0(arg0, a1) + 0x158);
    }
    return 0.0f;
}
