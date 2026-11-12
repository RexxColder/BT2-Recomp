#include "common.h"

void BtlScene_FillPackEntries(s32 arg0, u8 *arg1, s32 arg2, s32 arg3);
void BtlTask_CreateChildList(s32 arg0, s32 arg1, s32 arg2);
void func_00148000(s32 arg0);
s32 func_0014E258(s32 arg0, u8 *arg1);
void *memset(void *arg0, s32 arg1, u32 arg2);
extern f32 D_003847D8;
extern f32 D_003847DC;

void func_00168DE0(u8 *arg0, s32 arg1) {
    u8 *temp_s0;

    temp_s0 = *(u8 **)(arg0 + 0x38);
    func_00148000(0x1E98);
    memset(temp_s0, 0, 0x1E98);
    BtlScene_FillPackEntries(arg1, temp_s0 + 0x1E80, 1, func_0014E258(arg1, temp_s0));
    BtlTask_CreateChildList((s32)arg0, 2, 0xB50);
    *(f32 *)(temp_s0 + 0x1E94) = 1.0f;
    *(f32 *)(temp_s0 + 0x1E90) = D_003847DC;
    *(f32 *)(temp_s0 + 0x1E8C) = D_003847D8;
    *(f32 *)(temp_s0 + 0x1E88) = -1.0f;
    *(s32 *)(temp_s0 + 0x1E84) = 0;
}
