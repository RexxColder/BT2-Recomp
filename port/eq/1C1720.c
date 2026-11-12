#include "common.h"

u8 *func_001C14A0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

u8 *func_001C1720(u8 *arg0, s32 arg1, s16 arg2, s16 arg3, f32 fa, f32 fb, f32 fc, f32 fd) {
    u8 *r = func_001C14A0(arg0, arg1, arg2, arg3, 5);

    if (r != 0) {
        *(f32 *)(r + 0x18) = fd;
        *(f32 *)(r + 0xC) = fa;
        *(f32 *)(r + 0x10) = fb;
        *(f32 *)(r + 0x14) = fc;
    }
    return r;
}
