#include "common.h"

s32 Ot_Align64(s32 arg0);
s32 func_0028BAA8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern u8 *D_0038790C;

s32 BtlPool_Alloc(s32 arg0, s32 arg1) {
    s32 align;
    s32 bit;
    u8 *p;
    s32 r;

    align = Ot_Align64(arg1);
    bit = 1 << ((arg0 + 1) & 31);
    p = D_0038790C + (arg0 << 4);
    if (*(s32 *)(D_0038790C + 0x68) & bit) {
        r = *(s32 *)(p + 0x4);
        *(s32 *)(p + 0x4) = r + align;
        *(s32 *)(p + 0xC) = *(s32 *)(p + 0xC) + align;
    } else {
        *(s32 *)(p + 0xC) = *(s32 *)(p + 0xC) + align;
        r = func_0028BAA8(arg1, (s32)p, arg0 + 1, align);
    }
    return r;
}
