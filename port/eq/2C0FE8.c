#include "common.h"

u8 *func_00303D48(s32 *arg0, s32 arg1);
u8 *func_00304760(s32 *arg0, s32 arg1, s32 arg2);
extern s32 D_00393E70 __attribute__((section(".data")));
extern s32 D_00393E74 __attribute__((section(".data")));

void func_002C0FE8(void) {
    s32 sp[4];
    u8 *o;

    o = func_00304760(sp, 8, 0);
    D_00393E70 = ((s32 (*)(u8 *))(*(s32 *)(*(u8 **)o + 0x10)))(o);
    ((void (*)(u8 *))(*(s32 *)(*(u8 **)o + 0xC)))(o);
    o = func_00303D48(sp, 8);
    D_00393E74 = ((s32 (*)(u8 *))(*(s32 *)(*(u8 **)o + 0x10)))(o);
    ((void (*)(u8 *))(*(s32 *)(*(u8 **)o + 0xC)))(o);
}
