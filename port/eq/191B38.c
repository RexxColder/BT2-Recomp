#include "common.h"

extern u8 *gEftDisc;

void func_00191B38(u8 *arg0, u8 *arg1) {
    u8 *prev = *(u8 **)(arg1 + 0x144);
    u8 *next = *(u8 **)(arg1 + 0x140);

    if (prev != NULL) {
        *(u8 **)(prev + 0x140) = next;
    } else {
        *(u8 **)(arg0 + 0) = next;
    }
    next = *(u8 **)(arg1 + 0x140);
    prev = *(u8 **)(arg1 + 0x144);
    if (next != NULL) {
        *(u8 **)(next + 0x144) = prev;
    } else {
        *(u8 **)(arg0 + 4) = prev;
    }
    *(s32 *)(gEftDisc + 8) = *(s32 *)(gEftDisc + 8) - 1;
}
