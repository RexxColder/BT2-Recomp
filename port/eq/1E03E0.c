#include "common.h"

void func_001E1060(s32 arg0, s32 arg1, f32 farg0);
void func_001E1E28(s32 arg0, s32 arg1);

s32 func_001E03E0(u8 *arg0) {
    u8 *s0;
    u8 *s4;
    s32 s2;
    s32 s3;
    s32 count;
    f32 f0;

    s0 = arg0 + 0x10;
    s4 = s0;
    s2 = 0;
    s3 = *(u8 *)(s0 + 0x19C);
    if (*(s32 *)(arg0 + 0x1B0) > 0) {
        do {
            s2 += 1;
            func_001E1060((s32)s0, 0, *(f32 *)(arg0 + 0x21D0));
            s0 += 0x1B0;
        } while (s2 < *(s32 *)(arg0 + 0x1B0));
    }
    f0 = *(f32 *)(arg0 + 0x21D0) + 1.0f;
    *(f32 *)(arg0 + 0x21D0) = f0;
    if (*(f32 *)(arg0 + 0x21D4) < f0) {
        s0 = s4;
        if (s3 != 0) {
            s2 = 0;
            count = *(s32 *)(arg0 + 0x1B0);
            if (count > 0) {
                do {
                    func_001E1E28((s32)(s0 + 0x10), (s32)(s0 + 0x60));
                    s2 += 1;
                    s0 += 0x1B0;
                } while (s2 < count);
            }
            *(f32 *)(arg0 + 0x21D0) = 0.0f;
            return 1;
        }
        return 0;
    }
    return 1;
}
