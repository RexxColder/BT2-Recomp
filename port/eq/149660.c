#include "common.h"

extern s32 BtlScene_IsCharStopped(s32 a0);
extern void func_00129C38(u8 *dst, u8 *src);

s32 func_00149660(u8 *obj) {
    u8 *data;
    s32 r;
    u32 flags;

    data = *(u8 **)(obj + 0x38);
    r = BtlScene_IsCharStopped(**(s32 **)(data + 0x90));
    if (r != 0) {
        return r;
    }
    *(u32 *)data &= ~0x10u;
    flags = *(u16 *)(obj + 8);
    if (flags & 1) {
        func_00129C38(data + 0x60, obj + 0x10);
        *(u32 *)data |= 0x10;
        flags = *(u16 *)(obj + 8);
    }
    if (flags & 4) {
        *(u32 *)data |= 1;
        return *(u32 *)data;
    }
    return 0;
}
