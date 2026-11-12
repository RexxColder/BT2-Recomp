#include "common.h"

void func_002ACE58(s32 arg0);
s32 func_002ABB40(void);
extern u8 D_003B26B0[] __attribute__((section(".data")));
extern u8 D_003B2600[] __attribute__((section(".data")));
extern u8 D_00387E0C;

/* 0x002AC1F8: state machine on G = D_003B26B0 (word 0 = mode, word 1 = state, word 2 at +8, byte flag D_00387E0C).
 * Mode 4: word +0x24 = 0; returns 1 when the flag is clear (else clears it and returns 0). Otherwise the flag is
 * cleared and, for state (word 1): 0 -> func_002ACE58(word -0x40) when mode 3 (return 1); 1 -> return 1;
 * 2..4 -> func_002ACE58(word +8), return 1; 5 -> word -0x24 = mode, func_002ACE58(word +8, or word -0x40 when
 * that is -1), then func_002ABB40() == 2 sets the flag and returns 1 (0 otherwise); 6 -> D_003B2600+0x54 |= 0x20000,
 * return 0. Other states return 0. */
s32 func_002AC1F8(void) {
    u8 *g = D_003B26B0;
    s32 mode = *(s32 *)g;
    s32 state;
    s32 t;

    if (mode == 4) {
        *(s32 *)(g + 0x24) = 0;
        if (D_00387E0C == 0) {
            return 1;
        }
        D_00387E0C = 0;
        return 0;
    }
    state = *(s32 *)(g + 0x4);
    D_00387E0C = 0;
    if ((u32)state >= 7) {
        return 0;
    }
    switch (state) {
        case 0:
            if (mode != 3) {
                return 1;
            }
            func_002ACE58(*(s32 *)(g - 0x40));
            return 1;
        case 1:
            return 1;
        case 2:
        case 3:
        case 4:
            func_002ACE58(*(s32 *)(g + 0x8));
            return 1;
        case 5:
            t = *(s32 *)(g + 0x8);
            *(s32 *)(g - 0x24) = mode;
            if (t == -1) {
                func_002ACE58(*(s32 *)(g - 0x40));
            } else {
                func_002ACE58(t);
            }
            if (func_002ABB40() != 2) {
                return 0;
            }
            D_00387E0C = 1;
            return 1;
        case 6:
            *(s32 *)(D_003B2600 + 0x54) |= 0x20000;
            return 0;
    }
    return 0;
}
