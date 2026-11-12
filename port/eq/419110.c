#include "common.h"

extern u8 *D_0042BB80 __attribute__((section(".data")));
extern u8 *D_003876A4 __attribute__((section(".data")));
extern u8 *D_00387F2C __attribute__((section(".data")));
extern u8 *D_00421394 __attribute__((section(".data")));
extern u8 *D_004213A0 __attribute__((section(".data")));
extern u8 D_0042EED0[] __attribute__((section(".data")));

void *func_28BAA8(s32 arg0);
u8 *func_2B24C8(u8 *arg0, u8 *arg1, s32 arg2);
void Res_RelocateOffsets(u8 *arg0, u8 *arg1, u8 *arg2);
void func_26E7F0(u8 *arg0, u8 *arg1, u8 *arg2);
void func_26EAE0(u8 *arg0, s32 arg1);
void func_3B43F0(void);
void func_4190C0(void);

#define G (D_0042BB80)
#define GW(o) (*(s32 *)(G + (o)))
#define GP(o) (*(u8 **)(G + (o)))
#define BASE (GP(4))
/* section pointer: BASE + (BASE[o] >> 2 << 2) */
#define SEC(o) (BASE + (*(u32 *)(BASE + (o)) >> 2 << 2))

/* 0x00419110: builds the menu object (0x148 bytes) at D_0042BB80, resolving the sub-resources of a packed file. */
void func_00419110(s32 arg0) {
    u8 sp[0x80];
    u8 *a2;
    u8 *a0;
    s32 i;
    s32 cnt;

    *(u8 **)(sp + 0x40) = 0;
    G = func_28BAA8(0x148);
    __builtin_memset(G, 0, 0x148);
    if (*(s32 *)(D_003876A4 + 0x1C) == 0x40) {
        a0 = D_004213A0;
    } else {
        a0 = D_00421394;
    }
    GP(0) = a0 + (*(u32 *)(a0 + arg0 * 4) >> 2 << 2);
    GP(4) = func_2B24C8(GP(0), 0, 0);
    GP(0x58) = SEC(0x10);
    Res_RelocateOffsets(G + 0x58, GP(0x58), GP(0x58));
    GP(0xCC) = SEC(0x3C);
    Res_RelocateOffsets(G + 0xCC, GP(0xCC), GP(0xCC));

    *(u8 **)(sp + 0x40) = SEC(0x48);
    Res_RelocateOffsets(sp + 0x40, *(u8 **)(sp + 0x40), *(u8 **)(sp + 0x40));
    GW(0x88) = *(s32 *)(*(u8 **)(sp + 0x40) + 0x10);

    *(u8 **)(sp + 0x40) = SEC(0x38);
    Res_RelocateOffsets(sp + 0x40, *(u8 **)(sp + 0x40), *(u8 **)(sp + 0x40));
    GW(0x98) = *(s32 *)(*(u8 **)(sp + 0x40) + 0x10);

    *(u8 **)(sp + 0x40) = SEC(0x50);
    Res_RelocateOffsets(sp + 0x40, *(u8 **)(sp + 0x40), *(u8 **)(sp + 0x40));
    GW(0x8C) = *(s32 *)(*(u8 **)(sp + 0x40) + 0x10);

    *(u8 **)(sp + 0x40) = SEC(0x40);
    Res_RelocateOffsets(sp + 0x40, *(u8 **)(sp + 0x40), *(u8 **)(sp + 0x40));
    GW(0x64) = *(s32 *)(*(u8 **)(sp + 0x40) + 0x10);
    GW(0xAC) = *(s32 *)(*(u8 **)(sp + 0x40) + 0x10) + 0x40;

    *(u8 **)(sp + 0x40) = SEC(0x24);
    Res_RelocateOffsets(sp + 0x40, *(u8 **)(sp + 0x40), *(u8 **)(sp + 0x40));
    GW(0x60) = *(s32 *)(*(u8 **)(sp + 0x40) + 0x10);
    GW(0x68) = *(s32 *)(*(u8 **)(sp + 0x40) + 0x10) + 0x40;
    GW(0x94) = *(s32 *)(*(u8 **)(sp + 0x40) + 0x10) + 0x80;

    *(u8 **)(sp + 0x40) = SEC(0x28);
    Res_RelocateOffsets(sp + 0x40, *(u8 **)(sp + 0x40), *(u8 **)(sp + 0x40));
    GW(0x90) = *(s32 *)(*(u8 **)(sp + 0x40) + 0x10);

    *(u8 **)(sp + 0x40) = SEC(0x30);
    Res_RelocateOffsets(sp + 0x40, *(u8 **)(sp + 0x40), *(u8 **)(sp + 0x40));
    GW(0xA0) = *(s32 *)(*(u8 **)(sp + 0x40) + 0x10);
    GW(0xA4) = *(s32 *)(*(u8 **)(sp + 0x40) + 0x10) + 0x40;

    *(u8 **)(sp + 0x40) = SEC(0x44);
    Res_RelocateOffsets(sp + 0x40, *(u8 **)(sp + 0x40), *(u8 **)(sp + 0x40));
    GW(0xA8) = *(s32 *)(*(u8 **)(sp + 0x40) + 0x10);
    GW(0xB0) = *(s32 *)(*(u8 **)(sp + 0x40) + 0x10) + 0x40;
    GW(0xB4) = *(s32 *)(*(u8 **)(sp + 0x40) + 0x10) + 0x80;

    *(u8 **)(sp + 0x40) = SEC(0x54);
    Res_RelocateOffsets(sp + 0x40, *(u8 **)(sp + 0x40), *(u8 **)(sp + 0x40));
    GW(0x9C) = *(s32 *)(*(u8 **)(sp + 0x40) + 0x10);

    *(u8 **)(sp + 0x40) = SEC(0x34);
    Res_RelocateOffsets(sp + 0x40, *(u8 **)(sp + 0x40), *(u8 **)(sp + 0x40));
    for (i = 0; i < 7; i++) {
        GW(0x6C + i * 4) = *(s32 *)(*(u8 **)(sp + 0x40) + 0x10);
    }

    func_26E7F0(G + 0x30, SEC(4), G + 0x5C);
    func_26EAE0(G + 0x30, 0x3C);

    *(u8 **)(sp + 0x40) = SEC(0xC);
    Res_RelocateOffsets(sp + 0x40, *(u8 **)(sp + 0x40), *(u8 **)(sp + 0x40));
    GW(0xB8) = *(s32 *)(*(u8 **)(sp + 0x40) + 0x10);

    *(u8 **)(sp + 0x40) = SEC(0x2C);
    Res_RelocateOffsets(sp + 0x40, *(u8 **)(sp + 0x40), *(u8 **)(sp + 0x40));
    GW(0xBC) = *(s32 *)(*(u8 **)(sp + 0x40) + 0x10);

    func_26E7F0(G + 8, SEC(8), G + 0xB8);
    func_26EAE0(G + 8, 0x3C);

    __builtin_memcpy(sp, D_0042EED0, 0x40);
    for (i = 0; i < 16; i++) {
        if (i == 7 && *(s32 *)(D_003876A4 + 0x464) != 0) {
            continue;
        }
        if (*(s16 *)(D_00387F2C + *(s32 *)(sp + i * 4) * 4 + 0x1F32) != 0) {
            cnt = GW(0x13C);
            GW(0xFC + cnt * 4) = i;
            GW(0x13C) = cnt + 1;
        }
    }

    a2 = SEC(0x4C);
    GW(0x144) = *(s32 *)a2;
    GW(0x140) = (s32)(a2 + 4);
    if (*(s32 *)(D_003876A4 + 0x45C) >= GW(0x13C)) {
        *(s32 *)(D_003876A4 + 0x45C) = 0;
    }
    GW(0xD4) = *(s32 *)(D_003876A4 + 0x45C);
    GW(0xD8) = *(s32 *)(D_003876A4 + 0x460);
    GW(0xDC) = GW(0xD4) - 3;
    if (GW(0xDC) < 0) {
        GW(0xDC) = GW(0xDC) + GW(0x13C);
    }
    GW(0xE0) = *(s32 *)(D_00387F2C + 0x808) & 1;
    func_3B43F0();
    func_4190C0();
}
