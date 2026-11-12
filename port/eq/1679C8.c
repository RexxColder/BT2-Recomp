#include "common.h"

void func_0014EAE8(s32 arg0, void *arg1, s32 arg2, s32 arg3);
void *func_001F3758(void *arg0);
void *memset(void *arg0, s32 arg1, u32 arg2);

void func_001679C8(u8 *arg0, u8 *arg1) {
    u8 *s2;
    u8 *v0;
    s32 s0;
    s32 a2;
    f32 f1;

    s2 = *(u8 **)(arg0 + 0x38);
    s0 = *(s32 *)((u8 *)func_001F3758(arg0) + 0x38);
    memset(s2, 0, 0xAB0);
    *(u8 **)(s2 + 0xB0) = arg1;
    v0 = *(u8 **)(arg1 + 0x24);
    *(f32 *)(s2 + 0x10) = *(f32 *)(v0 + 8);
    f1 = *(f32 *)(v0 + 4);
    *(f32 *)(s2 + 0x14) = f1;
    *(f32 *)(s2 + 0x1C) = f1;
    *(f32 *)(s2 + 0x18) = *(f32 *)(v0 + 4);
    a2 = *(s32 *)(*(u8 **)(arg1 + 0x20));
    if (a2 < 0x10D) {
        if (!((a2 < 0x10B) && (a2 != 0x3A))) {
            *(s32 *)s2 = *(s32 *)s2 | 0x200;
        }
    } else if (a2 == 0x14F) {
        *(s32 *)s2 = *(s32 *)s2 | 0x200;
    }
    func_0014EAE8(s0, s2 + 0xB4, a2, 0x14F);
}
