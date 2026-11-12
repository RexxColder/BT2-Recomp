#include "common.h"

void func_001B8E80(s32 arg0, s32 arg1, f32 farg0) {
    *(f32 *)(arg0 + 0x00) = *(f32 *)(arg0 + 0x00) + *(f32 *)(arg1 + 0x00) * farg0;
    *(f32 *)(arg0 + 0x04) = *(f32 *)(arg0 + 0x04) + *(f32 *)(arg1 + 0x04) * farg0;
    *(f32 *)(arg0 + 0x08) = *(f32 *)(arg0 + 0x08) + *(f32 *)(arg1 + 0x08) * farg0;
    *(f32 *)(arg0 + 0x0C) = *(f32 *)(arg0 + 0x0C) + *(f32 *)(arg1 + 0x0C) * farg0;
    *(f32 *)(arg0 + 0x10) = *(f32 *)(arg0 + 0x10) + *(f32 *)(arg1 + 0x10) * farg0;
    *(f32 *)(arg0 + 0x14) = *(f32 *)(arg0 + 0x14) + *(f32 *)(arg1 + 0x14) * farg0;
}
