#include "common.h"

void *func_001D6F80(void);
void func_00129C28(void *arg0, void *arg1);
extern u8 *D_00387E9C;

s32 func_001D6FF0(u8 *arg0, u8 *arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, u8 arg6,
                  f32 farg0, f32 farg1, f32 farg2, f32 farg3, f32 farg4, f32 farg5,
                  f32 farg6, f32 farg7, f32 farg8, f32 farg9, f32 farg10, f32 farg11,
                  f32 farg12) {
    u8 blkA[16];
    u8 blkB[16];
    u8 *node;
    f32 invWidth;
    f32 invLen;
    f32 dz;
    s32 count;

    __builtin_memcpy(blkA, arg0, 16);
    __builtin_memcpy(blkB, arg1, 16);

    node = func_001D6F80();
    if (node == NULL) {
        return 0;
    }

    func_00129C28(node, blkA);
    func_00129C28(node + 0x10, blkB);

    *(f32 *)(node + 0x20) = farg0;
    invWidth = 0.0f;
    if (farg1 != 0.0f) {
        invWidth = 1.0f / farg1;
    }
    *(f32 *)(node + 0x24) = invWidth;

    *(f32 *)(node + 0x40) = farg5;
    *(f32 *)(node + 0x44) = farg6;
    invLen = 0.0f;
    if (farg7 != 0.0f) {
        invLen = 1.0f / farg7;
    }
    *(f32 *)(node + 0x48) = invLen;

    *(f32 *)(node + 0x4C) = farg8;
    *(f32 *)(node + 0x50) = farg9;
    *(f32 *)(node + 0x58) = farg11 * 30.0f;
    *(f32 *)(node + 0x54) = farg10;

    *(u8 *)(node + 0x60) = arg2;
    *(u8 *)(node + 0x61) = arg3;
    *(u8 *)(node + 0x62) = arg4;
    *(u8 *)(node + 0x65) = arg5;
    *(u8 *)(node + 0x66) = arg6;
    *(u8 *)(node + 0x67) = 1;

    *(f32 *)(node + 0x28) = farg2;
    dz = farg3 - farg2;
    *(f32 *)(node + 0x2C) = dz;
    if (farg4 != 0.0f) {
        *(f32 *)(node + 0x2C) = dz / (farg4 * 30.0f);
    }
    *(f32 *)(node + 0x30) = farg3;

    *(u8 *)(node + 0x63) = 0;
    *(u8 *)(node + 0x64) = 0;
    *(u8 *)(node + 0x68) = 0;
    *(f32 *)(node + 0x5C) = farg12;
    *(u8 *)(node + 0x64) = *(u8 *)(node + 0x64) | 4;

    count = *(s32 *)(D_00387E9C + 0x1440) + 1;
    *(s32 *)(D_00387E9C + 0x1440) = count;
    return count;
}
