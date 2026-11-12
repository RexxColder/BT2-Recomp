#include "common.h"

s32 func_003126C8(s32 arg0, s32 arg1);
extern u8 gGfxLens[] __attribute__((section(".data")));

s32 GfxLens_Start(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 farg0) {
    s32 s0 = 0;
    u8 *v1 = gGfxLens;

    for (;;) {
        if (*(s32 *)(v1 + 0x10) == 0) {
            *(s32 *)(v1 + 0x10) = arg1;
            *(s32 *)(v1 + 0x18) = arg2;
            *(s32 *)(v1 + 0x20) = arg3;
            *(f32 *)(v1 + 0x1C) = farg0;
            *(s32 *)(v1 + 0x14) = arg1;
            func_003126C8((s32)v1, arg0);
            return s0;
        }
        s0 += 1;
        v1 += 0x30;
        if (s0 >= 8) {
            return -1;
        }
    }
}
