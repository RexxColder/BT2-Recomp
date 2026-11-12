#include "common.h"

void Mtx_StoreIdentity(void *arg0);
void func_00128810(void *arg0, void *arg1);
void func_00129BD0(void *arg0, void *arg1, f32 farg0);
void func_00129C28(void *arg0, void *arg1);
s32 func_001EDB20(void *arg0, s32 arg1);
void func_001EDC20(s32 arg0, s32 arg1);
void func_001EDD40(s32 arg0, void *arg1);
void func_00208DE8(s32 arg0, void *arg1, s32 arg2);
s32 rand(void);
extern f32 D_00384F08;
extern u8 *D_0038784C;

void func_001AC388(u8 *arg0) {
    s32 sp[16];
    f32 temp_f1;
    f32 temp_f20;
    f32 temp_f21;
    f32 var_f1;
    s32 temp_v0;
    u8 *temp_s0;
    u8 *temp_s1;
    u8 *temp_s2;

    temp_s1 = *(u8 **)(arg0 + 0x38);
    temp_s2 = temp_s1 + 0x50;
    temp_f20 = D_00384F08;
    temp_s0 = temp_s1 + 0x70;
    func_00208DE8(*(s16 *)(temp_s1 + 0x12), temp_s1 + 0x40, *(s16 *)(temp_s1 + 0x14));
    func_00208DE8(*(s16 *)(temp_s1 + 0x12), temp_s2, *(s16 *)(temp_s1 + 0x14));
    func_00208DE8(*(s16 *)(temp_s1 + 0x12), temp_s1 + 0x60, 0x11);
    func_00129C28(temp_s0, temp_s1);
    temp_f1 = *(f32 *)(temp_s1 + 0x28);
    *(f32 *)(temp_s1 + 0xCC) = *(f32 *)(temp_s1 + 0x20);
    *(f32 *)(temp_s1 + 0xD0) = temp_f1;
    *(s32 *)(temp_s1 + 0xC4) = *(s16 *)(temp_s1 + 0x1C);
    *(f32 *)(temp_s1 + 0xD4) = temp_f1 * 5.0f;
    *(f32 *)(temp_s1 + 0xE0) = 0.5f;
    *(s16 *)(temp_s1 + 0xEA) = 0;
    *(s16 *)(temp_s1 + 0xE6) = 0;
    temp_f21 = ((((f32)rand() / temp_f20) * 10.0f) - 5.0f) + 32.0f;
    *(f32 *)(temp_s1 + 0xDC) = temp_f21;
    var_f1 = temp_f21;
    if (!(((f32)rand() / temp_f20) < 0.5f)) {
        var_f1 = -temp_f21;
    }
    *(f32 *)(temp_s1 + 0xDC) = var_f1;
    func_00129BD0(temp_s0, temp_s0, *(f32 *)(temp_s1 + 0xCC));
    *(s32 *)(temp_s1 + 0xC8) = 0;
    *(s16 *)(temp_s1 + 0x1C4) = 0xF;
    Mtx_StoreIdentity(sp);
    temp_v0 = func_001EDB20(temp_s1 + 0xEC, *(s32 *)(D_0038784C + 0x54));
    *(s32 *)(temp_s1 + 0x11C) = temp_v0;
    if (temp_v0 != -1) {
        func_001EDC20(temp_v0, 0);
        func_00128810(sp, temp_s2);
        func_001EDD40(*(s32 *)(temp_s1 + 0x11C), sp);
    }
    *(u8 **)(temp_s1 + 0x1C0) = D_0038784C + 8;
}
