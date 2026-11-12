#include "common.h"

void Rand_Seed(u32 arg0);
extern s32 gRandState[624] __attribute__((section(".data")));

void func_0028C9C8(s32 *arg0, u32 arg1) {
    u32 var_a3;
    u32 var_t2;
    u32 temp_t2;
    u32 temp_v0;
    u32 x;
    u32 lo;
    s32 var_t1;
    s32 var_a3_2;
    s32 *var_t0;
    s32 *var_a1;

    Rand_Seed(0x012BD6AA);
    var_t1 = 1;
    var_a3 = (arg1 < 0x270U) ? 0x270U : arg1;
    var_t2 = 0;
    if (var_a3 != 0) {
        var_t0 = &gRandState[1];
        do {
            temp_v0 = (u32)var_t0[-1];
            x = temp_v0 ^ (temp_v0 >> 30);
            lo = x * 0x19660DU;
            temp_t2 = var_t2 + 1;
            *var_t0 = (s32)(((u32)*var_t0 ^ lo) + (u32)arg0[var_t2] + var_t2);
            var_t2 = (temp_t2 >= arg1) ? 0U : temp_t2;
            var_t0 += 1;
            var_t1 += 1;
            if (var_t1 >= 0x270) {
                var_t0 = &gRandState[1];
                var_t1 = 1;
                gRandState[0] = gRandState[623];
            }
            var_a3 -= 1;
        } while (var_a3 != 0);
    }
    var_a1 = &gRandState[var_t1];
    var_a3_2 = 0x26F;
    temp_v0 = (u32)var_a1[-1];
    do {
        x = temp_v0 ^ (temp_v0 >> 30);
        lo = x * 0x5D588B65U;
        *var_a1 = (s32)(((u32)*var_a1 ^ lo) - (u32)var_t1);
        var_t1 += 1;
        var_a1 += 1;
        if (var_t1 >= 0x270) {
            var_a1 = &gRandState[1];
            var_t1 = 1;
            gRandState[0] = gRandState[623];
        }
        var_a3_2 -= 1;
        if (var_a3_2 != 0) {
            temp_v0 = (u32)var_a1[-1];
        }
    } while (var_a3_2 != 0);
    gRandState[0] = (s32)0x80000000;
}
