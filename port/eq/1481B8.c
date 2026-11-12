#include "common.h"

extern u8 *D_00387760;
extern void BtlPool_SetCurrent(s32 arg0);
extern s32 BtlPool_GetCurrent(void);
extern void BtlPool_Free(s32 arg0, s32 arg1);
extern void BtlPool_Reset(s32 arg0);
extern void func_00148A80(s32 arg0, s32 arg1, s32 arg2);

void func_001481B8(void) {
    s32 i = 0;

    BtlPool_SetCurrent(3);
    BtlPool_Free(BtlPool_GetCurrent(), *(s32 *)(D_00387760 + 4));
    BtlPool_Free(BtlPool_GetCurrent(), (s32)D_00387760);
    D_00387760 = 0;
    BtlPool_Reset(3);
    BtlPool_Reset(4);
    BtlPool_Reset(5);
    do {
        func_00148A80(0, i, 0);
        func_00148A80(1, i, 0);
        i++;
    } while (i < 5);
}
