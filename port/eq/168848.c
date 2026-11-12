#include "common.h"

s32 func_0014EAE8(s32 arg0, s32 arg1);
s32 func_00168158(s32 arg0);
u8 *func_001F3758(s32 arg0, s32 arg1);
void memset(void *arg0, s32 arg1, u32 arg2);

void func_00168848(u8 *arg0, u8 *arg1) {
    u8 *s0;
    u8 *v0;
    s32 s3;
    f32 f1;

    s0 = *(u8 **)(arg0 + 0x38);
    s3 = *(s32 *)(func_001F3758((s32)arg0, (s32)arg1) + 0x38);
    memset(s0, 0, 0xB50);
    *(u8 **)(s0 + 0x120) = arg1;
    v0 = *(u8 **)(arg1 + 0x24);
    *(f32 *)(s0 + 0x18) = *(f32 *)(v0 + 8);
    f1 = *(f32 *)(v0 + 4);
    *(f32 *)(s0 + 0x1C) = f1;
    *(f32 *)(s0 + 0x24) = f1;
    *(f32 *)(s0 + 0x20) = *(f32 *)(v0 + 4);
    func_00168158((s32)arg0);
    func_0014EAE8(s3, (s32)(s0 + 0x124));
}
