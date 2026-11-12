#include "m2c_macros.h"

s32 func_277E70(void *, s32, s32);
void func_26EBC0(void *, void *, void *);
void func_24A598(void *, void *, s32, s32, s32, s32, s32);
void func_26EA58(void *);
extern void *D_0042FD70 __attribute__((section(".data")));
extern s32 D_0042FDF0 __attribute__((section(".data")));

void func_0041C4A0(void) {
    s32 buf[4];

    func_277E70(M2C_FIELD(D_0042FD70, void **, 0x34), 0, 0x80);
    func_26EBC0((u8 *)D_0042FD70 + 0xC, &D_0042FDF0, buf);
    func_24A598((u8 *)D_0042FD70 + 0xC, buf, 0, 0, M2C_FIELD(D_0042FD70, s32 *, 8),
                M2C_FIELD(D_0042FD70, s32 *, 0x7C) + 0x165, 1);
    func_26EA58((u8 *)D_0042FD70 + 0xC);
}
