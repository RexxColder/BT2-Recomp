#include "common.h"

/* 0x00269A08 BtlObj_FindBound: walks the chain of bone records from arg0 + 0x48 (each record: a word at +0 with the
 * offset to the next one, halfword id at +0xA, halfword flag at +6). Returns the first record whose id is arg1; a
 * record with a non-zero flag ends the walk with NULL. */
u8 *BtlObj_FindBound(u8 *arg0, s32 arg1) {
    u8 *p = *(u8 **)(arg0 + 0x48);

    for (;;) {
        if (*(u16 *)(p + 0xA) == arg1) {
            return p;
        }
        if (*(u16 *)(p + 6) != 0) {
            return NULL;
        }
        p = p + *(s32 *)(p + 0);
    }
}
