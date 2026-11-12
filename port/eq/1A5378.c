#include "common.h"

extern s32 D_003425C8[] __attribute__((section(".data")));
extern s32 D_00342618[] __attribute__((section(".data")));
extern s32 D_00342578[] __attribute__((section(".data")));
extern s32 D_00387828;
extern s32 D_0038782C;
extern u8 *D_00387830;

void *memset(void *, s32, u32);
void *BtlPool_Alloc(s32 arg0, s32 arg1);
s32 BtlPool_GetCurrent(void);
s32 BtlTask_CreateChildList(s32 arg0, s32 arg1, s32 arg2);
void EftTexSet_Load16(s32 arg0, s32 arg1);
void EftTexSet_Load32(s32 arg0, s32 arg1);
s32 func_00126460(s32 arg0);

void func_001A5378(s32 arg0) {
    u8 *d;
    u8 *s4;
    s32 *var_s0;
    s32 *var_s1;
    s32 *var_s1_2;
    s32 *var_s2;
    s32 s3;
    s32 temp_a1;
    s32 temp_s0;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v0_5;

    s3 = 0;
    d = BtlPool_Alloc(BtlPool_GetCurrent(), 0x750);
    D_00387830 = d;
    memset(d, 0, 0x750);
    *(f32 *)(D_00387830 + 0x748) = 1.0f;
    s4 = d + 0x340;
    var_s2 = (s32 *)(d + 0x6F0);
    var_s1 = (s32 *)(d + 0x6A4);
    do {
        temp_a1 = D_003425C8[s3];
        temp_s0 = D_00342618[s3];
        s3 += 1;
        if (temp_a1 >= 0) {
            *var_s1 = func_00126460(temp_a1);
        } else {
            *var_s1 = 0;
        }
        if (temp_s0 < 0) {
            *var_s2 = 0;
        } else {
            *var_s2 = func_00126460(temp_s0);
        }
        var_s2 += 1;
        var_s1 += 1;
    } while (s3 < 0x13);

    if (D_0038782C >= 0) {
        temp_v0_3 = func_00126460(D_0038782C);
        *(s32 *)(s4 + 0x360) = temp_v0_3;
        EftTexSet_Load16((s32)(s4 + 0x258), temp_v0_3);
    }
    if (D_00387828 >= 0) {
        temp_v0_4 = func_00126460(D_00387828);
        *(s32 *)(s4 + 0x208) = temp_v0_4;
        EftTexSet_Load32((s32)s4, temp_v0_4);
    } else {
        *(s32 *)(s4 + 0x208) = 0;
    }

    var_s0 = (s32 *)(s4 + 0x20C);
    var_s1_2 = D_00342578;
    s3 = 0;
    do {
        temp_v0_5 = *var_s1_2;
        var_s1_2 += 1;
        if (temp_v0_5 >= 0) {
            s3 += 1;
            *var_s0 = func_00126460(temp_v0_5);
        } else {
            *var_s0 = 0;
            s3 += 1;
        }
        var_s0 += 1;
    } while (s3 < 0x13);

    *(s32 *)(D_00387830 + 0x740) = func_00126460(0x52);
    *(s32 *)(d + 0x0) = func_00126460(0x25);
    *(s32 *)(d + 0x4) = func_00126460(0x23);
    EftTexSet_Load16((s32)(d + 0x8), func_00126460(0x24));
    *(s32 *)(D_00387830 + 0x74C) = BtlTask_CreateChildList(arg0, 0x14, 0x90);
}
