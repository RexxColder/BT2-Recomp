#include "common.h"

extern u8 *D_003876A0;
extern u8 *func_001F3758(u8 *arg0);
extern void func_0014EAE8(u8 *arg0, u8 *arg1);

void func_00165650(u8 *arg0, u8 *arg1) {
    u8 *other = func_001F3758(arg0);
    u8 *dst = *(u8 **)(arg0 + 0x38);
    u8 *src = *(u8 **)(other + 0x38);
    u8 *info;

    __builtin_memset(dst, 0, 0xB10);
    *(u8 **)(dst + 0xB0) = arg1;
    info = *(u8 **)(arg1 + 0x24);
    *(f32 *)(dst + 0x10) = *(f32 *)(info + 8);
    *(f32 *)(dst + 0x14) = *(f32 *)(info + 4);
    *(f32 *)(dst + 0x18) = *(f32 *)(info + 4);
    func_0014EAE8(src, dst + 0xB4);
    if ((*(s64 *)(D_003876A0 + 0x4D8) & 2) == 0) {
        if (**(s32 **)(dst + 0xB0) == 0) {
            *(u32 *)dst |= 0x200;
        }
    }
}
