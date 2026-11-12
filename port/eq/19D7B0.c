#include "common.h"

void func_00129C28(s32 arg0, s32 arg1, s32 arg2);  /* GUESS: asm passes 3 args */
extern s32 func_0019C868 __attribute__((section(".data")));

void func_0019D7B0(s32 arg0, s32 arg1) {
    s64 sp[2];

    sp[1] = *(s64 *)(arg1 + 8);
    sp[0] = *(s64 *)(arg1 + 0);
    if ((arg0 != 0) && (*(s32 *)(*(s32 *)(arg0 + 0x28)) == (s32)0x0019C868u)) {
        func_00129C28(*(s32 *)(arg0 + 0x38) + 0xBD0, (s32)sp, arg0);
    }
}
