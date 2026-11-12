#include "common.h"

/* Battle scene pack: BtlScene_GetPackEntry(pack, idx) returns entry idx (sys function at 0x126488 in BT2). */
extern s32 BtlScene_GetPackEntry(s32 pack, s32 idx);

/* Fills count words of out with the pack entries first, first+1, ... of the scene's pack (scene + 0x1C). */
void BtlScene_FillPackEntries(void *scene, s32 *out, s32 count, s32 first) {
    s32 *dst;
    s32 n;
    s32 idx;

    idx = first;
    if (count > 0) {
        dst = out;
        n = count;
        do {
            s32 pack = *(s32 *)((u8 *)scene + 0x1C);
            n -= 1;
            *dst = BtlScene_GetPackEntry(pack, idx);
            idx += 1;
            dst += 1;
        } while (n != 0);
    }
}
