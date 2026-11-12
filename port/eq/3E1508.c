#include "common.h"

extern u8 *D_00427338 __attribute__((section(".data")));
extern s32 D_003B0B00[] __attribute__((section(".data")));
extern u8 D_004279B8[];

s32 func_0026EB60(u8 *arg0);
void func_0026EB78(u8 *arg0, u8 *arg1);
void func_00297FE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_00101438(s32 arg0);

#define G (D_00427338)
#define GW(o) (*(s32 *)(G + (o)))
#define PAD (*(u32 *)((u8 *)D_003B0B00 + 0x144))
#define PAD2 (*(u32 *)((u8 *)D_003B0B00 + 0x134))

static void Refresh(void) {
    if ((GW(0xCC) & 4) == 0) {
        func_00297FE0(0, 0, 0x40, 0x40, 1);
    }
}

void func_003E1508(s32 *arg0) {
    s32 a, b, d, e;

    if (func_0026EB60(G + 8) == 0) {
        return;
    }
    if (PAD & 0x50) {
        if (PAD & 0x10) {
            GW(0xD4) = GW(0xD4) - 1;
            if (GW(0xD4) >= 0) {
                if ((GW(0xCC) & 4) == 0) {
                    func_00297FE0(0, 0, 0x40, 0x40, 1);
                }
            } else {
                GW(0xD4) = 0;
            }
            if (GW(0xD4) < GW(0xD0)) {
                GW(0xD0) = GW(0xD4);
            }
            return;
        }
        if (PAD & 0x40) {
            GW(0xD4) = GW(0xD4) + 1;
            if (GW(0xD4) < GW(0xE8)) {
                if ((GW(0xCC) & 4) == 0) {
                    func_00297FE0(0, 0, 0x40, 0x40, 1);
                }
            } else {
                GW(0xD4) = GW(0xE8) - 1;
            }
            if (!(GW(0xD4) - 8 < GW(0xD0))) {
                GW(0xD0) = GW(0xD4) - 7;
            }
        }
        return;
    }
    if (PAD & 0xA0) {
        if (PAD & 0x80) {
            GW(0xD8) = GW(0xD8) - 1;
            if (GW(0xD8) < 0) {
                GW(0xD8) = 1;
            }
        } else if (PAD & 0x20) {
            GW(0xD8) = GW(0xD8) + 1;
            if (GW(0xD8) >= 2) {
                GW(0xD8) = 0;
            }
        }
        Refresh();
        return;
    }
    if (PAD & 0xC00) {
        a = GW(0xD0);
        b = GW(0xD4);
        d = b - a;
        if (PAD & 0x400) {
            if (a == 0) {
                if (b == 0) {
                    return;
                }
                GW(0xD4) = 0;
                Refresh();
                return;
            }
            GW(0xD0) = a - 8;
            if (GW(0xD0) < 0) {
                GW(0xD0) = 0;
            }
        } else {
            if (!(PAD & 0x800)) {
                return;
            }
            e = GW(0xE8);
            if (a == e - 8) {
                if (b == e - 1) {
                    return;
                }
                GW(0xD4) = e - 1;
                Refresh();
                return;
            }
            GW(0xD0) = a + 8;
            if (GW(0xE8) - 8 < GW(0xD0)) {
                GW(0xD0) = GW(0xE8) - 8;
            }
        }
        if ((GW(0xCC) & 4) == 0) {
            func_00297FE0(0, 0, 0x40, 0x40, 1);
        }
        GW(0xD4) = GW(0xD0) + d;
        return;
    }
    if (PAD & 0x200) {
        e = GW(0xE8) - 8;
        if (!(GW(0xD0) < e)) {
            return;
        }
        GW(0xD0) = e;
        GW(0xD4) = GW(0xE8) - 1;
        Refresh();
        return;
    }
    if (PAD & 0x100) {
        if (GW(0xD0) <= 0) {
            return;
        }
        GW(0xD0) = 0;
        GW(0xD4) = 0;
        Refresh();
        return;
    }
    if (PAD2 & 0x4000) {
        if (GW(0xD8) == 0) {
            GW(0xCC) = GW(0xCC) | 4;
            GW(0xCC) = GW(0xCC) & ~0x20;
            func_00101438(*(s32 *)(*(u8 **)(G + 0xE4) + GW(0xD4) * 8) + 0x3E1E);
            if ((u32)(GW(0xE0) - 0x20) >= 0x11) {
                GW(0xE0) = 0x20;
            }
            if (GW(0xCC) & 0x10) {
                return;
            }
            func_0026EB78(G + 0x30, D_004279B8);
            GW(0xCC) = GW(0xCC) | 0x10;
        } else {
            if ((GW(0xCC) & 4) == 0) {
                func_00297FE0(0, 1, 0x40, 0x40, 1);
            }
            GW(0xCC) = GW(0xCC) | 0x20;
            GW(0xCC) = GW(0xCC) & ~4;
        }
    } else if (PAD2 & 0x1000) {
        GW(0xCC) = GW(0xCC) | 2;
        *arg0 = 0;
        func_00297FE0(0, 2, 0x40, 0x40, 1);
    }
}
