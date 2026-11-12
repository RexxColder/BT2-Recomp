#include "common.h"

void EftChain2_Stop(s32 arg0);
void EftPtcl3_Stop(s32 arg0);
void FlashShapePool_Term(void *arg0);
void func_0018E098(s32 arg0);
void func_001CC9E8(s32 arg0);
void func_001E71D8(void *arg0, s32 arg1);

void func_001A8980(u8 *arg0) {
    u8 *var_s2;
    s32 temp_a0;
    s32 var_s1;

    var_s2 = *(u8 **)(arg0 + 0x38);
    temp_a0 = *(s32 *)(var_s2 + 0x360);
    if (temp_a0 != 0) {
        func_0018E098(temp_a0);
        *(s32 *)(var_s2 + 0x360) = 0;
    }
    var_s1 = 3;
    do {
        temp_a0 = *(s32 *)(var_s2 + 0x364 + (3 - var_s1) * 4);
        if (temp_a0 != 0) {
            EftPtcl3_Stop(temp_a0);
            *(s32 *)(var_s2 + 0x364 + (3 - var_s1) * 4) = 0;
        }
        var_s1 -= 1;
    } while (var_s1 >= 0);
    var_s1 = 3;
    do {
        func_001E71D8(var_s2 + 0x374 + (3 - var_s1) * 4, 0xF);
        var_s1 -= 1;
    } while (var_s1 >= 0);
    var_s1 = 3;
    do {
        FlashShapePool_Term(var_s2 + 0x374 + (3 - var_s1) * 4);
        var_s1 -= 1;
    } while (var_s1 >= 0);
    temp_a0 = *(s32 *)(var_s2 + 0x384);
    if (temp_a0 != 0) {
        EftChain2_Stop(temp_a0);
        *(s32 *)(var_s2 + 0x384) = 0;
    }
    temp_a0 = *(s32 *)(var_s2 + 0x388);
    if (temp_a0 != 0) {
        func_001CC9E8(temp_a0);
        *(s32 *)(var_s2 + 0x388) = 0;
    }
}
