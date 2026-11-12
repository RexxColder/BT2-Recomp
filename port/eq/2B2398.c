#include "common.h"

void func_002B2230(s32 arg0, s32 arg1, s32 arg2);
s32 func_00101608(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
s32 rand(void);

void func_002B2398(u8 *arg0) {
    s32 sp[2];
    u8 *s0;
    s32 s1;
    s32 s2;
    s32 s3;
    s32 s4;
    u8 s5;
    f32 f0;
    f32 f1;
    s32 r;
    f32 fr;

    s1 = -1;
    s0 = arg0;
    s4 = *(s32 *)(s0 + 0x30);
    s5 = *(u8 *)(*(u8 **)(*(u8 **)s0 + 0x958) + 0x3D);
    if (*(s32 *)(s0 + 4) == 0) {
        sp[0] = 0x7F;
        sp[1] = 0x40;
        func_002B2230((s32)(s0 + 0xD0), (s32)sp, (s32)&sp[1]);

        f1 = (f32)sp[0];
        f1 = f1 / 127.0f;
        f1 = f1 - 1.0f;
        f1 = f1 * 200.0f;
        r = (s32)f1;
        fr = f1 - (f32)r;
        if (fr > 0.5f || (fr == 0.5f && (r & 1))) {
            r += 1;
        } else if (fr < -0.5f || (fr == -0.5f && (r & 1))) {
            r -= 1;
        }
        s2 = r;

        f0 = (f32)sp[1] * 0.015625f;
        f0 = f0 - 1.0f;
        f0 = f0 * 15.0f;
        r = (s32)f0;
        fr = f0 - (f32)r;
        if (fr > 0.5f || (fr == 0.5f && (r & 1))) {
            r += 1;
        } else if (fr < -0.5f || (fr == -0.5f && (r & 1))) {
            r -= 1;
        }
        s3 = r;

        if (s4 & 1) {
            s1 = (rand() & 1) + 0x4E;
        }
        if (s4 & 2) {
            s1 = 0x52;
        }
        if (s1 >= 0) {
            func_00101608(*(s32 *)(s0 + 4), s5, s1, s2, s3);
        }
    }
}
