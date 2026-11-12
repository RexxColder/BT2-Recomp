#include "common.h"

void BtlTask_Kill(s32 arg0);
extern u8 *gBtlScene;

void func_00126C00(void) {
    if (*(s32 *)(gBtlScene + 0x1C) & 8) {
        BtlTask_Kill(*(s32 *)(gBtlScene + 0x10));
        *(s32 *)(gBtlScene + 0x10) = 0;
    }
    if (*(s32 *)(gBtlScene + 0x1C) & 4) {
        BtlTask_Kill(*(s32 *)(gBtlScene + 0xC));
        *(s32 *)(gBtlScene + 0xC) = 0;
    }
    if (*(s32 *)(gBtlScene + 0x1C) & 2) {
        BtlTask_Kill(*(s32 *)(gBtlScene + 0x8));
        *(s32 *)(gBtlScene + 0x8) = 0;
    }
    if (*(s32 *)(gBtlScene + 0x1C) & 1) {
        BtlTask_Kill(*(s32 *)(gBtlScene + 0x14));
        *(s32 *)(gBtlScene + 0x14) = 0;
    }
    if (*(s32 *)(gBtlScene + 0x1C) & 0x10) {
        BtlTask_Kill(*(s32 *)(gBtlScene + 0x18));
        *(s32 *)(gBtlScene + 0x18) = 0;
    }
}
