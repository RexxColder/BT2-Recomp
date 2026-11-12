#include "common.h"

void *memset(void *s, s32 c, u32 n);
s32 sceVu0UnitMatrix(s32 arg0, s32 arg1);

void func_001EC288(s32 arg0, s32 arg1) {
    s32 temp_s1;

    memset((void *)arg0, 0, 0x80);
    *(s32 *)(arg0 + 0x70) = arg1;
    *(s32 *)(arg0 + 0x74) = arg1 + 0x10;
    *(s32 *)(arg0 + 0x78) = arg1 + *(s32 *)(arg1 + 0x8);
    *(u8 *)(arg0 + 0x43) = (u8)-0x80;
    temp_s1 = arg1 + *(s32 *)(arg1 + 0xC);
    *(f32 *)(arg0 + 0x60) = 1.0f;
    *(s32 *)(arg0 + 0x7C) = temp_s1;
    *(u8 *)(arg0 + 0x40) = (u8)-0x80;
    *(u8 *)(arg0 + 0x41) = (u8)-0x80;
    *(u8 *)(arg0 + 0x42) = (u8)-0x80;
    sceVu0UnitMatrix(arg0, -0x80);
}
