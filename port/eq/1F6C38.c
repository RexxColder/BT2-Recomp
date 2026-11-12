#include "common.h"

void func_001F5A98(void);
void func_00212DB0(s32 arg0, s32 arg1);
u8 *func_0028BAA8(s32 arg0);
extern u8 **D_003876A0;
extern u8 *D_00387930;

void func_001F6C38(s32 arg0) {
    s32 temp_s0;
    u8 *temp_v0;
    u8 *temp_v1;
    u8 *temp_v1_2;

    temp_s0 = arg0 * 0x1550;
    temp_v0 = func_0028BAA8(0x70);
    D_00387930 = temp_v0;
    memset(temp_v0, 0, 0x70);
    *(u8 **)D_00387930 = func_0028BAA8(temp_s0);
    memset(*(u8 **)D_00387930, 0, temp_s0);
    *(s32 *)(D_00387930 + 4) = arg0;
    temp_v1 = *D_003876A0;
    *(u8 **)(D_00387930 + 0x14) = temp_v1 + (((u32) *(u32 *)(temp_v1 + 4) >> 2) * 4);
    temp_v1_2 = *D_003876A0;
    *(u8 **)(D_00387930 + 0x1C) = temp_v1_2 + (((u32) *(u32 *)(temp_v1_2 + 0x18) >> 2) * 4);
    func_00212DB0((s32)D_003876A0, (s32)D_00387930);
    func_001F5A98();
}
