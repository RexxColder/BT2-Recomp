#include "common.h"

u8 *func_001F3758(s32 arg0);
void func_0014EAE8(s32 arg0, s32 arg1);
void *memset(void *arg0, s32 arg1, u32 arg2);

void func_00148F90(u8 *arg0, u8 *arg1) {
    u8 *p;
    u8 *s2;
    u8 *v;
    s32 s0;

    p = func_001F3758((s32)arg0);
    s2 = *(u8 **)(arg0 + 0x38);
    s0 = *(s32 *)(p + 0x38);
    memset(s2, 0, 0xA90);
    *(u8 **)(s2 + 0x90) = arg1;
    v = *(u8 **)(arg1 + 0x24);
    *(f32 *)(s2 + 0x14) = *(f32 *)(v + 0x8);
    *(f32 *)(s2 + 0x18) = *(f32 *)(v + 0x4);
    func_0014EAE8(s0, (s32)(s2 + 0x94));
    if (*(s32 *)(*(u8 **)(*(u8 **)(s2 + 0x90) + 0x20)) == 0x15D) {
        *(s32 *)(s2 + 0x0) = *(s32 *)(s2 + 0x0) | 0x400;
    }
}
