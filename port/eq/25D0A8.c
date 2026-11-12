#include "common.h"

extern u8 *D_00387A40;

void func_0025D0A8(u8 *arg0) {
    u8 *node;

    node = *(u8 **)(arg0 + 0xDE8);
    while (node != NULL) {
        *(u8 **)(arg0 + 0xDE8) = *(u8 **)(node + 0xDC);
        *(s32 *)(node + 0xD8) = 0;
        *(u8 **)(node + 0xDC) = *(u8 **)(D_00387A40 + 0x38010);
        *(u8 **)(D_00387A40 + 0x38010) = node;
        node = *(u8 **)(arg0 + 0xDE8);
    }
}
