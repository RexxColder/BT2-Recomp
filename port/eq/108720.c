#include "common.h"

u8 **func_00107848(s32 arg0);

s64 BtlText_GetTex0(s32 arg0) {
    u8 **pp;
    u8 *base;
    u8 *t;
    u64 r;

    pp = func_00107848(arg0);
    base = *pp;
    t = *(u8 **)(base + 0x10) + ((u32)arg0 << 6);
    r = (u64)*(s64 *)(t + 0x30);
    r |= (u64)(s64)(s32)((u32)*(s32 *)(t + 0x24) + 0x2A00U) << 37;
    r |= (u64)(s64)(s32)((u32)*(s32 *)(t + 0x20) + 0x2A40U);
    r |= (u64)0x8000 << 19;
    return (s64)r;
}
