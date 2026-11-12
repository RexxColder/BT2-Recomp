#include "common.h"

s32 func_003126C8(void *a0, s32 a1);
s32 func_001E66A0(void *a0);
void *memset(void *arg0, s32 arg1, u32 arg2);

s32 func_001E70B0(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, f32 f12, s32 arg6, s32 arg7, s32 arg8) {
    u8 frame[0x40];
    u8 *s0;
    s32 r;

    if (*(s32 *)arg0 != 0) {
        return 0;
    }
    s0 = frame + 0x20;
    *(s32 *)(frame + 0) = arg1;
    *(s32 *)(frame + 4) = arg2;
    *(s32 *)(frame + 8) = arg3;
    *(s32 *)(frame + 0xC) = arg4;
    *(f32 *)(frame + 0x10) = f12;
    memset(s0, 0, 0x10);
    *(s32 *)(frame + 0x30) = arg7;
    *(s32 *)(frame + 0x34) = arg8;
    func_003126C8(s0, arg6);
    r = func_001E66A0(frame);
    *(s32 *)arg0 = r;
    return r != 0;
}
