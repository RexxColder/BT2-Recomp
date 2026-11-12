#include "common.h"

void func_001C9E48(s32 arg0, void *arg1, s32 arg2);
void func_001CA258(void *arg0, s32 arg1, s32 arg2, s32 arg3);

void func_001CA428(s32 arg0, void *arg1, s32 arg2) {
    u8 *p;
    f32 *s0;
    s32 v;
    s32 do7;
    s32 s2;
    s32 s3;
    f32 f0;

    p = (u8 *)arg1;
    v = *(s32 *)(p + 0x50);
    do7 = 1;
    if (v & 2) {
        if (*(f32 *)(p + 0x68) <= 0.0f) {
            do7 = 0;
            if (*(s32 *)(p + 0x58) <= 0) {
                v = v | 4;
                *(s32 *)(p + 0x50) = v;
            }
        }
    }

    if (do7) {
        if (*(f32 *)(p + 0x64) <= 0.0f) {
            s3 = 0;
            s2 = arg0 + 4;
            s0 = (f32 *)(p + 0x5C);
            do {
                f0 = *s0;
                if (!(f0 <= 0.0f)) {
                    *s0 = f0 - 1.0f;
                } else {
                    func_001CA258(p, arg2, s2, s3);
                }
                s3 += 1;
                s2 += 0x88;
                s0 += 1;
            } while (s3 < 2);
            v = *(s32 *)(p + 0x50);
        } else {
            *(f32 *)(p + 0x64) = *(f32 *)(p + 0x64) - 1.0f;
        }
    }

    if (v & 2) {
        if (*(f32 *)(p + 0x68) > 0.0f) {
            *(f32 *)(p + 0x68) = *(f32 *)(p + 0x68) - 1.0f;
        }
    }
    func_001C9E48(arg0, p, arg2);

    v = *(s32 *)(p + 0x50);
    if (!(v & 8) && *(f32 *)(p + 0x64) <= 0.0f) {
        f0 = *(f32 *)(p + 0x6C) - 1.0f;
        *(f32 *)(p + 0x6C) = f0;
        if (f0 <= 0.0f) {
            *(s32 *)(p + 0x50) = v | 2;
        }
    }
}
