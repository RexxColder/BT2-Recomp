#include "common.h"

extern void func_001E1258(u8 *a0, s32 a1, s32 a2, f32 f);

void func_001DFCA0(u8 *obj, s32 arg1, u32 arg2) {
    s32 i;
    u8 *entry;

    if (*(u8 *)(obj + 0x21DA) == 0) {
        return;
    }
    if (*(u8 *)(obj + 0x21CC) == 0) {
        return;
    }
    entry = obj;
    i = 0;
    do {
        func_001E1258(entry, arg1, arg2 & 0xFF, *(f32 *)(obj + 0x21D0));
        i++;
        entry += 0x1B0;
    } while (i < *(u8 *)(obj + 0x21CC));
}
