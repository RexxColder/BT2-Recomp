#include "common.h"

extern s32 D_003877B8;
extern s32 func_00129C38();

/* 0x0018E1A8: copies the 16-byte vector at pos to the stack; if the global flag is set and obj->+0x38 has bit 2 of +0x56, calls func_00129C38(sub + 0x10, copy). */
void func_0018E1A8(u8 *obj, u8 *pos) {
    u8 sp[16];
    u8 *sub;

    *(u64 *)(sp + 8) = *(u64 *)(pos + 8);
    *(u64 *)sp = *(u64 *)pos;
    if (D_003877B8 == 0) {
        return;
    }
    if (obj == 0) {
        return;
    }
    sub = *(u8 **)(obj + 0x38);
    if (sub == 0) {
        return;
    }
    if ((*(u16 *)(sub + 0x56) & 2) != 0) {
        func_00129C38(sub + 0x10, sp);
    }
}
