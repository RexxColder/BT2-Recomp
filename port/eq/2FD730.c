#include "common.h"

u8 *func_002FD6D8(s32 arg0);
void func_002FD2E8(s32 arg0, s32 arg1);
s32 func_002FD318(s32 arg0, s32 arg1);
void func_002FD710(u8 *arg0);
void func_002FDF58(s32 arg0, s32 arg1);
void func_002EFAB8(s32 arg0, s32 arg1);
void func_002FC550(s32 arg0);
s32 sceCdSync(s32 arg0);
s32 func_002FE7C8(s32 arg0, s32 arg1);
extern u8 D_00356BC0[] __attribute__((section(".data")));
extern u8 D_0037E350[] __attribute__((section(".data")));
extern u8 D_0037E378[] __attribute__((section(".data")));
extern u8 D_0037E3A0[] __attribute__((section(".data")));
extern u8 D_0037E3D0[] __attribute__((section(".data")));
extern u8 D_0037E3F8[] __attribute__((section(".data")));

/* a1 is never read by the original: arg2 is the third parameter (a2) */
u8 *func_002FD730(s32 arg0, s32 arg1, s32 arg2) {
    s32 var_a0;
    u8 *var_a1;
    s32 temp_s4;
    u8 *temp_v0;
    u8 *temp_s3;

    var_a0 = arg0;
    if (var_a0 == 0) {
        var_a1 = D_0037E350;
        goto block_7;
    }
    if (arg2 != 0) {
        var_a0 = 0;
        var_a1 = D_0037E378;
        goto block_7;
    }
    temp_v0 = func_002FD6D8(arg0);
    temp_s3 = temp_v0 + 0x20;
    if (temp_v0 == NULL) {
        var_a0 = 0;
        var_a1 = D_0037E3A0;
block_7:
        func_002FD2E8(var_a0, (s32)var_a1);
        return NULL;
    }
    temp_s4 = func_002FE7C8(arg0, (s32)temp_s3);
    if (*(s32 *)(temp_v0 + 0x24) == 0) {
        func_002FDF58(arg0, (s32)D_00356BC0);
        func_002EFAB8((s32)D_0037E3D0, (s32)D_00356BC0);
        func_002FC550(0x8300);
        sceCdSync(0);
        func_002FC550(0x8301);
        if (func_002FD318((s32)temp_s3, (s32)D_00356BC0) != 0) {
            *(u8 *)(temp_v0 + 1) = 0;
            goto block_15;
        }
        func_002FD2E8(0, (s32)D_0037E3F8);
        func_002FD710(temp_v0);
        return NULL;
    }
    *(u8 *)(temp_v0 + 1) = 1;
block_15:
    *(u32 *)(temp_v0 + 8) = (u32)(*(s32 *)(temp_v0 + 0x24) + 0x7FF) >> 11;
    *(u8 *)(temp_v0 + 0) = 1;
    *(s32 *)(temp_v0 + 4) = *(s32 *)(temp_v0 + 0x24);
    *(s32 *)(temp_v0 + 0xC) = 0;
    *(s32 *)(temp_v0 + 0x18) = 0;
    *(s32 *)(temp_v0 + 0x10) = 0;
    *(s32 *)(temp_v0 + 0x14) = 0;
    *(u8 *)(temp_v0 + 2) = 0;
    *(s32 *)(temp_v0 + 0x1C) = 0;
    if (temp_s4 == 1) {
        *(u32 *)(temp_v0 + 8) = 0x7FFFFFFFU;
    }
    return temp_v0;
}
