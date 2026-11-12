#include "common.h"

void *memset(void *dst, s32 val, u32 n);
extern u8 *D_00387E9C;

void func_001DBDF8(void) {
    u8 *p = D_00387E9C;

    if (p != NULL) {
        memset(p, 0, 0x1400);
        memset(*(void **)(p + 0x1400), 0, 0x28);
        memset(*(void **)(p + 0x1404), 0, (u32)*(s32 *)(p + 0x16C0) * 0xA0);
        memset(*(void **)(p + 0x1408), 0, 0xC80);
        memset(*(void **)(p + 0x140C), 0, 0x6C0);
        memset(*(void **)(p + 0x1410), 0, 0x12C0);
        memset(*(void **)(p + 0x1414), 0, 0xF00);
        memset(*(void **)(p + 0x1418), 0, 0x7D0);
        memset(*(void **)(p + 0x141C), 0, (u32)*(s32 *)(p + 0x16B8) * 0x70);
        memset(*(void **)(p + 0x1420), 0, (u32)*(s32 *)(p + 0x16BC) * 0x70);
        *(s32 *)(p + 0x1424) = 0;
        *(s32 *)(p + 0x1444) = 0;
        *(s32 *)(p + 0x1440) = 0;
        *(s32 *)(p + 0x143C) = 0;
        *(s32 *)(p + 0x1438) = 0;
        *(s32 *)(p + 0x1434) = 0;
        *(s32 *)(p + 0x1430) = 0;
        *(s32 *)(p + 0x142C) = 0;
        *(s32 *)(p + 0x1428) = 0;
    }
}
