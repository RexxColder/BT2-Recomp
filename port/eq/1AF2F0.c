#include "common.h"

void *func_001AF290(void);
void func_003126C8(void *arg0, f32 *arg1);
extern u8 *D_00387858;
extern f32 D_00384F38;
extern f32 D_00384F3C;

s32 func_001AF2F0(u8 **arg0, u8 **arg1, s32 arg2, f32 *arg3, f32 *arg4, s32 arg5,
                  u8 arg6, u8 arg7, u8 arg8, u8 arg9, u8 arg10,
                  f32 farg0, f32 farg1, f32 farg2, f32 farg3, f32 farg4, f32 farg5) {
    u8 *node;
    f32 zeroF;
    f32 invWidth;
    f32 scaleX;
    f32 scaleY;
    f32 dz;
    s32 count;

    node = func_001AF290();
    if (node == NULL) {
        return 0;
    }

    if (*arg0 != NULL) {
        *(s32 *)(node + 0x60) = 0;
        *(u8 **)(node + 0x5C) = *arg1;
    } else {
        *arg0 = node;
        *(s32 *)(node + 0x5C) = 0;
        *(s32 *)(node + 0x60) = 0;
    }
    if (*arg1 != NULL) {
        *(u8 **)(*arg1 + 0x60) = node;
    }
    *arg1 = node;

    func_003126C8(node, arg3);
    func_003126C8(node + 0x10, arg4);
    *(s32 *)(node + 0x20) = arg2;
    *(f32 *)(node + 0x24) = farg0;

    invWidth = 0.0f;
    if (farg1 != 0.0f) {
        invWidth = 1.0f / farg1;
    }
    *(f32 *)(node + 0x28) = invWidth;

    scaleX = farg4 * D_00384F38;
    *(s32 *)(node + 0x38) = 0;
    *(s32 *)(node + 0x4C) = arg5;
    *(u8 *)(node + 0x50) = arg6;
    *(u8 *)(node + 0x51) = arg7;
    *(f32 *)(node + 0x44) = scaleX;
    scaleY = farg4 * D_00384F3C;
    zeroF = *(f32 *)(node + 0x38);
    *(u8 *)(node + 0x52) = arg8;
    *(f32 *)(node + 0x48) = farg5 * 30.0f;
    *(u8 *)(node + 0x55) = arg9;
    *(u8 *)(node + 0x56) = arg10;
    *(u8 *)(node + 0x57) = 1;
    dz = farg3 - zeroF;
    *(f32 *)(node + 0x2C) = farg2;
    *(u8 *)(node + 0x53) = 0;
    *(u8 *)(node + 0x54) = 0;
    *(u8 *)(node + 0x58) = 0;
    *(f32 *)(node + 0x3C) = dz;
    if (scaleY != zeroF) {
        *(f32 *)(node + 0x3C) = dz / (scaleY * 30.0f);
    }
    *(f32 *)(node + 0x40) = farg3;
    *(u8 *)(node + 0x54) = *(u8 *)(node + 0x54) | 1;

    count = *(s32 *)(D_00387858 + 4) + 1;
    *(s32 *)(D_00387858 + 4) = count;
    return count;
}
