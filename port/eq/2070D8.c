#include "common.h"

extern u8 *D_00387A40;
extern void func_003126C8();

/* Copies two 16-byte vectors into entry obj[0x142C] (0x1520 bytes each) of the table at D_00387A40. */
void func_002070D8(u8 *obj, s32 arg1, s32 arg2) {
    s32 idx = *(s32 *)(obj + 0x142C);
    u8 *entry;

    if (idx >= 0 && idx < *(s32 *)(D_00387A40 + 0xC)) {
        entry = *(u8 **)(D_00387A40 + 8) + idx * 0x1520;
        func_003126C8(entry + 0x9A0, arg1);
        func_003126C8(entry + 0x9B0, arg2);
    }
}
