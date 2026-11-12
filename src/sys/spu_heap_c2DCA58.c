#include "common.h"
#include "sys/align.h"
#include "sys/spu_heap.h"

/*
 * Sound-RAM (SPU2) address allocator, 0x11ECB8..0x11F190.
 *
 * A table of 17 range descriptors {state, addr, size} covers SPU addresses 0x5010..0x1F5FE0. Each descriptor is
 * unused, a free range or a used range; the ranges always tile the whole region. The table is not sorted: the
 * neighbour of a range is found by searching for the descriptor that starts (or ends) at a given address.
 *
 * Alloc: the size is rounded up to 16, then the ranges are walked in ADDRESS order from the base and the first free
 * one that is large enough is taken (first fit, lowest address). The used range is carved from its start; the
 * remainder stays free in the same descriptor (which is released when the fit is exact).
 * Free: the range becomes free and is merged with a free neighbour on either side.
 *
 * There is no failure path: Alloc with no fitting range, Alloc with no unused descriptor (17 in total) and Free of
 * an address that is not the start of a range all dereference NULL.
 */

extern void *memset(void *dst, s32 c, u32 n);

extern SpuBlock gSpuHeapBlocks[SPU_HEAP_BLOCKS];

/* Marks a descriptor unused. */
void func_002DCA58(SpuBlock *block) {
    block->state = SPU_BLOCK_NONE;
    block->addr = 0;
    block->size = 0;
}

/* Makes a descriptor a free range, or unused when nothing is left. */
void SpuBlock_SetFree(SpuBlock *block, s32 addr, s32 size);

/* Makes a descriptor a used range. */
void SpuBlock_SetUsed(SpuBlock *block, s32 addr, s32 size);

/* Finds the descriptor that starts at `addr` (byEnd 0) or ends at it (byEnd 1); NULL when there is none. */
SpuBlock *SpuHeap_FindBlock(s32 addr, s32 byEnd);

/* Empties the table and makes the whole region one free range. */
void SpuHeap_Init(void);

/* Reserves `size` bytes (rounded up to 16) in the lowest free range that fits; returns the SPU address. */
s32 SpuHeap_Alloc(s32 size);

/* Releases the range that starts at `addr`, merging it with free neighbours. */
void SpuHeap_Free(s32 addr);

/* Total bytes in used ranges. */
s32 SpuHeap_GetUsedSize(void);

/* Total bytes in free ranges. */
s32 SpuHeap_GetFreeSize(void);

/* Size of the largest free range. */
s32 SpuHeap_GetMaxFree(void);

/* Walks the ranges in address order from the base and does nothing with them (a debug dump compiled out). */
void SpuHeap_Walk(void);
