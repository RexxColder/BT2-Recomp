#include "common.h"

extern u8 *D_0042FD74 __attribute__((section(".data")));
extern u8 *D_004213AC __attribute__((section(".data")));
extern u8 *D_387F2C __attribute__((section(".data")));
extern u8 *D_3876A4 __attribute__((section(".data")));

extern u8 *func_28BAA8(s32 a0);
extern u8 *func_2B24C8(u8 *a0, u8 *a1, s32 a2);
extern s64 GetTimerSystemTime(void);
extern void func_325370(s64 a0);
extern void Res_RelocateOffsets(u8 *a0, u8 *a1, u8 *a2);
extern void func_24BED8(u8 *a0, s32 a1);
extern void func_26E7F0(u8 *a0, u8 *a1, u8 *a2);
extern void func_26EAE0();
extern s32 func_24B3D8();

#define G (D_0042FD74)
#define W(off) (*(s32 *)(G + (off)))
#define P(off) (*(u8 **)(G + (off)))
#define G4 (P(4))
/* pointer = G4 + (word at G4+off with the low 2 bits cleared) */
#define OFS(off) (G4 + ((*(u32 *)(G4 + (off)) >> 2) << 2))
#define REL(off) do { sp0 = OFS(off); Res_RelocateOffsets((u8 *)&sp0, sp0, sp0); } while (0)
#define S10 (*(s32 *)(sp0 + 0x10))

