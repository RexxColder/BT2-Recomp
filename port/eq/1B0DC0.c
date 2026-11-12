#include "common.h"

void EftChain2_SetTex(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3) {
    u8 *a = arg1 + arg2 * 0x10;
    u8 *t = arg1 + arg3 * 0x10;

    *(s64 *)(arg0 + 0xA88) = *(s64 *)(a + 0);
    *(s64 *)(arg0 + 0xA90) = *(s64 *)(a + 8);
    *(s64 *)(arg0 + 0xA98) = *(s64 *)(t + 0);
    *(s32 *)(arg0 + 0x30) = arg3;
    *(s64 *)(arg0 + 0xAA0) = *(s64 *)(t + 8);
}
