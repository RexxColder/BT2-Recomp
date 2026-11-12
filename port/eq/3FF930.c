#include "m2c_macros.h"

void func_26EB78(void *, void *, void *);
void func_003FF340(void);
extern void *D_0042A590 __attribute__((section(".data")));
extern s32 D_0042B940 __attribute__((section(".data")));

void func_003FF930(void) {
    M2C_FIELD(D_0042A590, s32 *, 0x240) = M2C_FIELD(D_0042A590, s32 *, 0x240) - 1;
    M2C_FIELD(D_0042A590, s32 *, 0x244) = M2C_FIELD(D_0042A590, s32 *, 0x240) + 3;
    M2C_FIELD(D_0042A590, s32 *, 0x248) = M2C_FIELD(D_0042A590, s32 *, 0x240) + 4;
    func_26EB78((u8 *)D_0042A590 + 0x54, &D_0042B940, &D_0042A590);
    func_003FF340();
}
