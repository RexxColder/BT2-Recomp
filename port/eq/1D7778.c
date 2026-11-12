#include "common.h"

void *func_001D7708(void);
void func_00129C28(void *arg0, void *arg1);
extern u8 *D_00387E9C;

s32 func_001D7778(u8 *arg0, u8 *arg1, u8 *arg2, u8 arg3, u8 arg4, u8 arg5, u8 arg6,
                  u8 arg7, f32 farg0, f32 farg1, f32 farg2, f32 farg3, f32 farg4,
                  f32 farg5, f32 farg6, f32 farg7, f32 farg8, f32 farg9) {
    u8 blkA[16];
    u8 blkB[16];
    u8 blkC[16];
    u8 *node;
    f32 negA;
    f32 invLen;
    s32 count;

    __builtin_memcpy(blkA, arg0, 16);
    __builtin_memcpy(blkB, arg1, 16);
    __builtin_memcpy(blkC, arg2, 16);

    node = func_001D7708();
    if (node == NULL) {
        return 0;
    }

    func_00129C28(node, blkA);
    func_00129C28(node + 0x10, blkB);
    func_00129C28(node + 0x20, blkC);

    *(f32 *)(node + 0x30) = farg0;
    negA = 0.0f - farg4;
    *(f32 *)(node + 0x34) = farg1;
    *(f32 *)(node + 0x38) = farg2;
    if (farg3 == 0.0f) {
        *(f32 *)(node + 0x3C) = 0.0f;
    } else {
        *(f32 *)(node + 0x3C) = 1.0f / farg3;
    }
    *(f32 *)(node + 0x4C) = farg6;
    *(f32 *)(node + 0x50) = farg7;
    *(f32 *)(node + 0x54) = farg8 * 30.0f;
    *(u8 *)(node + 0x5C) = arg3;
    *(u8 *)(node + 0x5D) = arg4;
    *(u8 *)(node + 0x5E) = arg5;
    *(u8 *)(node + 0x61) = arg6;
    *(u8 *)(node + 0x62) = arg7;
    *(u8 *)(node + 0x63) = 1;
    *(u8 *)(node + 0x60) = 0;
    *(f32 *)(node + 0x44) = negA;
    *(u8 *)(node + 0x5F) = 0;
    *(u8 *)(node + 0x64) = 0;
    *(f32 *)(node + 0x40) = farg4;
    if (farg5 != 0.0f) {
        *(f32 *)(node + 0x44) = negA / (farg5 * 30.0f);
    }
    *(f32 *)(node + 0x48) = 0.0f;
    *(f32 *)(node + 0x58) = farg9;
    *(u8 *)(node + 0x60) = *(u8 *)(node + 0x60) | 2;

    count = *(s32 *)(D_00387E9C + 0x1444) + 1;
    *(s32 *)(D_00387E9C + 0x1444) = count;
    return count;
}
