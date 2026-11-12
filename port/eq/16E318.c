#include "common.h"

s32 EftShot_TestBits(s32 arg0, s32 arg1);
void func_0016DB58(f32 farg0, f32 farg1, f32 farg2, s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
s32 func_00191688(s32 arg0);

void func_0016E318(s32 arg0) {
    u8 *e;
    u8 *p;
    s32 s1;
    f32 f0;
    s32 v1;

    e = *(u8 **)(arg0 + 0x38);
    if (EftShot_TestBits(*(s32 *)*(u8 **)(e + 0xB0), 4) != 0) {
        func_0016DB58(1.0f, *(f32 *)(e + 0x1C), *(f32 *)(e + 0x18), arg0, 4, 2, 1, 0);
    }
    p = e + 0xAC0;
    s1 = 0xD;
    do {
        if (*(s32 *)(p + 0x20) != 0) {
            v1 = *(s32 *)p;
            if (!(v1 & 4)) {
                f0 = *(f32 *)(p + 8);
                if (!(8.0f <= f0)) {
                    *(f32 *)(p + 8) = f0 + 1.0f;
                } else {
                    *(s32 *)p = v1 | 4;
                    func_00191688(*(s32 *)(p + 0x20));
                }
            }
        }
        s1 -= 1;
        p += 0x30;
    } while (s1 >= 0);
}
