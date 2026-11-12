#include "common.h"

s32 BtlPool_GetCurrent(void);
void BtlPool_Free(s32 arg0, s32 arg1);
extern u8 *D_00387E9C;

void func_001D2CB8(void) {
    s32 a0;
    s32 a1;

    if (*(s32 *)(D_00387E9C + 0x1420) != 0) {
        a0 = BtlPool_GetCurrent();
        a1 = *(s32 *)(D_00387E9C + 0x1420);
        BtlPool_Free(a0, a1);
        *(s32 *)(D_00387E9C + 0x1420) = 0;
    }
    if (*(s32 *)(D_00387E9C + 0x141C) != 0) {
        a0 = BtlPool_GetCurrent();
        a1 = *(s32 *)(D_00387E9C + 0x141C);
        BtlPool_Free(a0, a1);
        *(s32 *)(D_00387E9C + 0x141C) = 0;
    }
    if (*(s32 *)(D_00387E9C + 0x1418) != 0) {
        a0 = BtlPool_GetCurrent();
        a1 = *(s32 *)(D_00387E9C + 0x1418);
        BtlPool_Free(a0, a1);
        *(s32 *)(D_00387E9C + 0x1418) = 0;
    }
    if (*(s32 *)(D_00387E9C + 0x1414) != 0) {
        a0 = BtlPool_GetCurrent();
        a1 = *(s32 *)(D_00387E9C + 0x1414);
        BtlPool_Free(a0, a1);
        *(s32 *)(D_00387E9C + 0x1414) = 0;
    }
    if (*(s32 *)(D_00387E9C + 0x1410) != 0) {
        a0 = BtlPool_GetCurrent();
        a1 = *(s32 *)(D_00387E9C + 0x1410);
        BtlPool_Free(a0, a1);
        *(s32 *)(D_00387E9C + 0x1410) = 0;
    }
    if (*(s32 *)(D_00387E9C + 0x140C) != 0) {
        a0 = BtlPool_GetCurrent();
        a1 = *(s32 *)(D_00387E9C + 0x140C);
        BtlPool_Free(a0, a1);
        *(s32 *)(D_00387E9C + 0x140C) = 0;
    }
    if (*(s32 *)(D_00387E9C + 0x1408) != 0) {
        a0 = BtlPool_GetCurrent();
        a1 = *(s32 *)(D_00387E9C + 0x1408);
        BtlPool_Free(a0, a1);
        *(s32 *)(D_00387E9C + 0x1408) = 0;
    }
    if (*(s32 *)(D_00387E9C + 0x1404) != 0) {
        a0 = BtlPool_GetCurrent();
        a1 = *(s32 *)(D_00387E9C + 0x1404);
        BtlPool_Free(a0, a1);
        *(s32 *)(D_00387E9C + 0x1404) = 0;
    }
    if (*(s32 *)(D_00387E9C + 0x1400) != 0) {
        a0 = BtlPool_GetCurrent();
        a1 = *(s32 *)(D_00387E9C + 0x1400);
        BtlPool_Free(a0, a1);
        *(s32 *)(D_00387E9C + 0x1400) = 0;
    }
    if (D_00387E9C != 0) {
        a0 = BtlPool_GetCurrent();
        a1 = (s32)D_00387E9C;
        BtlPool_Free(a0, a1);
        D_00387E9C = 0;
    }
}
