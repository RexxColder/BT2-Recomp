#include "common.h"

s32 func_002A3C68(void);
void func_002A4CF0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7,
                   s32 arg8, s32 arg9, s32 arg10, s32 arg11, s32 arg12, s32 arg13, s32 arg14,
                   s32 arg15, s32 arg16);

void func_002A42C8(s32 arg0, s32 arg1) {
    s32 s0;
    s32 s1;
    s32 s2;
    s32 v;
    s32 n;
    f32 t;
    f32 fr;

    s0 = 0;
    s1 = 0;
    s2 = 0;
    if (arg0 >= -1) {
        if (arg0 <= 0) {
            s0 = 0xC8;
            if (arg1 < 0x25) {
                t = (1.0f - ((f32)arg1 / 37.0f)) * 64.0f;
                n = (s32)t;
                fr = t - (f32)n;
                if (fr > 0.5f || (fr == 0.5f && (n & 1))) {
                    n += 1;
                } else if (fr < -0.5f || (fr == -0.5f && (n & 1))) {
                    n -= 1;
                }
                s1 = -n;
            }
        } else if (arg0 == 1) {
            s1 = 0x180;
            s0 = 0xC8;
            s2 = 1;
            if (arg1 < 0x25) {
                t = (1.0f - ((f32)arg1 / 37.0f)) * 64.0f;
                n = (s32)t;
                fr = t - (f32)n;
                if (fr > 0.5f || (fr == 0.5f && (n & 1))) {
                    n += 1;
                } else if (fr < -0.5f || (fr == -0.5f && (n & 1))) {
                    n -= 1;
                }
                s1 = n + 0x180;
            }
        }
    }
    v = func_002A3C68();
    func_002A4CF0(0x19, 3, v, 0, s1, s0, s1 + 0x80, s0 + 0x100, 0x80, 0x80, 0x80, 0x80, 0, 0, 0x80,
                  0x100, s2);
}
