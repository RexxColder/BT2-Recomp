#include "common.h"

void BtlTask_SetDead(u8 *arg0);
void EftGlow_Setup(u8 *arg0, s32 arg1);
void EftGlow_UpdateTextures(u8 *arg0);
void func_00198D58(u8 *arg0, s32 arg1);
void func_00198F10(u8 *arg0, s32 arg1);
s32 func_0020A5C0(s32 arg0);
extern u8 *D_003876A0;

void func_0019A220(u8 *arg0) {
    s32 temp_v1;
    u8 *temp_s0;

    temp_s0 = *(u8 **)(arg0 + 0x38);
    if (func_0020A5C0(*(s32 *)(temp_s0 + 0x4C)) != 0) {
        *(s32 *)(temp_s0 + 0) = *(s32 *)(temp_s0 + 0) | 0x10;
    }
    EftGlow_Setup(temp_s0, *(s32 *)(temp_s0 + 0x4C));
    *(s32 *)(temp_s0 + 0) = *(s32 *)(temp_s0 + 0) & ~0x10;
    if (!(*(s64 *)(D_003876A0 + 0x4D8) & 0x100)) {
        func_00198D58(temp_s0, *(s32 *)(temp_s0 + 0x4C));
        temp_v1 = *(s32 *)(temp_s0 + 0x10);
        switch (temp_v1) {
        case 0:
            *(s32 *)(temp_s0 + 0x10) = 1;
            break;
        case 1:
            *(s32 *)(temp_s0 + 0x10) = 2;
            break;
        }
        func_00198F10(temp_s0, *(s32 *)(temp_s0 + 0x4C));
    }
    if (*(s32 *)(temp_s0 + 0) & 4) {
        BtlTask_SetDead(arg0);
        return;
    }
    EftGlow_UpdateTextures(temp_s0);
}
