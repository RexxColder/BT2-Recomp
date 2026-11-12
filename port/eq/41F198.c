#include "common.h"

extern u8 *D_0042FD74 __attribute__((section(".data")));
extern u8 D_003B0B00[] __attribute__((section(".data")));

extern s32 func_0026EB60();
extern s32 func_0026EB78();
extern s32 rand();
extern void func_0041CF08(void);
extern void func_0041CAD8(s32 idx);
extern void func_0041E8E8(void);
extern void func_00243A80(s32 a0, s32 a1, s32 a2);
extern void func_002493C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
extern void EftShotFx_Update_2494A0();
extern void func_00297FE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

#define G (D_0042FD74)
#define W(off) (*(s32 *)(G + (off)))

/* 0x0041F198: menu input handler; G = D_0042FD74, state W(0x2F0) (0,1,2). pad words D_003B0B00+0x144 / +0x134. */
void func_0041F198(s32 *arg0) {
    s32 pad144, pad134, st, v, r, n, a, b;
    s32 *p;

    if (func_0026EB60(G + 0x44) == 0) {
        return;
    }
    st = W(0x2F0);
    if (st == 1) {
        pad144 = *(s32 *)(D_003B0B00 + 0x144);
        if (pad144 & 0x10) {
            W(0x2F4) = 0;
            n = *(s32 *)(G + 0x148 + W(0x1AC) * 4);
            p = (s32 *)(G + 0x1B8 + n * 4);
            v = *p;
            if (v <= 0) {
                return;
            }
            *p = v - 1;
            n = *(s32 *)(G + 0x148 + W(0x1AC) * 4);
            p = (s32 *)(G + 0x280 + n * 4);
            a = *(s32 *)(G + 0x1B8 + n * 4);
            b = *p;
            if (a < b) {
                *p = b - 1;
            }
            func_00297FE0(0, 0, 0x40, 0x40, 1);
            return;
        }
        if (pad144 & 0x40) {
            W(0x2F4) = 0;
            n = *(s32 *)(G + 0x148 + W(0x1AC) * 4);
            p = (s32 *)(G + 0x1B8 + n * 4);
            v = *p;
            if (!(v < *(s32 *)(G + 0x21C + n * 4) - 1)) {
                return;
            }
            *p = v + 1;
            n = *(s32 *)(G + 0x148 + W(0x1AC) * 4);
            p = (s32 *)(G + 0x280 + n * 4);
            a = *(s32 *)(G + 0x1B8 + n * 4);
            b = *p;
            if (b + 4 < a) {
                *p = b + 1;
            }
            func_00297FE0(0, 0, 0x40, 0x40, 1);
            return;
        }
        pad134 = *(s32 *)(D_003B0B00 + 0x134);
        if (pad134 & 0x4000) {
            W(0x2F4) = 0;
            W(0x2F0) = 2;
            func_0026EB78(G + 0x44, "fr_da_5");
            W(0x300) = 0x65;
            W(0x134) = W(0x134) & ~0x10;
            func_00297FE0(0, 1, 0x40, 0x40, 1);
            return;
        }
        if (pad134 & 0x1000) {
            W(0x2F4) = 0;
            W(0x2F0) = 0;
            W(0x134) = W(0x134) & ~0x10;
            func_0026EB78(G + 0x44, "fr_da_4_out");
            func_00297FE0(0, 2, 0x40, 0x40, 1);
            W(0x13C) = -1;
            EftShotFx_Update_2494A0();
            return;
        }
        W(0x2F4) = W(0x2F4) + 1;
        if (W(0x2F4) != 600) {
            return;
        }
        r = rand();
        W(0x13C) = r % 2 + 25;
        W(0x324) = 1;
        v = W(0x13C);
        func_002493C0(W(0x14), 0x33FA, 0x3813, 0, v);
        W(0x2F4) = 0;
        return;
    }
    if (st < 2) {
        if (st != 0) {
            return;
        }
        pad144 = *(s32 *)(D_003B0B00 + 0x144);
        if (pad144 & 0x10) {
            W(0x2F4) = 0;
            if (W(0x1B0) == 1) {
                return;
            }
            W(0x1AC) = W(0x1AC) - 1;
            if (W(0x1AC) < 0) {
                W(0x1AC) = W(0x1B0) - 1;
            }
            func_0041E8E8();
            func_00297FE0(0, 0, 0x40, 0x40, 1);
            return;
        }
        if (pad144 & 0x40) {
            W(0x2F4) = 0;
            if (W(0x1B0) == 1) {
                return;
            }
            W(0x1AC) = W(0x1AC) + 1;
            if (W(0x1B0) - 1 < W(0x1AC)) {
                W(0x1AC) = 0;
            }
            func_0041E8E8();
            func_00297FE0(0, 0, 0x40, 0x40, 1);
            return;
        }
        pad134 = *(s32 *)(D_003B0B00 + 0x134);
        if (pad134 & 0x4000) {
            W(0x2F4) = 0;
            W(0x2F0) = 1;
            func_0026EB78(G + 0x44, "fr_da_3");
            W(0x300) = 0x33;
            func_0041CF08();
            func_0041CAD8(*(s32 *)(G + W(0x1AC) * 4 + 0x148));
            func_00297FE0(0, 1, 0x40, 0x40, 1);
            return;
        }
        if (pad134 & 0x1000) {
            W(0x2F4) = 0;
            func_00243A80(0, 0, 0);
            *arg0 = 0;
            func_00297FE0(0, 2, 0x40, 0x40, 1);
            return;
        }
        W(0x2F4) = W(0x2F4) + 1;
        if (W(0x2F4) != 600) {
            return;
        }
        r = rand();
        v = (r - ((r < 0 ? r + 3 : r) >> 2 << 2)) + 11;
        W(0x13C) = v;
        v = W(0x13C);
        if (v == 12) {
            W(0x324) = 1;
        } else if (v < 13) {
            if (v == 11) {
                W(0x324) = 2;
            }
        } else if (v == 13) {
            W(0x324) = 2;
        } else if (v == 14) {
            W(0x324) = 3;
        }
        func_002493C0(W(0x14), 0x33FA, 0x3813, 0, W(0x13C));
        W(0x2F4) = 0;
        return;
    }
    if (st != 2) {
        return;
    }
    pad144 = *(s32 *)(D_003B0B00 + 0x144);
    if (pad144 & 0x80) {
        W(0x2F4) = 0;
        W(0x2E8) = W(0x2E8) - 1;
        if (W(0x2E8) < 0) {
            W(0x2E8) = 2;
        }
        func_00297FE0(0, 0, 0x40, 0x40, 1);
        return;
    }
    if (pad144 & 0x20) {
        W(0x2F4) = 0;
        W(0x2E8) = W(0x2E8) + 1;
        if (!(W(0x2E8) < 3)) {
            W(0x2E8) = 0;
        }
        func_00297FE0(0, 0, 0x40, 0x40, 1);
        return;
    }
    pad134 = *(s32 *)(D_003B0B00 + 0x134);
    if (pad134 & 0x4000) {
        W(0x2F4) = 0;
        W(0x13C) = 0x20;
        W(0x324) = 2;
        func_002493C0(W(0x14), 0x33FA, 0x3813, 0, W(0x13C));
        W(0x300) = 0x97;
        func_00297FE0(0, 1, 0x40, 0x40, 1);
        return;
    }
    if (pad134 & 0x1000) {
        W(0x2F4) = 0;
        W(0x2F0) = 1;
        func_0026EB78(G + 0x44, "fr_da_5_out");
        W(0x300) = 0x46;
        func_00297FE0(0, 2, 0x40, 0x40, 1);
        return;
    }
    W(0x2F4) = W(0x2F4) + 1;
    if (W(0x2F4) != 600) {
        return;
    }
    r = rand();
    W(0x13C) = r % 2 + 30;
    W(0x324) = 1;
    func_002493C0(W(0x14), 0x33FA, 0x3813, 0, W(0x13C));
    W(0x2F4) = 0;
}
