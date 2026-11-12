#include "common.h"

void EftPtcl3_SetStopDelay(s32 arg0, f32 farg0);
void EftPtcl3_Stop(s32 arg0);

void func_001A1548(u8 *arg0) {
    u8 *s0 = *(u8 **)(arg0 + 0x38);

    EftPtcl3_SetStopDelay(*(s32 *)(s0 + 0x2C), 1.0f);
    EftPtcl3_Stop(*(s32 *)(s0 + 0x2C));
    *(s32 *)(s0 + 0x2C) = 0;
}
