#include "common.h"

u8 *BtlPool_Alloc(s32 arg0, s32 arg1);
s32 BtlPool_GetCurrent(s32 arg0);
s32 BtlTask_CreateChildList(s32 arg0, s32 arg1, s32 arg2);
void EftTexSet_Load16(s32 arg0, s32 arg1);
s32 func_00126460();
extern u8 D_00342DB0[] __attribute__((section(".data")));
extern u8 *D_003878C8;

void func_001CCD60(s32 arg0) {
    u8 *temp_s0;
    u8 *temp_v0;

    temp_v0 = BtlPool_Alloc(BtlPool_GetCurrent(arg0), 0x258);
    D_003878C8 = temp_v0;
    memset(temp_v0, 0, 0x258);
    *(s32 *)(D_003878C8 + 0x210) = 0;
    *(s32 *)(D_003878C8 + 0x214) = 0;
    temp_s0 = D_003878C8;
    *(u8 **)(temp_s0 + 0x00) = D_00342DB0;
    *(s32 *)(temp_s0 + 0x00) = func_00126460(0x114, (s32)D_003878C8);
    EftTexSet_Load16((s32)(temp_s0 + 0x08), func_00126460(0x115));
    *(s32 *)(temp_s0 + 0x114) = func_00126460(0x116);
    *(s32 *)(temp_s0 + 0x118) = func_00126460(0x113);
    *(s32 *)(D_003878C8 + 0x254) = BtlTask_CreateChildList(arg0, 3, 0x130);
}
