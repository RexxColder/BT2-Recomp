#include "common.h"

u8 *BtlPool_Alloc(s32 arg0, s32 arg1);
s32 BtlPool_GetCurrent(s32 arg0);
s32 BtlTask_CreateChildList(s32 arg0, s32 arg1, s32 arg2);
void EftTexSet_Load16(s32 arg0, s32 arg1);
s32 func_00126460();
extern u8 D_00343000[] __attribute__((section(".data")));
extern u8 *D_003878D0;

void func_001DC148(s32 arg0) {
    u8 *temp_s0;
    u8 *temp_v0;

    temp_v0 = BtlPool_Alloc(BtlPool_GetCurrent(arg0), 0x168);
    D_003878D0 = temp_v0;
    memset(temp_v0, 0, 0x168);
    *(s32 *)(D_003878D0 + 0x120) = 0;
    *(s32 *)(D_003878D0 + 0x124) = 0;
    temp_s0 = D_003878D0;
    *(u8 **)(temp_s0 + 0x00) = D_00343000;
    *(s32 *)(temp_s0 + 0x00) = func_00126460(0x118, (s32)D_003878D0);
    EftTexSet_Load16((s32)(temp_s0 + 0x08), func_00126460(0x119));
    *(s32 *)(temp_s0 + 0x114) = func_00126460(0x11A);
    *(s32 *)(temp_s0 + 0x118) = func_00126460(0x117);
    *(s32 *)(D_003878D0 + 0x164) = BtlTask_CreateChildList(arg0, 3, 0x250);
}
