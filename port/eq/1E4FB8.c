#include "common.h"

void func_001E5098(u8 *arg0, s32 arg1, s32 arg2, f32 *arg3, f32 *arg4, f32 farg0);
f32 func_001E52A8(u8 *arg0);

/* cvt.w.s: truncates toward zero. */
/* cvt.w.s truncates toward zero (saturating): plain cast */
static s32 cvt_w_s(f32 x) {
    return (s32)x;
}

s32 func_001E4FB8(u8 *arg0, u8 *arg1) {
    u8 buf[0x20];
    s32 flags;

    if (arg0 == NULL) {
        return 0;
    }
    flags = *(s32 *)(arg1 + 0x164);
    if ((flags & 1) == 0 || (flags & 2) != 0) {
        return 0;
    }
    *(f32 *)(buf + 0x00) = *(f32 *)(arg1 + 0x140);
    *(f32 *)(buf + 0x04) = *(f32 *)(arg1 + 0x144);
    *(f32 *)(buf + 0x08) = *(f32 *)(arg1 + 0x148);
    *(f32 *)(buf + 0x0C) = *(f32 *)(arg1 + 0x14C);
    *(f32 *)(buf + 0x10) = *(f32 *)(arg1 + 0xE0);
    *(f32 *)(buf + 0x14) = *(f32 *)(arg1 + 0xE4);
    *(f32 *)(buf + 0x18) = *(f32 *)(arg1 + 0xE8);
    *(s32 *)(buf + 0x1C) = 0;
    func_001E5098(arg1, cvt_w_s(*(f32 *)(arg0 + 0x21C8)),
                  cvt_w_s(*(f32 *)(arg1 + 0x70)) + *(s32 *)(arg1 + 0x1A8),
                  (f32 *)(buf + 0x10), (f32 *)buf, *(f32 *)(arg1 + 0x88));
    *(f32 *)(arg0 + 0x21C4) = func_001E52A8(arg0);
    *(s32 *)(arg1 + 0x164) = *(s32 *)(arg1 + 0x164) | 2;
    return 1;
}
