#include "common.h"

void *memset(void *s, s32 c, u32 n);

void func_002E20C8(s32 arg0) {
    s32 temp_s0;

    temp_s0 = arg0 + 0x160;
    memset((void *) temp_s0, 0, 0x4D0);
    *(s32 *) (temp_s0 + 0xD4) = 1;
    *(s32 *) (temp_s0 + 0x7C) = 0xFF;
    *(s32 *) (temp_s0 + 0x4C0) = 0;
    *(s32 *) (temp_s0 + 0x4C) = 1;
    *(s32 *) (temp_s0 + 0x70) = 0;
    *(s32 *) (temp_s0 + 0x74) = 0xFF;
    *(s32 *) (temp_s0 + 0x78) = 0xFF;
    *(s32 *) (temp_s0 + 0x40C) = 0;
    *(s32 *) (temp_s0 + 0x410) = 0;
    *(s32 *) (temp_s0 + 0x414) = 0;
    *(s32 *) (temp_s0 + 0x418) = 0;
    *(s32 *) (temp_s0 + 0x41C) = 0;
    *(s32 *) (temp_s0 + 0x420) = 0;
    *(s32 *) (temp_s0 + 0x428) = 0;
    *(s32 *) (temp_s0 + 0x3C8) = 0;
    *(s32 *) (temp_s0 + 0x49C) = 0;
    *(s32 *) (temp_s0 + 0x4A0) = 0;
    *(s32 *) (temp_s0 + 0x4B0) = 0;
    *(s32 *) (temp_s0 + 0xD0) = 0;
}
