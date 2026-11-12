#include "common.h"

s32 func_00129C38(s32 arg0, s32 arg1, s32 arg2);
extern s32 D_003877B8;

typedef struct {
    s64 w[2];
} Pair16;

/* If D_003877B8 is set and arg0 has a block at +0x38 whose flag 2 at +0x56 is set, calls func_00129C38 on
   that block (+0x10) with a copy of the 16-byte arg1 and D_003877B8. */
void func_0018E1A8(void *arg0, void *arg1) {
    Pair16 c = *(Pair16 *)arg1;

    if (D_003877B8 != 0 && arg0 != NULL) {
        u8 *t = *(u8 **)((u8 *)arg0 + 0x38);
        if (t != NULL && (*(u16 *)(t + 0x56) & 2)) {
            func_00129C38((s32)(t + 0x10), (s32)&c, D_003877B8);
        }
    }
}
