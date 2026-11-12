#include "common.h"

s32 BtlCharApi_ObjGetParamFlags0(s32 arg0);
void func_0014EAE8(void *arg0, void *arg1, s32 arg2);
void *func_001F3758(void *arg0);
s32 func_0020B3D0(s32 arg0);
void *memset(void *arg0, s32 arg1, u32 arg2);

void func_0016C2F8(u8 *arg0, u8 *arg1) {
    u8 *s0;
    u8 *s2;
    u8 *v0;

    s0 = *(u8 **)(arg0 + 0x38);
    s2 = *(u8 **)((u8 *)func_001F3758(arg0) + 0x38);
    memset(s0, 0, 0xD40);
    *(u8 **)(s0 + 0xB0) = arg1;
    v0 = *(u8 **)(arg1 + 0x24);
    *(f32 *)(s0 + 0x1C) = *(f32 *)(v0 + 8);
    *(f32 *)(s0 + 0x20) = *(f32 *)(v0 + 4);
    if (*(s32 *)(*(u8 **)(arg1 + 0x20)) == 0x134) {
        *(s32 *)(s0 + 0x1C) = 0;
    }
    if (*(u8 *)(s2 + 0x1E80) != 0) {
        func_0014EAE8(s2, s0 + 0xB4, 0x134);
    }
    if (BtlCharApi_ObjGetParamFlags0(func_0020B3D0(*(s32 *)(*(u8 **)(s0 + 0xB0)))) & 0x80) {
        *(s32 *)s0 = *(s32 *)s0 | 0x4000;
    }
}
