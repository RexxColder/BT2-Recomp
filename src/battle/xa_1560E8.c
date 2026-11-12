#include "common.h"

/* Pool free of a block (the original's func_0014E968 is called first, on the same block). */
extern void func_0014E968(void *blk);
extern void BtlPool_Free(s32 slot, void *ptr);
extern s32 BtlPool_GetCurrent(void);

#define W32(p, off) (*(s32 *)((u8 *)(p) + (off)))

/* Runs the block's cleanup (func_0014E968), then frees the two blocks whose pointers are at +0x1E84 and +0x1E80
 * of the block (each pointer is cleared after it is freed). The block itself is the pointer at +0x38 of obj. */
void BtlSlot_FreeBlocks(void *obj) {
    void *blk;

    blk = *(void **)((u8 *)obj + 0x38);
    func_0014E968(blk);
    if (W32(blk, 0x1E84) != 0) {
        BtlPool_Free(BtlPool_GetCurrent(), (void *)W32(blk, 0x1E84));
        W32(blk, 0x1E84) = 0;
    }
    if (W32(blk, 0x1E80) != 0) {
        BtlPool_Free(BtlPool_GetCurrent(), (void *)W32(blk, 0x1E80));
        W32(blk, 0x1E80) = 0;
    }
}
