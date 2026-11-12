#include "common.h"

s32 EftShot_TestBits(s32 arg0, s32 arg1);
s32 func_0020B3D0(s32 arg0);
void func_00283770(s32 arg0, void *arg1, s32 arg2);
void func_002837C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 t0);
void func_00283800(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 t0);
void func_00283840(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 t0);
extern f32 D_003846A8;

void func_00156B70(void *arg0) {
    u8 *s2;
    u8 *s0;
    s32 s1;
    f32 f0;
    f32 f1;
    f32 xv;
    s32 r8;
    s32 r32;
    s32 r128;

    s2 = *(u8 **)((u8 *)arg0 + 0x38);
    s0 = *(u8 **)(s2 + 0xB0);
    s1 = func_0020B3D0(*(s32 *)s0);
    if (*(s32 *)(*(u8 **)(s0 + 0x20) + 0x30) & 0x200) {
        if (EftShot_TestBits(s1, 0x10) != 0) {
            *(s32 *)s2 = *(s32 *)s2 | 0x200;
        }
        if (EftShot_TestBits(s1, 0x20) != 0) {
            *(f32 *)(s2 + 0x20) = 0.0f;
            *(s32 *)s2 = *(s32 *)s2 & ~0x200;
        }
        if (*(s32 *)s2 & 0x200) {
            f0 = *(f32 *)(s2 + 0x20) + D_003846A8;
            *(f32 *)(s2 + 0x20) = f0;
            if (f0 > 1.0f) {
                *(f32 *)(s2 + 0x20) = 1.0f;
            }
        }
    }
    f1 = *(f32 *)(s2 + 0x20);

    /* cvt.w.s (truncates toward zero) of f1*8, f1*32, f1*128 */
    xv = f1 * 8.0f;
    r8 = (s32)xv;

    xv = f1 * 32.0f;
    r32 = (s32)xv;

    xv = f1 * 128.0f;
    r128 = (s32)xv;

    func_002837C0(0, 0x80, 0x80, 0x80, r8 & 0xFF);
    func_00283800(0, 0x80, 0x80, 0x80, r32 & 0xFF);
    func_00283840(0, 0x80, 0x80, 0x80, r128 & 0xFF);
    func_00283770(0, s2 + 0x30, 0);
}
