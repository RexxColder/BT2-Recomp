#include "common.h"

/* 0x001A22D0: frees the node list of the ribbon at arg0 (head at +0, tail at +4): every node's flags word (+0) is set
 * to 0, the chain is followed through the pointer at +0x120; head and tail are then cleared. Same code as
 * EftRibbon_FreeNodes (next at +0x40 in the other copy, 0x1C4EC8). */
void func_001A22D0(u8 *arg0) {
    u8 *n = *(u8 **)(arg0 + 0);
    u8 *next;

    if (n != NULL) {
        do {
            next = *(u8 **)(n + 0x120);
            *(s32 *)(n + 0) = 0;
            n = next;
        } while (next != NULL);
    }
    *(u8 **)(arg0 + 4) = NULL;
    *(u8 **)(arg0 + 0) = NULL;
}
