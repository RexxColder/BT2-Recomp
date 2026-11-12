#include "common.h"

void EftPtcl3_Stop(s32 arg0, s32 arg1);
void func_0018BAD0(s32 arg0);
extern s32 D_003877D0;

s32 func_00195538(s32 arg0) {
    u8 *temp_s0;

    temp_s0 = (u8 *)D_003877D0 + arg0 * 0x50;
    *(s32 *)(temp_s0 + 0x8) = 0;
    if (*(s32 *)(temp_s0 + 0x4) == 0) {
        EftPtcl3_Stop(*(s32 *)(temp_s0 + 0x40), D_003877D0);
        *(s32 *)(temp_s0 + 0x40) = 0;
        func_0018BAD0(*(s32 *)(temp_s0 + 0x44));
        *(s32 *)(temp_s0 + 0x44) = 0;
    }
    return 1;
}
