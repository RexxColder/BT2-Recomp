#include "common.h"

extern f32 D_00384658;
extern f32 D_0038465C;

void func_00129C28(s32 arg0, s32 arg1);
void func_0012A360(s32 arg0, s32 arg1, s32 arg2, f32 farg0);
s32 func_001EB7F0(s32 arg0);
void func_001EB8D0(s32 arg0, s32 arg1);
void func_001EB930(s32 arg0, s32 arg1);
void func_001EB9C0(s32 arg0, s32 arg1);
void func_001EBA20(s32 arg0, f32 farg0);
void func_001EBAB8(s32 arg0, f32 farg0);
void func_001EBB00(s32 arg0, f32 farg0);
void func_001EBB48(s32 arg0);
s32 func_001EB880(s32 arg0);
s32 func_001EB830(s32 arg0);

/* Effect driver (same shape as 150700, blast flavour): on bit 0 with no live object it builds a 64-byte
 * descriptor from the arguments on the frame and creates the object; then bits 3/4/5/6 update position,
 * size and extra params, bit 2 kills it, bit 1 stops it. */
s32 func_00151138(s32 a1, s32 a2, s32 a3, s32 a4, s32 *a5, u8 a6, s32 a7, s32 a8,
                  f32 a9, f32 a10, f32 a11, s32 a12) {
    u8 sp[0x110];
    s32 flags = a6 & 0xFF;
    s32 result;

    if ((flags & 1) != 0 && *a5 == 0) {
        __builtin_memset(sp + 0x70, 0, 16);
        __builtin_memset(sp + 0x80, 0, 16);
        *(s32 *)(sp + 0x60) = a2 + 8;
        *(s32 *)(sp + 0x64) = a3;
        *(s32 *)(sp + 0x68) = a4;
        *(s32 *)(sp + 0x98) = *(u8 *)(a1 + 3);
        *(f32 *)(sp + 0x90) = a9;
        *(f32 *)(sp + 0x94) = a10;
        *(s32 *)(sp + 0x9C) = a7;
        *(u8 *)(sp + 0xA0) = 1;
        __builtin_memcpy(sp + 0x10, sp + 0x60, 0x40);
        __builtin_memcpy(sp + 0x50, sp + 0xA0, 0x10);

        func_0012A360((s32)(sp + 0x20), a12, a8,
                      (f32)*(s16 *)(a1 + 0x18) * D_00384658 * a11);
        *(f32 *)(sp + 0x2C) = 1.0f;
        func_00129C28((s32)(sp + 0x30), a12);
        *a5 = func_001EB7F0((s32)(sp + 0x10));
        func_001EBAB8(*a5, (f32)*(u8 *)(a1 + 0x15));
        func_001EBB00(*a5, (f32)*(u8 *)(a1 + 4));
        if ((*(u8 *)(a1 + 7) & 0x20) != 0) {
            func_001EBB48(*a5);
        }
    }

    result = flags & 8;
    if (*a5 == 0) {
        return result;
    }

    if (result != 0) {
        func_0012A360((s32)sp, a12, a8,
                      (f32)*(s16 *)(a1 + 0x18) * D_0038465C * a11);
        *(f32 *)(sp + 0xC) = 1.0f;
        if ((flags & 0x10) == 0) {
            func_001EB8D0(*a5, (s32)sp);
        } else {
            func_001EB930(*a5, (s32)sp);
        }
    }

    if ((flags & 0x20) != 0) {
        func_001EBA20(*a5, a10);
    }
    if ((flags & 0x40) != 0) {
        func_001EB9C0(*a5, a12);
    }
    if ((flags & 4) != 0) {
        result = func_001EB880(*a5);
        *a5 = 0;
    } else {
        result = flags & 2;
        if (result != 0) {
            return func_001EB830(*a5);
        }
    }
    return result;
}
