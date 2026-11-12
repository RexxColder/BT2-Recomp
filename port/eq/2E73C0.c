#include "common.h"

/* 0x002E73C0: adds the third argument to the two words at +0x88 and +0x8C of the object. */
void func_002E73C0(u8 *arg0, s32 arg1, s32 arg2) {
    *(s32 *)(arg0 + 0x8C) = *(s32 *)(arg0 + 0x8C) + arg2;
    *(s32 *)(arg0 + 0x88) = *(s32 *)(arg0 + 0x88) + arg2;
}
