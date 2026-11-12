#include "m2c_macros.h"

void func_249548(s32);
void func_26E908(void *);
void func_28BB60(void *);
extern void *D_0042A57C __attribute__((section(".data")));

void func_003F8930(s32 arg0) {
    s32 i;
    s32 off;

    func_249548(arg0);
    i = 1;
    off = 0;
    do {
        i -= 1;
        func_26E908((u8 *)D_0042A57C + off + 0x18);
        off += 0x28;
    } while (i >= 0);
    func_28BB60(M2C_FIELD(D_0042A57C, void **, 8));
    func_28BB60(M2C_FIELD(D_0042A57C, void **, 4));
    func_28BB60(D_0042A57C);
}
