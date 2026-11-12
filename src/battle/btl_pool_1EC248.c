#include "common.h"
#include "battle/btl_pool.h"
#include "sys/heap.h"

extern void *memset(void *dst, s32 c, u32 n);

extern BtlPool *gBtlPool;
/* Written by BtlPool_Init and BtlPool_SetInitArg, never read. */
extern s32 gBtlPoolInitArg;

/* The arena block is reached through a pointer to the field, not as a plain member: after a store to it
 * the compiler reloads gBtlPool, which a direct `gBtlPool->arenaMem = x` does not reproduce. */
#define ARENA_MEM (*&gBtlPool->arenaMem)

s32 BtlPool_CalcArenaSize(void);
void BtlPool_CarveArenas(void);
u8 *BtlPool_InitSlot(BtlPoolSlot *slot, s32 size, u8 *mem);

/* Allocates the pool manager and the memory behind every arena slot. */
void BtlPool_Init(s32 arg);

/* Frees the arena memory and the pool manager. */
void BtlPool_Term(void);

/* Allocates size bytes (rounded up to 32) from a slot: bump allocation for an arena, the heap otherwise. */
void *BtlPool_Alloc(s32 slot, s32 size);

/* Frees a pointer from a slot; a no-op for arena slots, which are only released by BtlPool_Reset. */
void BtlPool_Free(s32 slot, void *ptr);

/* Rewinds an arena slot to empty. */
void BtlPool_Reset(s32 slot);

/* Selects the slot that BtlPool_GetCurrent reports. */
void BtlPool_SetCurrent(s32 slot);

/* Returns the slot selected by BtlPool_SetCurrent. */
s32 BtlPool_GetCurrent(void);

/* Stores the value BtlPool_Init also records (never read back). */
void BtlPool_SetInitArg(s32 arg);

/* Returns the total size of all enabled arena slots. */
s32 BtlPool_CalcArenaSize(void);

/* Hands each enabled arena slot its piece of arenaMem. Slots 5 and 8 test the bit of slots 4 and 7 (original bug). */
void BtlPool_CarveArenas(void);

/* Points a slot at its arena memory and returns the address just past it. */
u8 *BtlPool_InitSlot(BtlPoolSlot *slot, s32 size, u8 *mem) {
    slot->size = size;
    slot->base = mem;
    slot->cur = mem;
    return mem + size;
}

/* Rounds a size up to a multiple of 32. */
s32 BtlPool_AlignUp32(s32 size);
