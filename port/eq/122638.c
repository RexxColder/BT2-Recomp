#include "common.h"

void *BtlChar_GetPos(s32 arg0);
s32 func_00126040(s32 arg0);
f32 func_0029DFD0(s32 arg0);

s32 func_00122638(s32 arg0) {
    f32 temp_f20;
    u8 *temp_s1;
    u8 *temp_s2;
    u8 *pos;

    temp_s2 = (u8 *)arg0 + 0xFE0;
    temp_s1 = (u8 *)BtlChar_GetPos(func_00126040(arg0));
    pos = (u8 *)BtlChar_GetPos(func_00126040(arg0));
    temp_f20 = (*(f32 *)(temp_s1 + 0xC0) + fabsf(*(f32 *)(pos + 0xC4))) * 0.25f;
    if (!(func_0029DFD0((s32)((u8 *)BtlChar_GetPos(func_00126040(arg0)) + 0x50)) < temp_f20)) {
        *(s32 *)(temp_s2 + 0x38) = 0;
    } else {
        *(s32 *)(temp_s2 + 0x38) = *(s32 *)(temp_s2 + 0x38) + 1;
    }
    return (*(s32 *)(temp_s2 + 0x38) < 0x1F) == 0;
}
