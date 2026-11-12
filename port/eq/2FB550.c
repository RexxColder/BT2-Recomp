#include "common.h"

void func_00306F28(void);
void func_002FB520(void);
void func_00306FA0(void);
extern u8 D_00355338[] __attribute__((section(".data")));
extern s32 D_00355398 __attribute__((section(".data")));

/* 0x002FB550 (GUESS arity: no arguments; the asm passes a0 on to func_00306F28 untouched): calls func_00306F28,
 * then, if D_00355338[0] is 0, func_002FB520 and claims the record (byte 0 = 1, returned, byte 3 = -1,
 * byte 2 = 0, D_00355398 += 1, word +4 = 0). Calls func_00306FA0 and returns the record or NULL. */
u8 *func_002FB550(void) {
    u8 *res = NULL;

    func_00306F28();
    if (*(s8 *)D_00355338 == 0) {
        func_002FB520();
        *(s8 *)(D_00355338 + 0) = 1;
        res = D_00355338;
        *(s8 *)(D_00355338 + 3) = -1;
        *(s8 *)(D_00355338 + 2) = 0;
        D_00355398 += 1;
        *(s32 *)(D_00355338 + 4) = 0;
    }
    func_00306FA0();
    return res;
}
