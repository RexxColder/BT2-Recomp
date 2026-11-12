#include "common.h"

s32 BtlScene_IsCharStopped(s32 arg0);
void func_00129C38(void *arg0, void *arg1);
void func_0019CFA0(void *arg0, s32 arg1, s32 arg2, s32 arg3);

void func_0019CA70(u8 *arg0) {
    u16 temp_v1;
    u8 *temp_s0;

    temp_s0 = *(u8 **)(arg0 + 0x38);
    if (BtlScene_IsCharStopped(*(s32 *)(temp_s0 + 0xC1C)) == 0) {
        if (*(u16 *)(arg0 + 8) & 1 & 0xFFFF) {
            func_00129C38(temp_s0 + 0xB40, arg0 + 0x10);
            temp_v1 = *(u16 *)(temp_s0 + 0xC24);
            if (!(temp_v1 & 2)) {
                if (temp_v1 & 0x40) {
                    func_0019CFA0(arg0, *(s32 *)temp_s0, *(s32 *)(temp_s0 + 0xC1C), 1);
                }
                *(u16 *)(temp_s0 + 0xC24) = (u16)(*(u16 *)(temp_s0 + 0xC24) | 2);
            }
        }
        if (*(u16 *)(arg0 + 8) & 4) {
            *(u16 *)(temp_s0 + 0xC24) = (u16)(*(u16 *)(temp_s0 + 0xC24) | 4);
        }
    }
}
