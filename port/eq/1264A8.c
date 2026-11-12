#include "common.h"

s32 BtlStage_IsReady(void);
extern u8 *D_003876A0;

/* 0x001264A8 BtlScene_IsTimeStopped: s0 = (flags at D_003876A0+0x4D8 & 0x100) != 0; returns (BtlStage_IsReady() != 0) ? s0 : 1. */
s32 BtlScene_IsTimeStopped(void) {
    s32 s0 = ((*(s64 *)(D_003876A0 + 0x4D8) & 0x100) != 0) ? 1 : 0;

    return (BtlStage_IsReady() != 0) ? s0 : 1;
}
