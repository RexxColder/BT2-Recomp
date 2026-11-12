#include "common.h"

void func_002C5718(s32 arg0, s32 arg1, s32 arg2, u8 *arg3) {
    s32 w;
    s32 h;
    s32 cw;
    s32 ch;
    s32 cx;
    s32 cy;
    s32 base;

    w = arg1 + 0xF;
    if (w < 0) {
        w = arg1 + 0x1E;
    }
    w = w >> 4;
    cw = w * 0x10 + 0x3F;
    if (cw < 0) {
        cw = w * 0x10 + 0x7E;
    }
    cw = cw >> 6;
    ch = w * 8 + 0x3F;
    if (ch < 0) {
        ch = w * 8 + 0x7E;
    }
    ch = ch >> 6;
    h = arg2 + 0xF;
    if (h < 0) {
        h = arg2 + 0x1E;
    }
    h = h >> 4;
    *(s16 *)(arg3 + 0xE) = (s16)(cw << 6);
    *(s16 *)(arg3 + 0xC) = (s16)(ch << 6);
    base = arg0 + ((cw * h) << 0xA);
    *(s32 *)(arg3 + 0x8) = arg0;
    *(s32 *)(arg3 + 0x0) = base;
    *(s32 *)(arg3 + 0x4) = base + ((ch * h) << 9);
}
