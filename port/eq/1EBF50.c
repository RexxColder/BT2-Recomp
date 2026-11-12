#include "common.h"

void func_0028BB60(s32 arg0);
extern u8 *D_0038790C;

/* 0x001EBF50 BtlPool_Free (BT3 exact): if the arena bit (1 << (slot + 1)) of the pool's mask at +0x68 is clear and
 * ptr is not null, free it (tail call to func_0028BB60). */
void BtlPool_Free(s32 slot, u8 *ptr) {
    s32 bit = (s32)1 << ((slot + 1) & 31);

    if ((*(s32 *)(D_0038790C + 0x68) & bit) != 0) {
        return;
    }
    if (ptr != NULL) {
        func_0028BB60((s32)ptr);
    }
}
