#include "common.h"

void EftChain2_Stop(s32 arg0);
void EftPtcl3_Stop(s32 arg0);
void EftRibbon_StopAndKill(s32 arg0, s32 arg1);
void func_0018E098(s32 arg0);
void func_001CC9E8(s32 arg0);
void func_001E71D8(u8 *arg0, s32 arg1);

void func_001AA928(u8 *arg0) {
    u8 *temp_s0;

    temp_s0 = *(u8 **)(arg0 + 0x38);
    if (*(s32 *)(temp_s0 + 4) & 1) {
        func_0018E098(*(s32 *)(temp_s0 + 0xD8));
    }
    if (*(s32 *)(temp_s0 + 4) & 2) {
        EftPtcl3_Stop(*(s32 *)(temp_s0 + 0xDC));
        *(s32 *)(temp_s0 + 0xDC) = 0;
    }
    if (*(s32 *)(temp_s0 + 0) & 0x80) {
        func_001E71D8(temp_s0 + (*(s32 *)(temp_s0 + 8) * 4) + 0xE8, 5);
        EftChain2_Stop(*(s32 *)(temp_s0 + 0xEC));
        *(s32 *)(temp_s0 + 0xEC) = 0;
        return;
    }
    EftRibbon_StopAndKill(*(s32 *)(temp_s0 + 0xD4), 5);
    *(s32 *)(temp_s0 + 0xD4) = 0;
    EftPtcl3_Stop(*(s32 *)(temp_s0 + 0xE0));
    *(s32 *)(temp_s0 + 0xE0) = 0;
    func_001CC9E8(*(s32 *)(temp_s0 + 0xE4));
    *(s32 *)(temp_s0 + 0xE4) = 0;
}
