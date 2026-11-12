#include "common.h"

void func_00276A60(s32 arg0);
void func_003126C8(s32 arg0, s32 arg1);
void func_00312FB0(s32 arg0, s32 arg1, f32 farg0);

void func_00263ED0(s32 arg0_unused, u8 **arg1, u8 *arg2) {
    s32 sp[4];
    s32 flags;
    s32 mode;
    u8 *p;

    func_00276A60((s32)sp);
    flags = *(s32 *)arg2;
    if (flags & 0x10000) {
        mode = 1;
    } else if (flags & 0x20000) {
        mode = 2;
    } else if (flags & 0x40000) {
        mode = 1;
    } else if (flags & 0x80000) {
        mode = 3;
    } else if (flags & 0x100000) {
        mode = 1;
    } else if (flags & 0x400000) {
        mode = 2;
    } else {
        mode = 1;
    }
    if (mode == 1) {
        *(f32 *)(arg2 + 0x2C) = 128.0f;
        *(f32 *)(arg2 + 0x20) = (f32)sp[0];
        *(f32 *)(arg2 + 0x24) = (f32)sp[1];
        *(f32 *)(arg2 + 0x28) = (f32)sp[2];
    } else if (mode == 2) {
        *(f32 *)(arg2 + 0x2C) = 128.0f;
        *(f32 *)(arg2 + 0x20) = 128.0f;
        *(f32 *)(arg2 + 0x24) = 128.0f;
        *(f32 *)(arg2 + 0x28) = 128.0f;
    } else {
        *(f32 *)(arg2 + 0x20) = 0.0f;
        *(f32 *)(arg2 + 0x2C) = 128.0f;
        *(f32 *)(arg2 + 0x24) = 0.0f;
        *(f32 *)(arg2 + 0x28) = 0.0f;
    }
    if (arg1 != NULL) {
        p = *arg1;
        if (p != NULL) {
            if (*(f32 *)(p + 0x14) == 0.0f) {
                *(f32 *)(p + 0x14) = 1.0f;
            }
            func_00312FB0((s32)(arg2 + 0x20), (s32)(arg2 + 0x20), *(f32 *)(p + 0x14));
            return;
        }
    }
    func_003126C8((s32)(arg2 + 0x20), (s32)(arg2 + 0x20));
}
