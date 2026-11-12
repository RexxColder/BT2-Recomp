#include "common.h"

extern u8 *D_00421C94 __attribute__((section(".data")));
extern u8 *D_00387F2C __attribute__((section(".data")));
extern s32 D_003B0B00[] __attribute__((section(".data")));

s32 func_0026EB60(u8 *arg0);
void func_00297FE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_0029C550(s32 arg0);
void func_0029C820(s32 arg0);
void func_0029C7E0(s32 arg0);
void func_0029C810(s32 arg0);
void EftShotFx_Update_2494A0(void);

#define G (D_00421C94)
#define GW(o) (*(s32 *)(G + (o)))
#define PAD (*(u32 *)((u8 *)D_003B0B00 + 0x144))
#define PAD2 (*(u32 *)((u8 *)D_003B0B00 + 0x134))
#define SND(a1) func_00297FE0(0, (a1), 0x40, 0x40, 1)

void func_003BF270(s32 *arg0) {
    s32 v;

    if (func_0026EB60(G + 0x470) == 0) {
        return;
    }
    if (GW(0x20) > 0) {
        return;
    }
    if ((PAD & 0x10) && GW(0x54C) <= 0) {
        GW(0x520) = GW(0x520) - 1;
        if (GW(0x520) >= 0) {
            SND(0);
        } else {
            GW(0x520) = 0;
        }
        if (GW(0x520) < GW(0x524)) {
            GW(0x524) = GW(0x520);
        }
        GW(0x54C) = 6;
        return;
    }
    if ((PAD & 0x40) && GW(0x54C) <= 0) {
        GW(0x520) = GW(0x520) + 1;
        if (GW(0x520) < 10) {
            SND(0);
        } else {
            GW(0x520) = 9;
        }
        v = GW(0x520) - 2;
        if (GW(0x524) < v) {
            GW(0x524) = v;
        }
        GW(0x54C) = 6;
        return;
    }
    if (PAD & 0x480) {
        if (GW(0x524) > 0) {
            GW(0x524) = GW(0x524) - 3;
            GW(0x520) = GW(0x520) - 3;
            while (GW(0x524) < 0) {
                GW(0x524) = GW(0x524) + 1;
                GW(0x520) = GW(0x520) + 1;
            }
        } else {
            if (GW(0x520) <= 0) {
                return;
            }
            GW(0x520) = 0;
        }
        SND(0);
        return;
    }
    if (PAD & 0x820) {
        if (GW(0x524) < 7) {
            GW(0x524) = GW(0x524) + 3;
            GW(0x520) = GW(0x520) + 3;
            while (GW(0x524) >= 8) {
                GW(0x524) = GW(0x524) - 1;
                GW(0x520) = GW(0x520) - 1;
            }
        } else {
            if (GW(0x520) >= 9) {
                return;
            }
            GW(0x520) = 9;
        }
        SND(0);
        return;
    }
    if (PAD & 0x100) {
        if (GW(0x520) <= 0) {
            return;
        }
        GW(0x520) = 0;
        GW(0x524) = 0;
        SND(0);
        return;
    }
    if (PAD & 0x200) {
        if (GW(0x520) >= 9) {
            return;
        }
        GW(0x520) = 9;
        GW(0x524) = 7;
        SND(0);
        return;
    }
    if (PAD2 & 8) {
        if (*(u16 *)(D_00387F2C + GW(0x520) * 34 + 0x1DFC) & 1) {
            GW(0x20) = 0x19;
            func_0029C550(0);
            func_0029C820(1);
            func_0029C7E0(1);
            func_0029C810(0);
            EftShotFx_Update_2494A0();
            SND(1);
        } else {
            SND(7);
        }
        return;
    }
    if (PAD2 & 0x1000) {
        *arg0 = 0;
        SND(2);
        if (GW(0x52C) & 0x40) {
            GW(0x20) = 10;
            func_0029C550(0);
            func_0029C820(1);
            func_0029C7E0(1);
            func_0029C810(0);
        } else {
            GW(0x52C) = GW(0x52C) | 2;
        }
        return;
    }
    if (PAD2 & 0x4000) {
        if (*(u16 *)(D_00387F2C + GW(0x520) * 34 + 0x1DFC) & 1) {
            GW(0x52C) = GW(0x52C) | 0x80;
            SND(1);
        } else {
            SND(7);
        }
    }
}
