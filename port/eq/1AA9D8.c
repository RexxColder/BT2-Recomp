#include "common.h"

void EftChain2_Kill(s32 arg0);
void EftPtcl3_Kill(s32 arg0);
void EftRibbon_Kill(s32 arg0, s32 arg1);
void func_0018E168(s32 arg0);
void func_001CCA38(s32 arg0);
void func_001E71D8(void *arg0, s32 arg1);

void func_001AA9D8(u8 *arg0) {
    u8 *temp_s0;

    temp_s0 = *(u8 **)(arg0 + 0x38);
    if (*(s32 *)(temp_s0 + 4) & 1) {
        func_0018E168(*(s32 *)(temp_s0 + 0xD8));
        *(s32 *)(temp_s0 + 0xD8) = 0;
    }
    if (*(s32 *)(temp_s0 + 4) & 2) {
        EftPtcl3_Kill(*(s32 *)(temp_s0 + 0xDC));
        *(s32 *)(temp_s0 + 0xDC) = 0;
    }
    if (*(s32 *)(temp_s0 + 0) & 0x80) {
        func_001E71D8(temp_s0 + (*(s32 *)(temp_s0 + 8) * 4) + 0xE8, 0);
        EftChain2_Kill(*(s32 *)(temp_s0 + 0xEC));
        *(s32 *)(temp_s0 + 0xEC) = 0;
        return;
    }
    EftRibbon_Kill(*(s32 *)(temp_s0 + 0xD4), 0);
    *(s32 *)(temp_s0 + 0xD4) = 0;
    EftPtcl3_Kill(*(s32 *)(temp_s0 + 0xE0));
    *(s32 *)(temp_s0 + 0xE0) = 0;
    func_001CCA38(*(s32 *)(temp_s0 + 0xE4));
    *(s32 *)(temp_s0 + 0xE4) = 0;
}
