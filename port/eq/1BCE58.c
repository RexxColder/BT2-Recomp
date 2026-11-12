#include "common.h"

extern void func_00129C28(u8 *dst, u8 *src);

void func_001BCE58(u8 *obj) {
    u8 *child;

    child = *(u8 **)(obj + 0xE8);
    while (child != 0) {
        *(u32 *)child |= 1;
        *(u8 *)(child + 5) = *(u8 *)(obj + 5);
        func_00129C28(child + 0x40, obj + 0x40);
        func_00129C28(child + 0x60, obj + 0x60);
        child = *(u8 **)(child + 0xF0);
    }
}
