#include "common.h"

void func_00129BD0(s32 arg0, s32 arg1, f32 farg0);
s32 rand(void);
extern f32 D_00384814;
extern f32 D_00384818;
extern f32 D_0038481C;
extern f32 D_00384820;
extern f32 D_00384824;
extern f32 D_00384828;

void func_001693D8(s32 arg0, void *arg1) {
    u8 *s0;
    s32 p;

    s0 = (u8 *)arg1;
    p = (s32)(s0 + 0x70);
    func_00129BD0(p, p, 3.0f);

    *(f32 *)(s0 + 0xA0) = *(f32 *)(s0 + 0xA0) * ((((f32)rand() / D_00384814) * D_00384818) + D_0038481C);
    *(f32 *)(s0 + 0xA4) = *(f32 *)(s0 + 0xA4) * ((((f32)rand() / D_00384814) * D_00384818) + D_0038481C);
    *(s32 *)(s0 + 0xA8) = 0;
    *(f32 *)(s0 + 0x44) = (((f32)rand() / D_00384814) * D_00384820) + D_00384820;
    *(f32 *)(s0 + 0x4C) = ((((f32)rand() / D_00384814) * D_00384818) + D_00384824) * D_00384828;
}
