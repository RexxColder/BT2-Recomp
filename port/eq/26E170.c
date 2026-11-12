#include "common.h"

void func_0026C7A8(s32 arg0, s32 arg1, s32 arg2);

void func_0026E170(s32 arg0, s32 arg1) {
    s32 count;
    s32 off;

    if (*(u16 *)(arg0 + 0x12) != 0) {
        count = 0;
        off = 0;
        do {
            count++;
            func_0026C7A8(*(s32 *)(arg0 + 0x14) + off, arg1, *(s32 *)arg0);
            off += 0xC;
        } while (count < *(u16 *)(arg0 + 0x12));
    }
}
