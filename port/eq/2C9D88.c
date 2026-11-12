#include "common.h"

extern u8 D_00399C68[] __attribute__((section(".data")));
extern u8 D_00399C90[] __attribute__((section(".data")));
extern u8 D_00399C98[] __attribute__((section(".data")));

s32 func_002C9F80(s32 arg0);
s32 func_002C2FF0(s32 arg0, s32 arg1);
void func_002CA048(s32 arg0, s32 arg1, s32 arg2);
void func_002CA0F8(s32 arg0);
void func_002C7688(s32 arg0);
void func_002CA118(s32 arg0);

s32 func_002C9D88(s32 arg0, s32 arg1) {
    u8 *dst;
    u8 *slot;
    s32 addr;
    s32 i;

    if (func_002C9F80(arg0) != 0) {
        return func_002C2FF0(0, 0xFF000F15);
    }

    dst = (u8 *)arg1;
    __builtin_memcpy(dst + 0x04, D_00399C68, 0x24);
    __builtin_memcpy(dst + 0x28, D_00399C90, 8);
    __builtin_memcpy(dst + 0x30, D_00399C98, 0x40);

    *(s32 *)(dst + 0x74) = 5;
    *(s32 *)(dst + 0x78) = 0xC0;
    *(s32 *)(dst + 0x13C) = 1;
    *(s32 *)(dst + 0x00) = 0;
    *(s32 *)(dst + 0x70) = 0;
    *(s32 *)(dst + 0x138) = 0;
    *(s32 *)(dst + 0x7C) = 0;
    *(s32 *)(dst + 0x80) = 0;
    *(s32 *)(dst + 0x160) = 0;
    *(s32 *)(dst + 0x164) = 0;
    *(s32 *)(dst + 0x168) = 0;
    *(s32 *)(dst + 0x16C) = 0;
    *(s32 *)(dst + 0x170) = 0;
    *(s32 *)(dst + 0x174) = 0;

    func_002CA048((s32)(dst + 0x180), (s32)(dst + 0x30), 16);

    *(s32 *)(dst + 0x84) = 0;
    *(s32 *)(dst + 0x88) = 0;

    func_002CA0F8((s32)(dst + 0x8C));

    *(s32 *)(dst + 0x10C) = -1;
    *(s32 *)(dst + 0x110) = 0;
    *(s32 *)(dst + 0x114) = 0x7FFFFFFF;

    func_002C7688((s32)(dst + 0x118));
    func_002CA118((s32)(dst + 0x1080));

    /* table of 16 pointers walking down from dst+0x1114, step 8 bytes; stored every 0xF0 bytes from dst+0xFE4 */
    addr = arg1 + 0x1114;
    slot = dst + 0xFE4;
    for (i = 15; i >= 0; i--) {
        *(s32 *)slot = addr;
        slot -= 0xF0;
        addr -= 8;
    }

    return 0;
}
