#include "common.h"

s32 BtlPool_GetCurrent(void);
void *BtlPool_Alloc(s32 arg0, s32 arg1);
void EftTexSet_Load32(void *arg0, s32 arg1);
void Fade_UpdateAll(void);
s32 func_00126460(s32 arg0, void *arg1);
s32 func_00126560(void);
void func_001D2FD8(void);
void *memset(void *arg0, s32 arg1, u32 arg2);

extern u8 *D_00387E9C;

void func_001D29B0(void) {
    s32 s0;
    s32 s1;
    s32 s2;

    s1 = 0x1E;
    s2 = 0x20;
    if (func_00126560() != 0) {
        s1 = 0x190;
        s2 = 0x190;
    }
    if (D_00387E9C == 0) {
        D_00387E9C = BtlPool_Alloc(BtlPool_GetCurrent(), 0x16D0);
        memset(D_00387E9C, 0, 0x16D0);
    }
    if (*(s32 *)(D_00387E9C + 0x1400) == 0) {
        *(void **)(D_00387E9C + 0x1400) = BtlPool_Alloc(BtlPool_GetCurrent(), 0x28);
        memset(*(void **)(D_00387E9C + 0x1400), 0, 0x28);
    }
    if (*(s32 *)(D_00387E9C + 0x1404) == 0) {
        s0 = s2 * 0xA0;
        *(void **)(D_00387E9C + 0x1404) = BtlPool_Alloc(BtlPool_GetCurrent(), s0);
        memset(*(void **)(D_00387E9C + 0x1404), 0, s0);
    }
    if (*(s32 *)(D_00387E9C + 0x1408) == 0) {
        *(void **)(D_00387E9C + 0x1408) = BtlPool_Alloc(BtlPool_GetCurrent(), 0xC80);
        memset(*(void **)(D_00387E9C + 0x1408), 0, 0xC80);
    }
    if (*(s32 *)(D_00387E9C + 0x140C) == 0) {
        *(void **)(D_00387E9C + 0x140C) = BtlPool_Alloc(BtlPool_GetCurrent(), 0x6C0);
        memset(*(void **)(D_00387E9C + 0x140C), 0, 0x6C0);
    }
    if (*(s32 *)(D_00387E9C + 0x1410) == 0) {
        *(void **)(D_00387E9C + 0x1410) = BtlPool_Alloc(BtlPool_GetCurrent(), 0x12C0);
        memset(*(void **)(D_00387E9C + 0x1410), 0, 0x12C0);
    }
    if (*(s32 *)(D_00387E9C + 0x1414) == 0) {
        *(void **)(D_00387E9C + 0x1414) = BtlPool_Alloc(BtlPool_GetCurrent(), 0xF00);
        memset(*(void **)(D_00387E9C + 0x1414), 0, 0xF00);
    }
    if (*(s32 *)(D_00387E9C + 0x1418) == 0) {
        *(void **)(D_00387E9C + 0x1418) = BtlPool_Alloc(BtlPool_GetCurrent(), 0x7D0);
        memset(*(void **)(D_00387E9C + 0x1418), 0, 0x7D0);
    }
    if (*(s32 *)(D_00387E9C + 0x141C) == 0) {
        s0 = s1 * 0x70;
        *(void **)(D_00387E9C + 0x141C) = BtlPool_Alloc(BtlPool_GetCurrent(), s0);
        memset(*(void **)(D_00387E9C + 0x141C), 0, s0);
    }
    if (*(s32 *)(D_00387E9C + 0x1420) == 0) {
        *(void **)(D_00387E9C + 0x1420) = BtlPool_Alloc(BtlPool_GetCurrent(), 0xD20);
        memset(*(void **)(D_00387E9C + 0x1420), 0, 0xD20);
    }
    *(s32 *)(D_00387E9C + 0x16B8) = s1;
    *(s32 *)(D_00387E9C + 0x16BC) = 0x1E;
    *(s32 *)(D_00387E9C + 0x16C0) = s2;
    EftTexSet_Load32(D_00387E9C + 0x14B0, func_00126460(0x1E, D_00387E9C));
    Fade_UpdateAll();
    func_001D2FD8();
}
