#include "common.h"

/* 0x002A3AF8: func_003126C8(&D_003B1C80[a0 * 16], a1); tail func_003126C8(&D_003B1C80[0x80 + a0 * 16], a2). */
extern u8 D_003B1C80[] __attribute__((section(".data")));
s32 func_003126C8(s32 arg0, s32 arg1);

s32 func_002A3AF8(s32 a0, s32 a1, s32 a2) {
    s32 off;

    off = a0 << 4;
    func_003126C8((s32)(D_003B1C80 + off), a1);
    return func_003126C8((s32)(D_003B1C80 + 0x80 + off), a2);
}