/* 0x0041CF48: builds the menu resource object (D_0042FD74) from the resource pack index arg0 */
s32 func_0041CF48(s32 arg0) {
    u8 *sp0;
    u8 *base;
    s32 i, j, e, s2, cnt, a2, r, c;
    f32 f;

    sp0 = 0;
    G = func_28BAA8(0x32C);
    __builtin_memset(G, 0, 0x32C);
    base = D_004213AC;
    P(0) = base + ((*(u32 *)(base + arg0 * 4) >> 2) << 2);
    G4 = func_2B24C8(P(0), 0, 0);
    func_325370((s32)GetTimerSystemTime());

    REL(0x14);
    P(0x6C) = sp0;
    REL(0x7C);
    W(0xB8) = S10;
    REL(0x60);
    W(0x90) = S10;
    W(0x80) = S10 + 0x40;
    REL(0x64);
    func_24BED8(OFS(0x80), S10);
    W(0xCC) = S10 + 0x40;
    REL(0x30);
    P(0x70) = sp0;
    REL(0x34);
    P(0x74) = sp0;
    REL(0x38);
    P(0x78) = sp0;
    REL(0x3C);
    P(0x7C) = sp0;
    REL(0x58);
    W(0xBC) = S10;
    W(0xD0) = S10 + 0x40;
    W(0xD4) = S10 + 0x80;
    W(0xC0) = S10 + 0xC0;
    REL(0x4C);
    W(0xC4) = S10;
    REL(0x20);
    W(0xC8) = S10;
    W(0xE0) = S10 + 0x40;
    REL(0x50);
    W(0xD8) = S10;
    REL(0x54);
    W(0xDC) = S10;
    REL(0x10);
    W(0xE4) = S10;
    REL(0x8);
    W(0xE8) = S10;
    REL(0x2C);
    W(0xEC) = S10;
    W(0x100) = S10 + 0x40;
    REL(0x24);
    W(0x104) = S10;
    REL(0x74);
    W(0xF8) = S10;
    REL(0x28);
    W(0x118) = S10;
    REL(0x5C);
    W(0x110) = S10;
    REL(0x78);
    W(0x114) = S10;
    REL(0x48);
    W(0x11C) = S10;
    REL(0x44);
    W(0x120) = S10;
    REL(0x40);
    W(0x124) = S10;
    W(0x128) = S10 + 0x40;

    func_26E7F0(G + 0x44, G4 + ((*(u32 *)(G4 + 4) >> 2) << 2), G + 0x80);
    func_26EAE0(G + 0x44, 0x3C);
    REL(0x18);
    W(0x130) = S10;
    W(0x12C) = S10 + 0x40;
    func_26E7F0(G + 0x1C, G4 + ((*(u32 *)(G4 + 0x1C) >> 2) << 2), G + 0x12C);
    func_26EAE0(G + 0x1C, 0x3C);
    P(0x14) = OFS(0x6C);
    P(0x10) = OFS(0x68);
    P(0x18) = OFS(0x70);
    P(0x328) = OFS(0xC);

    P(8) = func_28BAA8(0xB800);
    P(0xC) = func_28BAA8(0x20560);

    for (i = 0; i < 0x19; i++) {
        if (i == 0x17) continue;
        if (*(s16 *)(D_387F2C + 0x2548 + i * 4 + 2) != 0) {
            c = W(0x1B0);
            W(0x148 + c * 4) = i;
            W(0x1B0) = c + 1;
        }
    }

    if (W(0x1B0) > 0) {
        if (W(0x148) == *(s32 *)(D_3876A4 + 0x30)) {
            W(0x1AC) = 0;
        } else {
            for (i = 1; i < W(0x1B0); i++) {
                if (W(0x148 + i * 4) == *(s32 *)(D_3876A4 + 0x30)) {
                    W(0x1AC) = i;
                    break;
                }
            }
        }
    }

    W(0x1B4) = W(0x1AC) - 1;
    if (W(0x1B4) < 0) W(0x1B4) = W(0x1B4) + W(0x1B0);

    s2 = 0;
    for (i = 0; i < 0x19; i++) {
        if (i == 0x17) continue;
        W(0x21C + i * 4) = 1;
        for (j = 0; j < func_24B3D8(i) - 1; j++) {
            if (*(s8 *)(D_387F2C + s2 + j + 0xC) != 0) W(0x21C + i * 4) = W(0x21C + i * 4) + 1;
        }
        s2 = s2 + func_24B3D8(i);
    }

    e = W(0x148 + W(0x1AC) * 4);
    W(0x1B8 + e * 4) = *(s32 *)(D_3876A4 + 0x34);
    e = W(0x148 + W(0x1AC) * 4);
    r = W(0x1B8 + e * 4);
    if (r < W(0x21C + e * 4)) {
        W(0x280 + e * 4) = r;
        e = W(0x148 + W(0x1AC) * 4);
        a2 = W(0x280 + e * 4) + 5;
        if (W(0x21C + e * 4) < a2) {
            for (;;) {
                e = W(0x148 + W(0x1AC) * 4);
                W(0x280 + e * 4) = W(0x280 + e * 4) - 1;
                e = W(0x148 + W(0x1AC) * 4);
                a2 = a2 - 1;
                if (W(0x280 + e * 4) <= 0) {
                    W(0x280 + e * 4) = 0;
                    break;
                }
                if (!(W(0x21C + e * 4) < a2)) break;
            }
        }
    } else {
        W(0x1B8 + e * 4) = 0;
        e = W(0x148 + W(0x1AC) * 4);
        W(0x280 + e * 4) = 0;
    }

    cnt = 0;
    for (i = 0; i < 200; i++) {
        if (*(s8 *)(D_387F2C + 0xC + i) != 0) cnt = cnt + 1;
    }
    f = (f32)cnt / 200.0f * 100.0f;
    W(0x2EC) = (s32)f;
    if (cnt != 0 && W(0x2EC) == 0) W(0x2EC) = 1;
    if (W(0x2EC) == 100 && (*(s32 *)(D_387F2C + 8) & 2) == 0) {
        W(0x134) = W(0x134) | 0x40;
        *(s32 *)(D_387F2C + 8) = *(s32 *)(D_387F2C + 8) | 2;
    }
    W(0x2E8) = 1;
    W(0x134) = W(0x134) | 0x20;
    return W(0x134);
}
