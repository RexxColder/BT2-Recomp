#include "m2c_macros.h"

void func_26EB78(void *, void *, void *);
void func_003F5750(void);
extern void *D_0042A578 __attribute__((section(".data")));
extern s32 D_0042AF48 __attribute__((section(".data")));

void func_003F5E90(void) {
    M2C_FIELD(D_0042A578, s32 *, 0x19C) = M2C_FIELD(D_0042A578, s32 *, 0x19C) + 1;
    M2C_FIELD(D_0042A578, s32 *, 0x1A0) = M2C_FIELD(D_0042A578, s32 *, 0x1A0) + 1;
    M2C_FIELD(D_0042A578, s32 *, 0x1A4) = M2C_FIELD(D_0042A578, s32 *, 0x1A0) - 1;
    M2C_FIELD(D_0042A578, s32 *, 0x1A8) = M2C_FIELD(D_0042A578, s32 *, 0x1A0) + 3;
    func_26EB78((u8 *)D_0042A578 + 0x38, &D_0042AF48, D_0042A578);
    func_003F5750();
}
