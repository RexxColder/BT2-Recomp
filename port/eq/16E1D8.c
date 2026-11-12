#include "common.h"

s32 EftShot_TestBits(s32 arg0, s32 arg1);
void func_0016DB58(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, f32 farg0, f32 farg1, f32 farg2);
void func_00191688(s32 arg0);
extern f32 D_00384898;
extern f32 D_0038489C;

void func_0016E1D8(u8 *arg0) {
    u8 *s2;
    s32 *s0;
    u8 *p;
    s32 n;
    s32 flags;
    f32 f;

    s2 = *(u8 **)(arg0 + 0x38);
    s0 = *(s32 **)(s2 + 0xB0);

    if (EftShot_TestBits(*s0, 0x40) != 0) {
        if (EftShot_TestBits(*s0, 4) != 0) {
            func_0016DB58((s32)arg0, 4, 2, 1, 0, 0.0f, *(f32 *)(s2 + 0x1C) * D_00384898,
                          *(f32 *)(s2 + 0x18) * D_0038489C);
        }
    } else if (EftShot_TestBits(*s0, 4) != 0) {
        func_0016DB58((s32)arg0, 4, 2, 1, 0, 0.0f, *(f32 *)(s2 + 0x1C), *(f32 *)(s2 + 0x18));
    }

    n = 0xD;
    p = s2 + 0xAC0;
    do {
        if (*(s32 *)(p + 0x20) != 0) {
            flags = *(s32 *)p;
            if (!(flags & 4)) {
                f = *(f32 *)(p + 8);
                if (!(f >= 8.0f)) {
                    *(f32 *)(p + 8) = f + 1.0f;
                } else {
                    *(s32 *)p = flags | 4;
                    func_00191688(*(s32 *)(p + 0x20));
                }
            }
        }
        n -= 1;
        p += 0x30;
    } while (n >= 0);
}
