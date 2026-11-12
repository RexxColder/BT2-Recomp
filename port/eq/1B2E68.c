#include "common.h"

void EftChain2_SetTex(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void memset(void *arg0, s32 arg1, u32 arg2);
extern f32 D_00384FBC;
extern u8 *D_00387870;

void func_001B2E68(s32 arg0, s32 arg1) {
    u8 *s0;
    s32 a1;
    f32 f1;
    s32 i;

    s0 = *(u8 **)(arg0 + 0x38);
    memset(s0, 0, 0xAB0);
    a1 = *(s32 *)(s0 + 0xA40);
    for (i = 0; i < 8; i++) {
        *(s64 *)(s0 + i * 8) = *(s64 *)(arg1 + i * 8);
    }
    *(s32 *)(s0 + 0xA40) = a1 | 1;
    f1 = *(f32 *)(arg1 + 8);
    if (f1 <= 0.0f) {
        *(s32 *)(s0 + 0xA40) = a1 | 9;
    } else {
        *(f32 *)(s0 + 0xA54) = 0.0f;
        *(f32 *)(s0 + 0xA58) = f1 * 30.0f;
    }
    *(f32 *)(s0 + 0xA84) = D_00384FBC;
    *(s32 *)(s0 + 0xA50) = 7;
    *(f32 *)(s0 + 0xA6C) = D_00384FBC;
    *(f32 *)(s0 + 0xA80) = D_00384FBC;
    *(f32 *)(s0 + 0xA74) = D_00384FBC;
    *(s32 *)(s0 + 0xA68) = 0;
    *(s32 *)(s0 + 0xA78) = 0;
    *(s32 *)(s0 + 0xA7C) = 0;
    *(s32 *)(s0 + 0xA70) = 0;
    EftChain2_SetTex((s32)s0, *(s32 *)(arg1 + 0x34), *(s32 *)(arg1 + 0x30), *(s32 *)(arg1 + 0x30));
    *(s32 *)(D_00387870 + 8) = *(s32 *)(D_00387870 + 8) + 1;
}
