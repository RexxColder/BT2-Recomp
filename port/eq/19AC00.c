#include "common.h"

void func_0019AE80(void *arg0);
void func_0019B078(void *arg0);
void func_0019B0E8(void *arg0);
void func_0019B150(void *arg0);
void func_0019B198(void *arg0);
void func_0019B2D0(void *arg0);
s32 func_0019B308(void *arg0);
void func_0019B328(void *arg0);
void func_0019B348(void *arg0, s32 arg1);
void func_00208DE8(s32 arg0, void *arg1, s32 arg2);
void Vec3_Sub(void *a0, void *a1, void *a2);
void Vec3_Normalize(void *a0, void *a1);
void func_00129C38(void *a0, void *a1);
s32 BtlTask_SetDead(void *arg0);

void func_0019AC00(void *arg0) {
    s32 sp[4];
    s32 sp10[4];
    s32 sp20[4];
    u8 *var_s1;
    u8 *var_s2;
    u8 *var_s4;
    void *var_s3;
    void *var_s0;
    s32 temp_v0;
    s32 temp_v1;

    var_s1 = arg0;
    var_s4 = *(u8 **)(var_s1 + 0x38);
    var_s2 = var_s4;
    temp_v1 = var_s1[1];
    if (temp_v1 == 1) {
        var_s1[1] = 2;
    } else if (temp_v1 < 2) {
        if (temp_v1 == 0) {
            func_0019AE80(arg0);
            func_0019B198(arg0);
            var_s2 = *(u8 **)(var_s1 + 0x38);
            var_s1[1] = var_s1[1] + 1;
        }
    } else if (temp_v1 == 2) {
        func_0019B0E8(arg0);
        temp_v0 = func_0019B308(arg0);
        if (temp_v0 == 0) {
            *(u16 *)(var_s4 + 0x58) = (u16)(*(u16 *)(var_s4 + 0x58) | 2);
        }
        if (!(*(u16 *)(var_s4 + 0x58) & 2)) {
            var_s2 = *(u8 **)(var_s1 + 0x38);
        } else {
            if (temp_v0 != 0) {
                func_0019B150(arg0);
                func_0019B328(arg0);
            }
            var_s2 = *(u8 **)(var_s1 + 0x38);
            var_s1[1] = var_s1[1] + 1;
        }
    }

    if (*(s32 *)(var_s2 + 0x54) == 1) {
        func_00208DE8(*(s32 *)(var_s2 + 0x50), sp, 7);
        var_s3 = sp10;
        func_00208DE8(*(s32 *)(var_s2 + 0x50), var_s3, 6);
    } else {
        func_00208DE8(*(s32 *)(var_s2 + 0x50), sp, 0x23);
        var_s3 = sp10;
        func_00208DE8(*(s32 *)(var_s2 + 0x50), var_s3, 0x22);
    }
    var_s0 = sp20;
    Vec3_Sub(var_s0, sp, var_s3);
    Vec3_Normalize(var_s0, var_s0);
    func_00129C38(var_s2 + 0x40, var_s0);
    func_00129C38(var_s2 + 0x30, sp);
    func_0019B2D0(arg0);
    func_0019B078(arg0);
    func_0019B308(arg0);
    func_0019B0E8(arg0);
    if (*(u16 *)(var_s4 + 0x58) & 4) {
        func_0019B348(arg0, *(s32 *)(var_s4 + 0x50));
        BtlTask_SetDead(arg0);
    }
}
