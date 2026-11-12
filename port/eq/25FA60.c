#include "common.h"

s32 func_0025E7A0(s32 arg0, s32 arg1);
u8 *func_0025EF60(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void memset(void *arg0, s32 arg1, u32 arg2);

void func_0025FA60(u8 *arg0, s16 arg1) {
    s32 sp[4];
    u8 *s1;
    u8 *v0;

    v0 = func_0025EF60((s32)arg0, (s32)(arg0 + 0xDD80), arg1, (s32)sp);
    s1 = arg0 + 0xBD0;
    *(u8 **)(s1 + 0x2C) = v0;
    if (v0 != NULL) {
        *(s16 *)(s1 + 6) = arg1;
        *(f32 *)(s1 + 0xC) = (f32)*(u16 *)(v0 + 2);
        memset(arg0 + 0xC8E, 0, 0x8E);
        if (arg0[0xE5C] != 0) {
            func_0025E7A0((s32)arg0, (s32)*(u8 **)(s1 + 0x2C));
        }
    }
}
