#include "common.h"

void func_001BDA28(s32 arg0, s32 arg1);
void func_001BDE48(s32 arg0, s32 arg1);

void func_001BDF90(u8 *arg0, s32 arg1) {
    s32 v1;
    s32 go8;
    f32 f;

    v1 = *(s32 *)(arg0 + 0x60);
    go8 = 0;
    if (v1 & 2) {
        if (!(*(f32 *)(arg0 + 0x7C) <= 0.0f)) {
            go8 = 1;
        } else if (*(s32 *)(arg0 + 0x68) <= 0) {
            v1 = v1 | 4;
            *(s32 *)(arg0 + 0x60) = v1;
        }
    } else {
        go8 = 1;
    }

    if (go8) {
        if (*(f32 *)(arg0 + 0x78) <= 0.0f) {
            f = *(f32 *)(arg0 + 0x74);
            if (!(f <= 0.0f)) {
                *(f32 *)(arg0 + 0x74) = f - 1.0f;
            } else {
                func_001BDE48((s32)arg0, arg1);
                v1 = *(s32 *)(arg0 + 0x60);
            }
        } else {
            *(f32 *)(arg0 + 0x78) = *(f32 *)(arg0 + 0x78) - 1.0f;
        }
    }

    if (v1 & 2) {
        f = *(f32 *)(arg0 + 0x7C);
        if (0.0f < f) {
            *(f32 *)(arg0 + 0x7C) = f - 1.0f;
        }
    }
    func_001BDA28((s32)arg0, arg1);

    v1 = *(s32 *)(arg0 + 0x60);
    if (!(v1 & 8) && *(f32 *)(arg0 + 0x78) <= 0.0f) {
        f = *(f32 *)(arg0 + 0x70) - 1.0f;
        *(f32 *)(arg0 + 0x70) = f;
        if (f <= 0.0f) {
            *(s32 *)(arg0 + 0x60) = v1 | 2;
        }
    }
}
