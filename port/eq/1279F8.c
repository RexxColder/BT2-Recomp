#include "common.h"

void func_001AC968(s32 arg0, u8 *arg1);
extern u8 *gEftHitList;

void func_001279F8(u32 arg0, u8 *arg1) {
    s32 temp_a0;
    u8 *temp_v0;

    if (gEftHitList != NULL && arg0 < *(u32 *)(gEftHitList + 0x6000)) {
        temp_v0 = gEftHitList + arg0 * 0x180;
        temp_a0 = *(s32 *)(temp_v0 + 0x60);
        if (temp_a0 != 0 && *(s32 *)(temp_v0 + 0xC) == 0) {
            func_001AC968(temp_a0, arg1);
        }
    }
}
