#include "common.h"

s32 BtlChar_GetPos(s32 arg0);
s32 func_003126C8(s32 arg0, s32 arg1);

void func_00211828(u8 *arg0) {
    s32 temp_v0;
    u8 *temp_v1;

    func_003126C8((s32)(arg0 + 0x950), BtlChar_GetPos((s32)arg0));
    func_003126C8((s32)(arg0 + 0x960), BtlChar_GetPos((s32)arg0) + 0x10);
    temp_v1 = *(u8 **)(arg0 + 0x1530);
    temp_v0 = *(s32 *)(temp_v1 + 0xF44);
    if (temp_v0 != 0) {
        func_003126C8((s32)(arg0 + 0x970), temp_v0);
        return;
    }
    func_003126C8((s32)(arg0 + 0x970), *(s32 *)(temp_v1 + 0xF40));
}
