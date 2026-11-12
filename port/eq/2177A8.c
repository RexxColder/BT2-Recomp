#include "common.h"

s32 BtlCharApi_IsInTechnique(s32 arg0);
u8 *BtlChar_GetPos(u8 *arg0);
f32 Mathf_Asin(f32 farg0);
void func_001F9D10(u8 *arg0, s32 arg1);
void func_001F9D68(f32 farg0, u8 *arg1);
void func_00208DE8(s32 arg0, s32 *arg1, s32 arg2);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
void func_00210F30(u8 *arg0, s32 *arg1, s32 arg2);
void func_00312650(s32 *arg0, s32 *arg1, s32 *arg2);
f32 func_0029DFD0(s32 *arg0);
void func_00312680(f32 farg0, s32 *arg1, s32 *arg2);
extern f32 D_00385B0C;
extern f32 D_00385B10;
extern f32 D_00385B14;

void func_002177A8(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 sp[4];
    s32 sp10[4];
    f32 sp20[4];
    f32 temp_f0;
    f32 y;
    f32 var_f12;
    u8 *p;

    if (func_00211310((s32)arg0, 0, 1) == 0) {
        p = BtlChar_GetPos(arg0);
        *(s32 *)(p + 0xD8) = 0;
        return;
    }
    if ((arg3 & 0xFF) != 0) {
        func_00208DE8(*(s32 *)(arg0 + 0x1534), sp, 0x11);
        func_00210F30(arg0, sp10, 0x11);
        func_00312650((s32 *)sp20, sp10, sp);
        temp_f0 = func_0029DFD0((s32 *)sp20);
        if (D_00385B0C < temp_f0) {
            func_00312680(1.0f / temp_f0, (s32 *)sp20, (s32 *)sp20);
        }
        y = sp20[1];
        if (y < -1.0f) {
            y = -1.0f;
            sp20[1] = -1.0f;
        }
        if (y > 1.0f) {
            sp20[1] = 1.0f;
        }
        p = BtlChar_GetPos(arg0);
        *(f32 *)(p + 0xD8) = -Mathf_Asin(sp20[1]);
        if (BtlCharApi_IsInTechnique(*(s32 *)(arg0 + 0x1534)) != 0) {
            f32 cur = *(f32 *)(arg0 + 0xA4C);
            *(f32 *)(arg0 + 0xA4C) = cur + ((*(f32 *)(arg0 + 0xA44) - cur) * D_00385B10);
            p = BtlChar_GetPos(arg0);
            *(f32 *)(p + 0xD8) = *(f32 *)(p + 0xD8) + *(f32 *)(arg0 + 0xA4C);
        }
    }
    p = BtlChar_GetPos(arg0);
    var_f12 = *(f32 *)(p + 0xD8) / D_00385B14;
    if (var_f12 < -1.0f) {
        var_f12 = -1.0f;
    }
    if (var_f12 > 1.0f) {
        var_f12 = 1.0f;
    }
    if (var_f12 < 0.0f) {
        func_001F9D68(-var_f12, arg0);
        func_001F9D10(arg0, arg2);
        return;
    }
    func_001F9D68(var_f12, arg0);
    func_001F9D10(arg0, arg1);
}
