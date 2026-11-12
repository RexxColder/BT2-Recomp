#include "common.h"

void *memcpy(void *arg0, const void *arg1, u32 arg2);
void *memset(void *arg0, s32 arg1, u32 arg2);
extern u8 D_00399C68 __attribute__((section(".data")));
extern u8 D_00399C90 __attribute__((section(".data")));
extern u8 D_00399C98 __attribute__((section(".data")));

void func_002C54D8(void *arg0) {
    memcpy(&D_00399C68, arg0, 0x24);
    *(s32 *)(&D_00399C68 + 0x10) = (*(s32 *)(&D_00399C68 + 0x10) + 0x3F) & -0x40;
    *(s32 *)(&D_00399C68 + 0x20) = (*(s32 *)(&D_00399C68 + 0x20) + 0x3F) & -0x40;
    memset(&D_00399C90, 0, 8);
    memset(&D_00399C98, 0, 0x40);
}
