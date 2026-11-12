#include "common.h"

extern u8 *D_0042A578 __attribute__((section(".data")));

void func_003F5E20(void);
void func_003F5E90(void);
void func_003F5D40(void);
s32 func_0026EB70(u8 *arg0);
void func_0026EBA8(u8 *arg0, s32 arg1);

#define G (D_0042A578)
#define GW(o) (*(s32 *)(G + (o)))
#define GF(o) (*(f32 *)(G + (o)))

static s32 EntryVal(void) {
    u8 *g = G;
    s32 idx = *(s32 *)(g + 0x140);
    s32 e = *(s32 *)(g + idx * 4 + 0x14C);
    return *(s32 *)(*(u8 **)(g + 0x1C4) + e * 56 + 8);
}

/* wait: 0x1AC counter until limit, then state++ and counter = 0 */
static void Wait(s32 limit) {
    GW(0x1AC) = GW(0x1AC) + 1;
    if (GW(0x1AC) == limit) {
        GW(0x1B0) = GW(0x1B0) + 1;
        GW(0x1AC) = 0;
    }
}

void func_003F7840(void) {
    s32 st = GW(0x1B0);
    f32 t;

    if (st == 0) {
        return;
    }
    switch (st) {
    case 1:
    case 0x15:
        GW(0x1AC) = 0;
        GW(0x1B0) = GW(0x1B0) + 1;
        if (EntryVal() < 2) {
            GW(0x1B0) = 0;
            return;
        }
        /* fallthrough */
    case 2:
    case 0x16:
        Wait((st == 1 || st == 2) ? 180 : 120);
        return;
    case 3:
    case 4:
        if (st == 3) {
            GW(0x1B4) = EntryVal() - 1;
            func_003F5E20();
            GW(0x1B0) = GW(0x1B0) + 1;
        }
        if ((func_0026EB70(G + 0x38) & 0x200) == 0) {
            return;
        }
        GW(0x1B4) = GW(0x1B4) - 1;
        if (GW(0x1B4) == 0) {
            GW(0x1B0) = 0x15;
        } else {
            func_003F5E20();
            func_0026EBA8(G + 0x38, 1);
        }
        return;
    case 0x17:
    case 0x18:
        if (st == 0x17) {
            GW(0x1B4) = EntryVal() - 1;
            func_003F5E90();
            GW(0x1B0) = GW(0x1B0) + 1;
        }
        if ((func_0026EB70(G + 0x38) & 0x200) == 0) {
            return;
        }
        GW(0x1B4) = GW(0x1B4) - 1;
        if (GW(0x1B4) == 0) {
            GW(0x1B0) = 1;
        } else {
            func_003F5E90();
            func_0026EBA8(G + 0x38, 1);
        }
        return;
    case 0x29:
        GW(0x13C) = GW(0x13C) | 4;
        GF(0x1B8) = GF(0x1B8) - 15.0f;
        if (!(GF(0x1B8) <= -256.0f)) {
            return;
        }
        GW(0x140) = GW(0x140) + 1;
        if (GW(0x188) - 1 < GW(0x140)) {
            GW(0x140) = 0;
        }
        func_003F5D40();
        GF(0x1B8) = 512.0f;
        GW(0x1B0) = GW(0x1B0) + 1;
        return;
    case 0x2A:
        GF(0x1B8) = GF(0x1B8) - 15.0f;
        if (GF(0x1B8) < 0.0f) {
            GW(0x13C) = GW(0x13C) & ~4;
            GF(0x1B8) = 0.0f;
            GW(0x1B0) = 1;
        }
        return;
    case 0x3D:
        GW(0x13C) = GW(0x13C) | 4;
        GF(0x1B8) = GF(0x1B8) + 15.0f;
        if (!(GF(0x1B8) >= 512.0f)) {
            return;
        }
        GW(0x140) = GW(0x140) - 1;
        if (GW(0x140) < 0) {
            GW(0x140) = GW(0x188) - 1;
        }
        func_003F5D40();
        GF(0x1B8) = -256.0f;
        GW(0x1B0) = GW(0x1B0) + 1;
        return;
    case 0x3E:
        GF(0x1B8) = GF(0x1B8) + 15.0f;
        if (GF(0x1B8) >= 0.0f) {
            GW(0x13C) = GW(0x13C) & ~4;
            GF(0x1B8) = 0.0f;
            GW(0x1B0) = 1;
        }
        return;
    default:
        return;
    }
}
