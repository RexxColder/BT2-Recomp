#include "common.h"

extern void func_00113BE0(s32 arg0, s32 arg1);

void func_00113C50(u8 *list, u8 flag) {
    if (*(u32 *)list & 2) {
        return;
    }
    do {
        func_00113BE0((s32)list, flag);
        list += 0x60;
    } while (!(*(u32 *)list & 2));
}
