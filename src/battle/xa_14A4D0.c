#include "common.h"

/* Per-block cleanup of the original (func_0014E970, 0x14E970). */
extern void func_0014E970(void *blk);

/* Runs the block's cleanup (func_0014E970) and clears the word at +0x204 of the sub-block pointed to by +0x1E84. */
void BtlSlot_ResetSubWord(void *obj) {
    void *blk;

    blk = *(void **)((u8 *)obj + 0x38);
    func_0014E970(blk);
    *(s32 *)(*(u8 **)((u8 *)blk + 0x1E84) + 0x204) = 0;
}
