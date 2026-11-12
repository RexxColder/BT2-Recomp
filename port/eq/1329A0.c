#include "common.h"

extern void *gEftStage;

void func_001329A0(s32 arg0) {
    s32 temp_v0;

    if (gEftStage != NULL) {
        temp_v0 = *(s32 *)((u8 *)gEftStage + 8);
        if (arg0 & 0xFF) {
            *(s32 *)((u8 *)gEftStage + 8) = temp_v0 | 2;
            return;
        }
        *(s32 *)((u8 *)gEftStage + 8) = temp_v0 & ~2;
    }
}
