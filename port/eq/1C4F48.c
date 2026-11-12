#include "common.h"

extern u8 *func_001C4E08(u8 *a0);
extern void func_00129C28(u8 *dst, u8 *src);

s32 func_001C4F48(u8 *owner, u8 *fallback) {
    u8 *ent;
    u8 *parent;

    ent = func_001C4E08(owner);
    if (ent == 0) {
        return 0;
    }
    *(u32 *)ent |= 1;
    parent = *(u8 **)(owner + 4);
    if (parent != 0) {
        func_00129C28(ent + 0x10, parent + 0x10);
    } else {
        func_00129C28(ent + 0x10, fallback + 0x10);
    }
    *(u8 *)(ent + 5) = 1;
    return 1;
}
