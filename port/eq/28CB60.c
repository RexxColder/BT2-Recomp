#include "common.h"

void Rand_Seed(u32 seed);
extern u32 D_00387D68[2];
extern s32 gRandIndex;
extern u32 gRandState[624] __attribute__((section(".data")));

s32 func_0028CB60(void) {
    s32 k;
    s32 idx;
    u32 y;

    if (gRandIndex >= 0x270) {
        if (gRandIndex == 0x271) {
            Rand_Seed(0x1571);
        }
        for (k = 0; k < 227; k++) {
            y = (gRandState[k] & 0x80000000) | (gRandState[k + 1] & 0x7FFFFFFF);
            gRandState[k] = gRandState[k + 397] ^ (y >> 1) ^ D_00387D68[y & 1];
        }
        for (k = 227; k < 623; k++) {
            y = (gRandState[k] & 0x80000000) | (gRandState[k + 1] & 0x7FFFFFFF);
            gRandState[k] = gRandState[k - 227] ^ (y >> 1) ^ D_00387D68[y & 1];
        }
        gRandIndex = 0;
        y = (gRandState[623] & 0x80000000) | (gRandState[0] & 0x7FFFFFFF);
        gRandState[623] = gRandState[396] ^ (y >> 1) ^ D_00387D68[y & 1];
    }

    idx = gRandIndex;
    gRandIndex = idx + 1;
    y = gRandState[idx];
    y ^= y >> 11;
    y ^= (y << 7) & 0x9D2C5680;
    y ^= (y << 15) & 0xEFC60000;
    y ^= y >> 18;
    return (s32)y;
}
