#include "common.h"

/* ctx.h lists 16 parameters; the call site passes only the pointer, so declare the real one-argument form. */
s32 func_002EA050(s32 arg0);
extern s32 D_00366ED8 __attribute__((section(".data")));
extern s32 D_0037C180 __attribute__((section(".data")));
extern s32 D_0037C1A8 __attribute__((section(".data")));

// Validates index arg0 (below 0x100, with a non-null table entry) and arg1 (not negative, below the entry's word at +8).
// Returns 0 when valid; otherwise reports through func_002EA050 with one of two blocks and returns -3.
s32 func_002EC9F8(u32 arg0, s32 arg1) {
    s32 *entry;
    if (arg0 >= 0x100U) {
        func_002EA050((s32)&D_0037C180);
        return -3;
    }
    entry = (s32 *)(*(s32 *)((u8 *)&D_00366ED8 + (arg0 * 4)));
    if (entry == NULL) {
        func_002EA050((s32)&D_0037C180);
        return -3;
    }
    if ((arg1 < 0) || !(arg1 < entry[2])) {
        func_002EA050((s32)&D_0037C1A8);
        return -3;
    }
    return 0;
}
