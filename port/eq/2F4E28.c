#include "common.h"

extern s32 func_002EA050();
extern s32 func_002F14E0(s32 a0);
extern u8 D_0037C890[];

/* 0x002F4E28: NULL handle -> error call, -1; fmt (lb at +1) < 2 -> 0; else tail call with *(a0+4). */
s32 func_002F4E28(u8 *h) {
    if (h == 0) {
        func_002EA050(D_0037C890);
        return -1;
    }
    if (*(s8 *)(h + 1) < 2) {
        return 0;
    }
    return func_002F14E0(*(s32 *)(h + 4));
}
