#include "common.h"

void func_00129C28(void *dst, void *src);

/* Walks the linked list at node[0] (next at +0x40); each node's 16-byte vector at +0x10 is swapped
 * through a running vector (seeded from node+0x90) and the byte at +4 is cleared. */
void EftRibbon_PlaceTrail1(s32 arg0, u8 *node) {
    u8 sp[0x20];
    u8 *it;

    func_00129C28(sp, node + 0x90);
    it = *(u8 **)node;
    if (it != 0) {
        do {
            func_00129C28(sp + 0x10, it + 0x10);
            func_00129C28(it + 0x10, sp);
            func_00129C28(sp, sp + 0x10);
            *(u8 *)(it + 4) = 0;
            it = *(u8 **)(it + 0x40);
        } while (it != 0);
    }
}
