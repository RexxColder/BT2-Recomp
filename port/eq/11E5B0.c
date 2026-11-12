#include "common.h"

void ColBox_GetCenter(s32 arg0, s32 arg1);
void ColBox_GetHalf(s32 arg0, s32 arg1);
s32 BtlStage_FindZoneNear(s32 arg0, s32 arg1);
s32 func_00273248(s32 arg0);
void func_0011CB00(void);
void func_0011CB18(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_0011E4F8(void);

void func_0011E5B0(s32 arg0, s32 arg1) {
    u8 fr[0x60];
    s32 temp_s0_2;

    if (arg1 == 0 || *(s32 *)arg1 == 0) {
        return;
    }
    memset((void *)fr, 0, 0x30);
    *(f32 *)(fr + 0x20) = *(f32 *)(arg1 + 0x14);
    *(s32 *)fr = arg1;
    ColBox_GetCenter(arg1 + 4, (s32)(fr + 0x10));
    ColBox_GetHalf(arg1 + 4, (s32)(fr + 0x50));
    *(f32 *)(fr + 0x14) = *(f32 *)(fr + 0x14) - *(f32 *)(fr + 0x54) * 0.5f;
    temp_s0_2 = func_00273248(BtlStage_FindZoneNear(arg0, (s32)(fr + 0x10)));
    func_0011CB00();
    func_0011CB18((s32)(fr + 0x30), temp_s0_2, arg1 + 0x1C, (s32)fr, (s32)func_0011E4F8);
}
