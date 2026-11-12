#include "common.h"

/* 0x001C4EC8 EftRibbon_FreeNodes: gives every node of the ribbon at arg0 back to the pool (head at +0, tail at +4;
 * flags word of each node at +0, next pointer at +0x40), then clears head and tail. */
void EftRibbon_FreeNodes(u8 *arg0) {
    u8 *n = *(u8 **)(arg0 + 0);
    u8 *next;

    if (n != NULL) {
        do {
            next = *(u8 **)(n + 0x40);
            *(s32 *)(n + 0) = 0;
            n = next;
        } while (next != NULL);
    }
    *(u8 **)(arg0 + 4) = NULL;
    *(u8 **)(arg0 + 0) = NULL;
}
