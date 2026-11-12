#include "common.h"

extern f32 D_00384640;
extern f32 D_00384644;

void func_00129C28(s32 arg0, s32 arg1);
void func_0012A360(s32 arg0, s32 arg1, s32 arg2, f32 farg0);
s32 EftChain2_Create(s32 arg0);
void EftChain2_SetParam3(s32 arg0, s32 arg1);
void EftChain2_SetParam5(s32 arg0, f32 farg0);
void EftChain2_SetParam6(s32 arg0, f32 farg0);
void EftChain2_SetViewOnly(s32 arg0);
void EftChain2_SetType(s32 arg0, s32 arg1);
void EftChain2_SetPos(s32 arg0, s32 arg1);
void EftChain2_Warp(s32 arg0, s32 arg1);
void EftChain2_SetSize(s32 arg0, f32 farg0);
s32 EftChain2_Kill(s32 arg0);
s32 EftChain2_Stop(s32 arg0);

/* Effect-chain driver: when flags bit 0 is set and no chain exists yet, builds one from the descriptor
 * a2 and the frame's two vectors; each call then applies position/size updates, and bit 2 kills the chain,
 * bit 1 stops it. */
s32 func_00150700(s32 a1, s32 a2, s32 a3, s32 a4, s32 *a5, s32 a6, s32 a7, s32 a8,
                  f32 a9, f32 a10, f32 a11, s32 a12, s32 a13) {
    u8 sp[0xF0];
    s32 flags = a6 & 0xFF;
    s32 result;

    if ((flags & 1) != 0 && *a5 == 0) {
        __builtin_memset(sp + 0x60, 0, 16);
        __builtin_memset(sp + 0x70, 0, 16);
        *(s32 *)(sp + 0x50) = a7;
        *(s32 *)(sp + 0x54) = a8;
        *(f32 *)(sp + 0x58) = a9;
        *(f32 *)(sp + 0x5C) = a10;
        *(s32 *)(sp + 0x80) = *(u8 *)(a2 + 3);
        *(s32 *)(sp + 0x84) = a1 + 0x1608;
        *(s32 *)(sp + 0x88) = a3;
        *(s32 *)(sp + 0x8C) = a4;
        __builtin_memcpy(sp + 0x10, sp + 0x50, 0x40);

        func_00129C28((s32)(sp + 0x30), a13);
        func_0012A360((s32)sp, a13, a12,
                      (f32)*(s16 *)(a2 + 0x18) * D_00384640 * a11);
        *(f32 *)(sp + 0xC) = 1.0f;
        func_00129C28((s32)(sp + 0x20), (s32)sp);

        *a5 = EftChain2_Create((s32)(sp + 0x10));
        EftChain2_SetParam3(*a5, *(u8 *)(a2 + 0x14));
        EftChain2_SetParam5(*a5, (f32)*(u8 *)(a2 + 0x15));
        EftChain2_SetParam6(*a5, (f32)*(u8 *)(a2 + 4));
        if ((*(u8 *)(a2 + 7) & 0x20) != 0) {
            EftChain2_SetViewOnly(*a5);
        }
        EftChain2_SetType(*a5, 1);
    }

    result = flags & 8;
    if (*a5 == 0) {
        return result;
    }

    if (result != 0) {
        func_0012A360((s32)sp, a13, a12,
                      (f32)*(s16 *)(a2 + 0x18) * D_00384644 * a11);
        *(f32 *)(sp + 0xC) = 1.0f;
        if ((flags & 0x10) == 0) {
            EftChain2_SetPos(*a5, (s32)sp);
        } else {
            EftChain2_Warp(*a5, (s32)sp);
        }
    }

    if ((flags & 0x20) != 0) {
        EftChain2_SetSize(*a5, a10);
    }
    if ((flags & 4) != 0) {
        result = EftChain2_Kill(*a5);
        *a5 = 0;
    } else {
        result = flags & 2;
        if (result != 0) {
            return EftChain2_Stop(*a5);
        }
    }
    return result;
}
