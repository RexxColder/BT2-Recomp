#include "common.h"

extern u8 *gBtlStage;
s32 BtlStage_IsReady(void);

s32 func_00276E58(void) {
    u8 *p;

    if (BtlStage_IsReady() == 0) {
        return -1;
    }
    p = (u8 *)*(s32 *)(gBtlStage + 0x4);
    if (*(u8 *)(p + 0x13) != 0) {
        return 0xF;
    }
    if (*(u8 *)(p + 0x14) == 0) {
        return -1;
    }
    return 3;
}
