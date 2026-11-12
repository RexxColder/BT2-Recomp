#include "m2c_macros.h"

void func_26E9E8(void *);
extern void *D_0042A57C __attribute__((section(".data")));

void func_003F90B0(void) {
    s32 i;
    s32 off;
    s32 a1;

    i = 1;
    off = 0;
    do {
        i -= 1;
        func_26E9E8((u8 *)D_0042A57C + off + 0x18);
        off += 0x28;
    } while (i >= 0);
    if (M2C_FIELD(D_0042A57C, s32 *, 0xB4) & 0x10) {
        a1 = M2C_FIELD(D_0042A57C, s32 *, 0xBC);
        if (a1 < M2C_FIELD(D_0042A57C, s32 *, 0xC0)) {
            M2C_FIELD(D_0042A57C, s32 *, 0xBC) = a1 + 3;
            if (!(M2C_FIELD(D_0042A57C, s32 *, 0xBC) < M2C_FIELD(D_0042A57C, s32 *, 0xC0))) {
                M2C_FIELD(D_0042A57C, s32 *, 0xBC) = a1;
                M2C_FIELD(D_0042A57C, s32 *, 0xB4) ^= 0x10;
            }
        }
    }
}
