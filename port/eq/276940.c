#include "common.h"

extern s32 D_003876A0;

s32 BtlStage_GetFileMember(s32 arg0) {
    s32 a3 = arg0 << 2;
    s32 t0 = 0;
    s32 a2;
    s32 addr;
    s32 base;
    u32 x;
    u32 y;

    if (*(s64 *)(D_003876A0 + 0x4D8) & ((s64)0x8000 << 47)) {
        a2 = *(s32 *)(D_003876A0 + 4) + 0x40;
        addr = a3 + a2;
        x = *(u32 *)(addr + 0xC);
        y = *(u32 *)(addr + 0x10);
        if (y != x) {
            t0 = a2 + (s32)((x >> 2) << 2);
        }
    } else {
        base = *(s32 *)(D_003876A0 + 4);
        addr = a3 + base;
        x = *(u32 *)(addr + 0xC);
        y = *(u32 *)(addr + 0x10);
        if (y != x) {
            t0 = base + (s32)((x >> 2) << 2);
        }
    }
    return t0;
}
