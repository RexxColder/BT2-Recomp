#include "common.h"

s32 BtlScene_IsCharStopped(s32 arg0);
void BtlTask_SetDead(void *arg0);
void func_00151FB0(void *arg0);
s32 func_00152200(s32 arg0, void *arg1);
void func_00182C58(s32 arg0, void *arg1, s32 arg2);
void func_00183410(void *arg0);
void func_00183670(void *arg0);
void func_001837C8(s32 arg0, void *arg1, void *arg2);
void func_00183B78(void *arg0, s32 arg1, s32 arg2);
void func_00183BE0(void *arg0);
void func_00183CC0(void *arg0);

void func_00183228(void *arg0) {
    s16 temp_v0;
    s32 *temp_s1;
    s32 temp_s1_2;
    s32 var_v0;
    u16 temp_v0_2;
    u16 temp_v0_3;
    u16 temp_v0_4;
    u16 temp_v0_5;
    u16 var_v1;
    u16 var_v1_2;
    u8 *temp_s0;

    temp_s0 = *(u8 **)((u8 *)arg0 + 0x38);
    temp_s1 = *(s32 **)(temp_s0 + 0xA54);
    if (BtlScene_IsCharStopped(*(s32 *)(temp_s0 + 0xA40)) == 0) {
        temp_v0 = (s16)(*(u16 *)(temp_s0 + 0xAD0) + 1);
        *(u16 *)(temp_s0 + 0xAD0) = (u16)temp_v0;
        if (temp_v0 == 0x1E) {
            *(u16 *)(temp_s0 + 0xAD6) = (u16)(*(u16 *)(temp_s0 + 0xAD6) & 0xFFFD);
        }
        var_v1 = *(u16 *)(temp_s0 + 0xAD6);
        if (var_v1 & 0x40) {
            temp_v0_2 = (u16)((var_v1 | 0x80) & 0xFFBF);
            *(u16 *)(temp_s0 + 0xAD6) = temp_v0_2;
            var_v1 = temp_v0_2;
        }
        if (var_v1 & 0x80) {
            temp_v0_3 = (u16)(*(u16 *)(temp_s0 + 0xAD2) - 1);
            *(u16 *)(temp_s0 + 0xAD2) = temp_v0_3;
            if ((s16)temp_v0_3 <= 0) {
                *(u16 *)(temp_s0 + 0xAD2) = 0;
                func_00183B78(temp_s0, 2, 1);
                *(u16 *)(temp_s0 + 0xAD6) = (u16)((*(u16 *)(temp_s0 + 0xAD6) | 8) & 0xFF7F);
            }
        }
        func_001837C8(*temp_s1, temp_s0 + 0x7B0, temp_s0);
        func_00151FB0(temp_s0);
        func_00182C58(*temp_s1, arg0, *(s32 *)(temp_s0 + 0xA00));
        temp_s1_2 = func_00152200(*(s32 *)(temp_s0 + 0xA00), temp_s0) != 0;
        func_00183410(temp_s0);
        func_00183CC0(temp_s0);
        func_00183BE0(temp_s0);
        var_v1_2 = *(u16 *)(temp_s0 + 0xAD6);
        temp_v0_4 = (u16)(var_v1_2 | 0x30);
        if (!(var_v1_2 & 0x10)) {
            *(u16 *)(temp_s0 + 0xAD6) = temp_v0_4;
            var_v1_2 = temp_v0_4;
        }
        var_v0 = var_v1_2 & 0x2000;
        if (temp_s1_2 == 0) {
            if (var_v1_2 & 0x400) {
                temp_v0_5 = (u16)((var_v1_2 & ~0x20) | 0x1000);
                *(u16 *)(temp_s0 + 0xAD6) = temp_v0_5;
                var_v1_2 = temp_v0_5;
            }
            var_v0 = var_v1_2 & 0x2000;
        }
        if (var_v0 != 0) {
            BtlTask_SetDead(arg0);
            return;
        }
        if (var_v1_2 & 0x100) {
            func_00183670(arg0);
        }
    }
}
