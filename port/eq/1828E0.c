#include "common.h"

s32 BtlScene_IsCharStopped(s32 arg0);
void func_00129C38(u8 *arg0, u8 *arg1, s32 arg2);
void func_00182380(u8 *arg0, s32 arg1, s32 arg2);

void func_001828E0(u8 *arg0) {
    u8 *temp_s0;
    u8 *temp_s2;
    s32 temp_a2;
    s32 var_a1;
    u16 temp_v0;

    temp_s0 = *(u8 **)(arg0 + 0x38);
    temp_s2 = temp_s0 + 0xA00;
    if (BtlScene_IsCharStopped(*(s32 *)*(u8 **)(temp_s2 + 0x28)) == 0) {
        temp_a2 = *(s32 *)(temp_s0 + 0xA80) & ~0x40;
        *(s32 *)(temp_s0 + 0xA80) = temp_a2;
        temp_v0 = *(u16 *)(arg0 + 8);
        var_a1 = temp_v0 & 1;
        if (temp_v0 & 4) {
            *(s32 *)(temp_s0 + 0xA80) = (temp_a2 & ~0x10) | 2;
            var_a1 = !(*(u8 *)temp_s2 & 2) ? 1 : var_a1;
        }
        if (var_a1 != 0) {
            func_00129C38(temp_s0 + 0xA40, arg0 + 0x10, temp_a2);
            if (!(*(u8 *)temp_s2 & 8)) {
                func_00182380(arg0, *(s32 *)(temp_s2 + 0x24), 1);
            }
            *(s32 *)(temp_s0 + 0xA80) = (*(s32 *)(temp_s0 + 0xA80) | 0x40) & ~0x20;
        }
    }
}
