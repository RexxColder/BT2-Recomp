#include "common.h"

s32 func_001F3758(s32 arg0);
void func_0014EAE8(s32 arg0, s32 arg1);

void func_0016F8B8(s32 arg0, s32 arg1) {
    u8 *obj = *(u8 **)(arg0 + 0x38);
    u8 *other = *(u8 **)(func_001F3758(arg0) + 0x38);
    u8 *src;

    __builtin_memset(obj, 0, 0x47A0);
    *(s32 *)(obj + 0xB0) = arg1;
    src = *(u8 **)(arg1 + 0x24);
    *(f32 *)(obj + 0x14) = *(f32 *)(src + 8);
    *(f32 *)(obj + 0x18) = *(f32 *)(src + 4);
    *(f32 *)(obj + 0x1C) = *(f32 *)(src + 4);
    func_0014EAE8((s32)other, (s32)(obj + 0xB4));
}
