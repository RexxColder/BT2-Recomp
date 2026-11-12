#include "common.h"

void BtlTask_SetTagBits(s32 arg0, s32 arg1);
void func_001F3720(s32 arg0, s32 arg1);
extern u8 *gEftHitList;

void EftHit_SetTaskFlag(u32 arg0, s32 arg1, s32 arg2) {
    s32 temp_v0;
    u8 *temp_s0;

    if (gEftHitList == NULL) {
        return;
    }
    temp_s0 = gEftHitList + arg0 * 0x180;
    if (arg0 < *(u32 *)(gEftHitList + 0x6000)) {
        temp_v0 = *(s32 *)(temp_s0 + 0x60);
        if (temp_v0 != 0) {
            BtlTask_SetTagBits(temp_v0, arg1);
            func_001F3720(*(s32 *)(temp_s0 + 0x60), arg2);
        }
    }
}
