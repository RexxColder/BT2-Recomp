#include "common.h"

void EftPtcl3_SetStopDelay(s32 arg0, f32 farg0);
void EftPtcl3_Stop(s32 arg0);
void FlashShapePool_Term(s32 arg0);
void func_001817D0(void *arg0);
s32 func_0019F940(s32 arg0, s32 arg1);
void func_001E71D8(s32 arg0, s32 arg1);

s32 func_0019FF00(u8 *arg0) {
    s32 var_s1;
    u8 *var_s2;
    u8 *var_s0;
    u8 *var_a0;

    var_s1 = 1;
    var_s2 = *(u8 **)(arg0 + 0x38);
    var_s0 = var_s2 + 0x2C;
    var_a0 = var_s0;
    do {
        var_s0 += 4;
        var_s1 -= 1;
        func_001E71D8((s32)var_a0, 0);
        var_a0 = var_s0;
    } while (var_s1 >= 0);
    var_s0 = var_s2 + 0x2C;
    var_s1 = 1;
    var_a0 = var_s0;
loop_3:
    var_s0 += 4;
    var_s1 -= 1;
    FlashShapePool_Term((s32)var_a0);
    if (var_s1 >= 0) {
        var_a0 = var_s0;
        goto loop_3;
    }
    EftPtcl3_SetStopDelay(*(s32 *)(var_s2 + 0x34), 1.0f);
    EftPtcl3_Stop(*(s32 *)(var_s2 + 0x34));
    *(s32 *)(var_s2 + 0x34) = 0;
    func_001817D0(var_s2 + 0x38);
    return func_0019F940(*(s32 *)(var_s2 + 0x3C), 0);
}
