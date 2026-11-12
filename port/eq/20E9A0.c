#include "m2c_macros.h"

extern s32 func_003126C8(s32 arg0, s32 arg1);

void func_0020E9A0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 *s0;

    s0 = arg0 + (arg3 << 4);
    func_003126C8((s32)(s0 + 0x7B0), arg1);
    func_003126C8((s32)(s0 + 0x830), arg2);
    *(s32 *)(arg0 + 0x8B0) = *(s32 *)(arg0 + 0x8B0) | (1 << arg3);
    func_003126C8((s32)(arg0 + 0x820), arg1);
    func_003126C8((s32)(arg0 + 0x8A0), arg2);
    *(s32 *)(arg0 + 0x8B0) = *(s32 *)(arg0 + 0x8B0) | 0x80;
}
