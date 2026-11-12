#include "common.h"

s32 GfxLens_Start(void *arg0, s32 arg1, s32 arg2, s32 arg3, f32 farg4);
s64 __fixunssfdi(f32 arg0);
void func_00129C28(void *arg0, void *arg1);
void *memset(void *arg0, s32 arg1, u32 arg2);

void func_001B52D8(void *arg0, void *arg1) {
    u8 *var_s0;
    s64 res1;
    s64 res2;
    s64 res3;
    s64 res4;
    s64 var_s2;
    s64 var_s1;

    var_s0 = *(u8 **)((u8 *)arg0 + 0x38);
    memset(var_s0, 0, 0x60);
    *(s64 *)(var_s0 + 0x0) = *(s64 *)((u8 *)arg1 + 0x0);
    *(s64 *)(var_s0 + 0x8) = *(s64 *)((u8 *)arg1 + 0x8);
    *(s64 *)(var_s0 + 0x10) = *(s64 *)((u8 *)arg1 + 0x10);
    *(s64 *)(var_s0 + 0x18) = *(s64 *)((u8 *)arg1 + 0x18);
    *(s64 *)(var_s0 + 0x20) = *(s64 *)((u8 *)arg1 + 0x20);
    *(s64 *)(var_s0 + 0x28) = *(s64 *)((u8 *)arg1 + 0x28);
    *(s64 *)(var_s0 + 0x30) = *(s64 *)((u8 *)arg1 + 0x30);
    *(s64 *)(var_s0 + 0x38) = *(s64 *)((u8 *)arg1 + 0x38);
    func_00129C28(var_s0 + 0x40, var_s0);
    res1 = __fixunssfdi(*(f32 *)(var_s0 + 0x10));
    res2 = __fixunssfdi(*(f32 *)(var_s0 + 0x1C));
    res3 = __fixunssfdi(*(f32 *)(var_s0 + 0x18));
    res4 = __fixunssfdi(*(f32 *)(var_s0 + 0x14));
    var_s2 = res1;
    var_s2 |= res2 << 24;
    var_s1 = res3 << 16;
    var_s1 |= res4 << 8;
    var_s2 |= var_s1;
    *(s32 *)(var_s0 + 0x50) = GfxLens_Start(var_s0, *(s32 *)(var_s0 + 0x28), (s32)var_s2,
                                            *(s32 *)(var_s0 + 0x24), *(f32 *)(var_s0 + 0x20));
}
