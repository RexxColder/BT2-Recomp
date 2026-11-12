#include "common.h"

/* 0x001B8C08 EftPtcl3_PickTexture: copies the 16-byte entries arg2 and arg3 of the table arg1 into arg0 + 0x260 /
 * +0x268 (entry arg2) and +0x270 / +0x278 (entry arg3), stores arg3 at +0x40. */
void EftPtcl3_PickTexture(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3) {
    *(s64 *)(arg0 + 0x260) = *(s64 *)(arg1 + arg2 * 0x10);
    *(s64 *)(arg0 + 0x268) = *(s64 *)(arg1 + arg2 * 0x10 + 8);
    *(s64 *)(arg0 + 0x270) = *(s64 *)(arg1 + arg3 * 0x10);
    *(s32 *)(arg0 + 0x40) = arg3;
    *(s64 *)(arg0 + 0x278) = *(s64 *)(arg1 + arg3 * 0x10 + 8);
}
