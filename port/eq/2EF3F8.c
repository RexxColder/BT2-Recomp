#include "common.h"

/* GUESS arity: func_002EE8E0 gets 4 args in the asm; ctx.h says 1 */
void func_002EE8E0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_002EF3F8(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 buf[8];
    s32 *p;

    if (arg0 != NULL) {
        buf[0] = *(s32 *)(arg0 + 0x0);
        buf[1] = *(s32 *)(arg0 + 0x4);
        buf[2] = *(s32 *)(arg0 + 0x8);
        buf[3] = *(s32 *)(arg0 + 0x8) + 1;
        buf[4] = *(s32 *)(arg0 + 0xC);
        buf[5] = 0x19;
        p = buf;
        func_002EE8E0((s32)p, *(s32 *)(arg0 + 0x8) + 1, *(s32 *)(arg0 + 0x8), 0x19);
    } else {
        func_002EE8E0(0, arg1, arg2, arg3);
    }
}
