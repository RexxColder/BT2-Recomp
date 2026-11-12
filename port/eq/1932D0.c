#include "common.h"

void func_00191C80(s32 a0, s32 a1);
void func_00191F20(f32 f12, s32 a0, s32 a1);
void func_00192B38(s32 a0, s32 a1);
s32 rand(void);
extern f32 D_00384C7C;

void func_001932D0(u8 *arg0, s32 arg1) {
    s32 v1;
    s32 v0;
    f32 f0;
    f32 f1;

    v1 = *(s32 *)(arg0 + 0x60);
    if ((v1 & 2) && *(f32 *)(arg0 + 0x124) <= 0.0f) {
        if (*(s32 *)(arg0 + 0x68) <= 0) {
            v1 = v1 | 4;
            *(s32 *)(arg0 + 0x60) = v1;
        }
    } else {
        f1 = *(f32 *)(arg0 + 0x120);
        if (f1 <= 0.0f) {
            func_00191C80((s32)arg0, arg1);
            f1 = *(f32 *)(arg0 + 0x11C);
            if (f1 <= 0.0f) {
                func_00191F20(*(f32 *)(arg0 + 0x6C), (s32)arg0, arg1);
                f1 = (f32)rand();
                f1 = f1 / D_00384C7C;
                f0 = *(f32 *)(arg0 + 0x74);
                f0 = f0 * f1;
                f1 = *(f32 *)(arg0 + 0x70);
                *(f32 *)(arg0 + 0x11C) = f1 + f0;
                v1 = *(s32 *)(arg0 + 0x60);
            } else {
                v1 = *(s32 *)(arg0 + 0x60);
                *(f32 *)(arg0 + 0x11C) = f1 - 1.0f;
            }
        } else {
            *(f32 *)(arg0 + 0x120) = f1 - 1.0f;
        }
    }
    v0 = v1 & 2;
    if (v0 != 0) {
        f1 = *(f32 *)(arg0 + 0x124);
        if (0.0f < f1) {
            *(f32 *)(arg0 + 0x124) = f1 - 1.0f;
        }
    }
    func_00192B38((s32)arg0, arg1);
    v1 = *(s32 *)(arg0 + 0x60);
    if (!(v1 & 8) && *(f32 *)(arg0 + 0x120) <= 0.0f) {
        f0 = *(f32 *)(arg0 + 0x118) - 1.0f;
        *(f32 *)(arg0 + 0x118) = f0;
        if (f0 <= 0.0f) {
            *(s32 *)(arg0 + 0x60) = v1 | 2;
        }
    }
}
