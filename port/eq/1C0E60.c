#include "common.h"

void BtlTask_SetDead(void *arg0, s32 arg1, s32 arg2);
void func_00151FB0(void *arg0);
s32 func_00152200(s32 arg0, void *arg1);
void func_00152608(s32 arg0, void *arg1, s32 arg2);
void func_001C0F50(void *arg0);

void func_001C0E60(u8 *arg0) {
    s32 var_v1;
    u8 *temp_s0;
    u8 *temp_s1;

    temp_s1 = *(u8 **)(arg0 + 0x38);
    temp_s0 = temp_s1 + 0x70;
    func_00152608(*(s32 *)(temp_s1 + 0), temp_s1 + 0x820, *(s32 *)(temp_s1 + 0xAC8));
    func_00151FB0(temp_s0);
    func_001C0F50(arg0);
    if (*(s64 *)(temp_s1 + 0xAC0) != 0) {
        *(s32 *)(temp_s1 + 0xACC) = 2;
    }
    if (func_00152200(*(s32 *)(temp_s1 + 4), temp_s0) == 0) {
        var_v1 = *(s32 *)(temp_s1 + 0xACC);
        if (var_v1 == 2) {
            var_v1 = 3;
            *(s32 *)(temp_s1 + 0xACC) = 3;
        }
    } else {
        var_v1 = *(s32 *)(temp_s1 + 0xACC);
    }
    if (var_v1 == 3) {
        BtlTask_SetDead(arg0, 2, 3);
    }
}
