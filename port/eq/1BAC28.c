#include "common.h"

void func_001B8FD0(s32 arg0, s32 arg1);
void func_001BA518(s32 arg0, s32 arg1);
void func_001BAAF8(s32 arg0, s32 arg1);

void func_001BAC28(u8 *arg0, s32 arg1) {
    s32 flags;
    s32 v0;
    f32 f;
    f32 f138;

    flags = *(s32 *)(arg0 + 0x60);
    if ((flags & 2) && (*(f32 *)(arg0 + 0x140) <= 0.0f)) {
        if (*(s32 *)(arg0 + 0x68) <= 0) {
            flags = flags | 4;
            *(s32 *)(arg0 + 0x60) = flags;
        }
    } else {
        f = *(f32 *)(arg0 + 0x13C);
        if (f <= 0.0f) {
            func_001B8FD0((s32)arg0, arg1);
            f138 = *(f32 *)(arg0 + 0x138);
            if (!(f138 <= 0.0f)) {
                flags = *(s32 *)(arg0 + 0x60);
                *(f32 *)(arg0 + 0x138) = f138 - 1.0f;
            } else {
                func_001BAAF8((s32)arg0, arg1);
                flags = *(s32 *)(arg0 + 0x60);
            }
        } else {
            *(f32 *)(arg0 + 0x13C) = f - 1.0f;
        }
    }
    v0 = flags & 2;
    if (v0 != 0) {
        f = *(f32 *)(arg0 + 0x140);
        if (0.0f < f) {
            *(f32 *)(arg0 + 0x140) = f - 1.0f;
        }
    }
    func_001BA518((s32)arg0, arg1);
    flags = *(s32 *)(arg0 + 0x60);
    if (!(flags & 8) && *(f32 *)(arg0 + 0x13C) <= 0.0f) {
        f = *(f32 *)(arg0 + 0x134) - 1.0f;
        *(f32 *)(arg0 + 0x134) = f;
        if (f <= 0.0f) {
            *(s32 *)(arg0 + 0x60) = flags | 2;
        }
    }
}
