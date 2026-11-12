#include "common.h"

void Res_RelocateOffsets(s32 arg0, s32 arg1, s32 arg2);
s32 func_002A3C08(s32 arg0);
s32 func_002A3C68();
s32 func_002A3CC0();
s32 func_002A3D18();
void func_001F4278(s32 arg0);
s32 func_0028BAA8(s32 arg0);
void func_00256360(s32 arg0, s32 arg1);
extern u8 D_003B0F40[] __attribute__((section(".data")));

void func_002A3328(void) {
    s32 sp[4];
    s32 s0;
    s32 r;

    for (s0 = 0; s0 < 8; s0++) {
        if (*(s32 *)(D_003B0F40 + 4 + (s0 * 4)) != 0) {
            r = func_002A3C08(s0);
            sp[0] = r;
            Res_RelocateOffsets((s32)sp, r, r);
        }
    }
    if (*(s32 *)(D_003B0F40 + 0x24) != 0) {
        r = func_002A3C68();
        sp[0] = r;
        Res_RelocateOffsets((s32)sp, r, r);
    }
    if (*(s32 *)(D_003B0F40 + 0x28) != 0) {
        r = func_002A3CC0();
        sp[0] = r;
        Res_RelocateOffsets((s32)sp, r, r);
    }
    if (*(s32 *)(D_003B0F40 + 0x2C) != 0) {
        func_001F4278(func_002A3D18());
    }
    if (*(s32 *)(D_003B0F40 + 0x30) != 0) {
        r = func_0028BAA8(0x62800);
        *(s32 *)(D_003B0F40 + 0x34) = r;
        func_00256360(*(s32 *)(D_003B0F40 + 0x30), r);
    }
}
