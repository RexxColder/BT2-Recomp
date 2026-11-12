#include "common.h"

/* Battle work block (D_003876A0; the sub-block at +0x70 is used here). */
extern void *D_003876A0;
/* One-time flag: set after the setup below has run once. */
extern u8 D_003876A9;

/* Callees of the original (func_ labels of the asm snapshot). */
extern void func_00100E78(void);
extern s32 func_00100ED0(s32 id, s32 cur, s32 flag);
extern s32 func_00100FC8(s32 flag);

/* Runs the one-time setup of the battle work sub-block at +0x70 (three values with ids 0x3C29, 0x3C2A, 0x3C2C,
 * then waits for func_00100FC8 to report done), then sets D_003876A9. Does nothing once the flag is 1. */
void BtlWork_InitOnce(void) {
    u8 *sub;

    sub = (u8 *)D_003876A0 + 0x70;
    if (D_003876A9 != 1) {
        func_00100E78();
        *(s32 *)(sub + 8) = func_00100ED0(0x3C29, *(s32 *)(sub + 8), 1);
        *(s32 *)(sub + 0xC) = func_00100ED0(0x3C2A, *(s32 *)(sub + 0xC), 0);
        *(s32 *)(sub + 4) = func_00100ED0(0x3C2C, *(s32 *)(sub + 4), 0);
        func_00100FC8(1);
        do {
        } while (func_00100FC8(0) == 0);
        func_00100E78();
        D_003876A9 = 1;
    }
}
