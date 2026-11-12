#include "common.h"

void *memset(void *arg0, s32 arg1, u32 arg2);
s32 BtlTaskList_AddTail(s32 arg0, void *arg1, void *arg2, s32 arg3);
extern u8 D_00342A10[];
extern f32 D_00385198;
extern f32 D_0038519C;
extern u8 *D_003878AC;

void func_001C84E8(void *arg0) {
    s32 sp[24];
    f32 *pf;
    u8 *var_s0;
    s32 *var_v0;
    s64 temp_a3;

    memset(sp, 0, 0x60);
    var_s0 = (u8 *)arg0;
    var_v0 = sp;
    do {
        temp_a3 = *(s64 *)(var_s0 + 0x18);
        *(s64 *)((u8 *)var_v0 + 0x0) = *(s64 *)(var_s0 + 0x0);
        *(s64 *)((u8 *)var_v0 + 0x8) = *(s64 *)(var_s0 + 0x8);
        *(s64 *)((u8 *)var_v0 + 0x10) = *(s64 *)(var_s0 + 0x10);
        *(s64 *)((u8 *)var_v0 + 0x18) = temp_a3;
        var_s0 += 0x20;
        var_v0 = (s32 *)((u8 *)var_v0 + 0x20);
    } while (var_s0 != (u8 *)arg0 + 0x60);

    pf = (f32 *)&sp[16];
    if (sp[19] < 3) {
        sp[19] = 3;
    }
    if (pf[0] < 0.0f) {
        pf[0] = D_00385198;
    }
    if (pf[1] < 0.0f) {
        pf[1] = 0.0f;
    }
    if (pf[2] < D_0038519C) {
        pf[2] = D_0038519C;
    }
    *(f32 *)&sp[11] = 1.0f;
    BtlTaskList_AddTail(*(s32 *)(D_003878AC + 0x208), D_00342A10, sp, (s32)temp_a3);
}
