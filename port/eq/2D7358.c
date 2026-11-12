#include "common.h"

s32 func_003063E8(void *arg0, void *arg1, void *arg2, void *arg3);
extern u8 D_0037AC70[];
extern u8 D_0037AC78[];
extern u8 D_0037AC80[];

void func_002D7358(void *arg0) {
    s32 sp[8];
    u8 *temp_s3;
    u8 *temp_s4;
    u8 *a0;

    a0 = (u8 *)arg0;
    temp_s3 = a0 + 0x18;
    temp_s4 = a0 + 0x28;
    if (*(s32 *)(a0 + 0xC) == 0) {
        *(s32 *)(temp_s3 + 0x8) = 0;
        *(s32 *)(a0 + 0x18) = 1;
        *(s32 *)(temp_s3 + 0x4) = 0;
        *(s32 *)(a0 + 0x28) = 1;
        *(s32 *)(temp_s4 + 0x8) = 0;
        *(s32 *)(temp_s4 + 0x4) = 0;
        return;
    }
    sp[0] = *(s32 *)(a0 + 0xC);
    sp[1] = *(s32 *)(a0 + 0x10);
    func_003063E8(sp, D_0037AC70, D_0037AC78, &sp[4]);
    *(s32 *)(temp_s3 + 0x4) = sp[4];
    *(s32 *)(temp_s3 + 0x8) = sp[5];
    *(s32 *)(a0 + 0x18) = 1;
    func_003063E8(sp, D_0037AC80, D_0037AC78, &sp[4]);
    *(s32 *)(a0 + 0x28) = 1;
    *(s32 *)(temp_s4 + 0x4) = sp[4];
    *(s32 *)(temp_s4 + 0x8) = sp[5];
}
