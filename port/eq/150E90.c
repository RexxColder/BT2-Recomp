#include "common.h"

extern f32 D_00384650;
extern f32 D_00384654;

void func_00129C28(s32 arg0, s32 arg1);
void func_0012A360(s32 arg0, s32 arg1, s32 arg2, f32 farg0);
s32 func_00194D18(s32 arg0);
void func_00194E70(s32 arg0, s32 arg1);
void func_00194EC8(s32 arg0, s32 arg1);
void func_00194F60(s32 arg0, f32 farg0);
void func_00194FA8(s32 arg0, s32 arg1);
s32 func_00194DE0(s32 arg0);
s32 func_00194D90(s32 arg0);
void func_00195098(s32 arg0, f32 farg0);
void func_001950E0(s32 arg0, f32 farg0);
void func_00195180(s32 arg0);
void func_001951D0(s32 arg0, s32 arg1);

/* Effect driver, sibling of func_00151138 with its own callee set: creates the object from a 64-byte
 * frame descriptor on bit 0, then applies position/size/extra updates by flag bits and kills or stops it. */
s32 func_00150E90(s32 a1, s32 a2, s32 a3, s32 a4, s32 *a5, u8 a6, s32 a7, s32 a8,
                  f32 a9, f32 a10, f32 a11, s32 a12) {
    u8 sp[0x110];
    s32 flags = a6 & 0xFF;
    s32 result;

    if ((flags & 1) != 0 && *a5 == 0) {
        *(f32 *)(sp + 0x60) = a9;
        *(f32 *)(sp + 0x64) = a10;
        __builtin_memset(sp + 0x70, 0, 16);
        __builtin_memset(sp + 0x80, 0, 16);
        *(s32 *)(sp + 0x90) = *(u8 *)(a1 + 3);
        *(s32 *)(sp + 0x94) = a2 + 8;
        *(s32 *)(sp + 0x98) = a3;
        *(s32 *)(sp + 0x9C) = a4;
        *(s32 *)(sp + 0xA0) = a7;
        __builtin_memcpy(sp + 0x10, sp + 0x60, 0x40);
        __builtin_memcpy(sp + 0x50, sp + 0xA0, 0x10);

        func_0012A360((s32)(sp + 0x20), a12, a8,
                      (f32)*(s16 *)(a1 + 0x18) * D_00384650 * a11);
        *(f32 *)(sp + 0x2C) = 1.0f;
        func_00129C28((s32)(sp + 0x30), a12);
        *a5 = func_00194D18((s32)(sp + 0x10));
        func_00195098(*a5, (f32)*(u8 *)(a1 + 0x15));
        func_001950E0(*a5, (f32)*(u8 *)(a1 + 4));
        if ((*(u8 *)(a1 + 7) & 0x20) != 0) {
            func_00195180(*a5);
        }
        func_001951D0(*a5, 1);
    }

    result = flags & 8;
    if (*a5 == 0) {
        return result;
    }

    if (result != 0) {
        func_0012A360((s32)sp, a12, a8,
                      (f32)*(s16 *)(a1 + 0x18) * D_00384654 * a11);
        *(f32 *)(sp + 0xC) = 1.0f;
        if ((flags & 0x10) == 0) {
            func_00194E70(*a5, (s32)sp);
        } else {
            func_00194EC8(*a5, (s32)sp);
        }
    }

    if ((flags & 0x20) != 0) {
        func_00194F60(*a5, a10);
    }
    if ((flags & 0x40) != 0) {
        func_00194FA8(*a5, a12);
    }
    if ((flags & 4) != 0) {
        result = func_00194DE0(*a5);
        *a5 = 0;
    } else {
        result = flags & 2;
        if (result != 0) {
            return func_00194D90(*a5);
        }
    }
    return result;
}
