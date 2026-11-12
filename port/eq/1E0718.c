#include "common.h"

f32 floorf(f32 arg0);
void func_001E1BC8(u8 *arg0, s32 arg1, s32 arg2, void *arg3, void *arg4, f32 arg5);

void func_001E0718(u8 *arg0, s32 arg1, s32 arg2) {
    s32 sp[8];
    u8 *s0;
    u8 *s1;
    s32 i;
    s32 a1;
    s32 a2;
    u32 idx;
    f32 f21;
    f32 f12;
    f32 f20;
    f32 f0;
    f32 f1;

    idx = (u8)arg1;
    if (idx < *(u8 *)(arg0 + 0x10F00)) {
        s1 = arg0 + 0x21E0 * idx;
        s0 = s1 + 0x10;
        f21 = (f32)arg2;
        if (*(s32 *)(s1 + 0x1B0) > 0) {
            i = 0;
            do {
                i++;
                f12 = *(f32 *)(s0 + 0x70) / *(f32 *)(s1 + 0x21D4);
                *(f32 *)&sp[0] = *(f32 *)(s0 + 0x140);
                *(f32 *)&sp[1] = *(f32 *)(s0 + 0x144);
                *(f32 *)&sp[2] = *(f32 *)(s0 + 0x148);
                *(f32 *)&sp[3] = *(f32 *)(s0 + 0x14C);
                *(f32 *)&sp[4] = *(f32 *)(s0 + 0xE0);
                *(f32 *)&sp[5] = *(f32 *)(s0 + 0xE4);
                *(f32 *)&sp[6] = *(f32 *)(s0 + 0xE8);
                sp[7] = 0;
                f12 = f21 * f12;
                f12 = f12 + 0.5f;
                f20 = *(f32 *)(s0 + 0x88);
                f0 = floorf(f12);
                a2 = (s32)f0;
                f1 = *(f32 *)(s1 + 0x21D0);
                a1 = (s32)f1;
                func_001E1BC8(s0, a1, a2, (void *)&sp[4], (void *)sp, f20);
                *(s8 *)(s0 + 0x19C) = 0;
                s0 += 0x1B0;
            } while (i < *(s32 *)(s1 + 0x1B0));
        }
        *(f32 *)(s1 + 0x21D4) = f21;
        *(s32 *)(s1 + 0x21D0) = 0;
    }
}
