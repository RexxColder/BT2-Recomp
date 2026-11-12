#include "common.h"

extern s32 PauseMenu_Term();
extern void BtlSeq_Term();
extern void func_002FCE78(s32 arg0);
extern u8 D_003553F0[];

void func_002FD258(void) {
    u8 *entry;
    s32 i;

    PauseMenu_Term();
    entry = D_003553F0;
    for (i = 15; i >= 0; i--) {
        if (*(s8 *)entry == 1) {
            func_002FCE78((s32)entry);
        }
        entry += 0x44;
    }
    BtlSeq_Term();
}
