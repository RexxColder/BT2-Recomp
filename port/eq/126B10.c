#include "common.h"

s32 BtlTaskList_AddTail(s32 arg0, void *arg1, s32 arg2);
extern u8 D_002C3550[];
extern u8 D_003400E0[];
extern u8 D_00340230[];
extern u8 D_00342A28[];
extern u8 D_00343600[];
extern u8 *gBtlScene;

void BtlScene_CreateLayers(void) {
    if (*(s32 *)(gBtlScene + 0x1C) & 1) {
        *(s32 *)(gBtlScene + 0x14) = BtlTaskList_AddTail(*(s32 *)(gBtlScene + 4), D_00343600, 0);
    }
    if (*(s32 *)(gBtlScene + 0x1C) & 2) {
        *(s32 *)(gBtlScene + 8) = BtlTaskList_AddTail(*(s32 *)(gBtlScene + 4), D_002C3550, 0);
    }
    if (*(s32 *)(gBtlScene + 0x1C) & 4) {
        *(s32 *)(gBtlScene + 0xC) = BtlTaskList_AddTail(*(s32 *)(gBtlScene + 4), D_00340230, 0);
    }
    if (*(s32 *)(gBtlScene + 0x1C) & 8) {
        *(s32 *)(gBtlScene + 0x10) = BtlTaskList_AddTail(*(s32 *)(gBtlScene + 4), D_00342A28, 0);
    }
    if (*(s32 *)(gBtlScene + 0x1C) & 0x10) {
        *(s32 *)(gBtlScene + 0x18) = BtlTaskList_AddTail(*(s32 *)(gBtlScene + 4), D_003400E0, 0);
    }
}
