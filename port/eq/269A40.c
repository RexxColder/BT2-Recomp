#include "common.h"

/* Node fields (PS2 addresses held in s32): key +0xD4, left +0xD8, right/next +0xDC.
 * base+0xDE8 holds the list head (+0) and the last found node (+4, the cache). */
#define FLD(a, off) (*(s32 *)((u8 *)(s32)(a) + (off)))

/* 0x00269A40: find the node with the given key. Keys >= 0x37 walk the list from the head; smaller keys
 * search the tree from the cached node and cache the node they find. */
s32 func_00269A40(s32 base, s32 key) {
    s32 root = base + 0xDE8;
    s32 node;
    s32 k;

    if (key >= 0x37) {
        node = FLD(root, 0);
        while (node != 0) {
            if (FLD(node, 0xD4) == key) {
                return node;
            }
            node = FLD(node, 0xDC);
        }
        return 0;
    }

    node = FLD(root, 4);
    k = FLD(node, 0xD4);
    if (key == k) {
        return node;
    }
    if ((u32)k < (u32)key) {
        node = FLD(node, 0xDC);
        while (node != 0) {
            if (FLD(node, 0xD4) == key) {
                FLD(root, 4) = node;
                return node;
            }
            node = FLD(node, 0xDC);
        }
        return 0;
    }
    node = FLD(node, 0xD8);
    while (node != 0) {
        if (FLD(node, 0xD4) == key) {
            FLD(root, 4) = node;
            return node;
        }
        node = FLD(node, 0xD8);
    }
    return 0;
}
