#include "common.h"

void func_001E0EA0(s32 arg0);
void func_001E1E28(s32 arg0, s32 arg1);
s32 func_00312FB0(s32 arg0, s32 arg1, f32 farg0);

void func_001E05F8(u8 *arg0, s32 arg1, f32 fa) {
    u32 t;
    s32 s2;
    u8 *s1;
    u8 *s0;

    t = arg1 & 0xFF;
    if (t < *(u8 *)(arg0 + 0x10F00)) {
        s2 = 0;
        s1 = arg0 + t * 0x21E0;
        s0 = s1 + 0x10;
        if (*(s32 *)(s1 + 0x1B0) > 0) {
            do {
                s2 += 1;
                func_00312FB0((s32)(s0 + 0x110), (s32)(s0 + 0x110), fa);
                func_00312FB0((s32)(s0 + 0x120), (s32)(s0 + 0x120), fa);
                func_00312FB0((s32)(s0 + 0x130), (s32)(s0 + 0x130), fa);
                func_00312FB0((s32)(s0 + 0x140), (s32)(s0 + 0x140), fa);
                func_001E0EA0((s32)s0);
                func_001E1E28((s32)(s0 + 0x10), (s32)(s0 + 0x60));
                s0 += 0x1B0;
            } while (s2 < *(s32 *)(s1 + 0x1B0));
        }
    }
}
