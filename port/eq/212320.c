#include "common.h"

s32 BtlObjXf_Update(s32 arg0);
s32 func_001FA3A8(s32 arg0);
s32 func_00217488(s32 arg0);

/* 0x00212320: BtlObjXf_Update(arg0), func_001FA3A8(its result), v = func_00217488(arg0). v in 0xDE..0xE2 -> v - 0xDE
 * (jump table). Else the first set bit of 0x04000000 / 0x08000000 / 0x10000000 / 0x20000000 OF func_001FA3A8'S RESULT
 * (the animation's flags, $s1 in the asm; testing v instead returned -1 for every technique, and 231300 then counted
 * the use into gauge +0x2C, the flag that blocks every later technique: B3) gives 2 / 3 / 4 / 0, and 0x40000000
 * gives 1 when set, -1 when not. */
s32 func_00212320(s32 arg0) {
    s32 v;
    s32 f;

    f = func_001FA3A8(BtlObjXf_Update(arg0));
    v = func_00217488(arg0);
    if ((u32)(v - 0xDE) < 5) {
        switch (v - 0xDE) {
        case 0:
            return 0;
        case 1:
            return 1;
        case 2:
            return 2;
        case 3:
            return 3;
        case 4:
            return 4;
        }
    }
    if (f & 0x04000000) {
        return 2;
    }
    if (f & 0x08000000) {
        return 3;
    }
    if (f & 0x10000000) {
        return 4;
    }
    if (f & 0x20000000) {
        return 0;
    }
    return (f & 0x40000000) ? 1 : -1;
}
