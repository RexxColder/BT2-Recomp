#include "common.h"

extern s32 func_001F3758(s32 a0);
extern void func_0014EAE8(s32 a0, u8 *a1);
extern void func_0016A408(u8 *a0);

void func_0016AB98(u8 *obj, u8 *src) {
    u8 *res;
    u8 *a;
    u8 *b;
    u8 *vec;

    res = (u8 *)func_001F3758((s32)obj);
    a = *(u8 **)(obj + 0x38);
    b = *(u8 **)(res + 0x38);
    __builtin_memset(a, 0, 0xB60);
    *(u8 **)(a + 0xB0) = src;
    vec = *(u8 **)(src + 0x24);
    *(f32 *)(a + 0x14) = *(f32 *)(vec + 8);
    *(f32 *)(a + 0x18) = *(f32 *)(vec + 4);
    *(f32 *)(a + 0x1C) = *(f32 *)(vec + 4);
    func_0014EAE8((s32)b, a + 0xB4);
    func_0016A408(obj);
}
