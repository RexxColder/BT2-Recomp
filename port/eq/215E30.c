#include "common.h"

void *BtlChar_GetPos(s32 arg0);

void func_00215E30(s32 arg0, f32 farg0, f32 farg1) {
    *(f32 *)((u8 *)BtlChar_GetPos(arg0) + 0xB0) = farg1;
    *(f32 *)((u8 *)BtlChar_GetPos(arg0) + 0xB4) = farg0;
    *(f32 *)((u8 *)BtlChar_GetPos(arg0) + 0x14) = farg0;
}
