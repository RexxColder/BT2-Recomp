#include "common.h"

extern u8 *gBtlStage;
void func_0011CB00(s32 arg0, s32 arg1);
s32 func_0011CB18(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_0011DA78(void);
s32 StgCol_FirstBit(s64 arg0);
s32 func_002745F8(s32 arg0);

void func_0011E130(s32 arg0, u8 *arg1) {
    s32 sp[8];
    s32 temp_s0;
    s32 temp_v0;

    temp_s0 = *(s32 *)(gBtlStage + 0x5C) + (*(s32 *)(gBtlStage + 0x3C) * 4);
    func_0011CB00(arg0, (s32)arg1);
    if (func_0011CB18((s32)sp, temp_s0 + (arg0 << 6), (s32)(arg1 + 0x40), (s32)arg1, (s32)func_0011DA78) != 0) {
        temp_v0 = StgCol_FirstBit(*(s64 *)&sp[4]);
        if (temp_v0 >= 0 && func_002745F8(temp_v0) == 0) {
            *(s32 *)(arg1 + 0xC4) = temp_v0;
        }
    }
}
