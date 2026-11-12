#include "m2c_macros.h"

s32 BtlScene_IsCharStopped(s32);
void func_00129C38(void *, void *);

// Per-frame update of a character state: flags word at +0 of the object at arg0+0x38; bit 0x10 follows arg0 bit 0x1, bit 1 follows arg0 bit 0x4.
void func_00149660(void *arg0) {
    s32 *flags;

    flags = (s32 *) ((s32 **) arg0)[0xE];
    if (BtlScene_IsCharStopped(*(s32 *) (*(s32 **)((u8 *) flags + 0x90))) == 0) {
        *flags = *flags & ~0x10;
        if (*(u16 *)((u8 *) arg0 + 8) & 1) {
            func_00129C38((u8 *) flags + 0x60, (u8 *) arg0 + 0x10);
            *flags = *flags | 0x10;
        }
        if (*(u16 *)((u8 *) arg0 + 8) & 4) {
            *flags = *flags | 1;
        }
    }
}
