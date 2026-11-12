#include "common.h"

extern u8 *D_00387760;

/* 0x00148530: address of record arg0 (0x270 bytes each) in the array at D_00387760 + 4, plus arg1 * 0x50. */
u8 *func_00148530(s32 arg0, s32 arg1) {
    if (D_00387760 == NULL) {
        return NULL;
    }
    return *(u8 **)(D_00387760 + 4) + arg0 * 0x270 + arg1 * 0x50;
}
