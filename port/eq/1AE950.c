#include "common.h"

void BtlPool_Free(s32 arg0, s32 arg1);
s32 BtlPool_GetCurrent(void);
extern u8 *D_00387858;

void func_001AE950(void) {
    if (*(s32 *)(D_00387858 + 0x170) != 0) {
        BtlPool_Free(BtlPool_GetCurrent(), *(s32 *)(D_00387858 + 0x170));
        *(s32 *)(D_00387858 + 0x170) = 0;
    }
    if (*(s32 *)(D_00387858 + 8) != 0) {
        BtlPool_Free(BtlPool_GetCurrent(), *(s32 *)(D_00387858 + 8));
        *(s32 *)(D_00387858 + 8) = 0;
    }
    if (D_00387858 != 0) {
        BtlPool_Free(BtlPool_GetCurrent(), (s32)D_00387858);
        D_00387858 = 0;
    }
}
