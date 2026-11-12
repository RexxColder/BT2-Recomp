#include "common.h"

void func_001AEF80(s32 arg0, s32 arg1);
s32 func_003126C8(s32 arg0, s32 arg1);
void *memset(void *arg0, s32 arg1, u32 arg2);

void func_001AE3E8(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, f32 fa, f32 fb, f32 fc) {
    s32 sp[24];
    u8 *b;
    u8 *s2;
    f32 f0;
    s32 s0;

    b = (u8 *)sp;
    memset(sp, 0, 0x60);
    s2 = *(u8 **)(arg0 + 0x38);
    func_003126C8((s32)(b + 0x10), arg2);
    s0 = (arg1 == 0) ? 0 : (arg3 & 0xFF);
    b[0x48] = (u8)s0;
    if (*(u8 *)(s2 + 0x5A) != 0) {
        f0 = 15.0f;
    } else {
        f0 = -15.0f;
    }
    *(f32 *)(b + 0x3C) = fa;
    *(f32 *)(b + 0x40) = fb;
    *(f32 *)(b + 0x44) = fc * 30.0f;
    *(s32 *)(b + 0x50) = arg1;
    *(f32 *)(b + 0x38) = f0;
    func_001AEF80((s32)arg0, (s32)sp);
    arg0[1] = 2;
}
