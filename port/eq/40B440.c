#include "common.h"

extern u8 *D_0042BB78 __attribute__((section(".data")));
extern u8 *D_00421394 __attribute__((section(".data")));
extern u8 *D_3876A4 __attribute__((section(".data")));
extern u8 *D_00387F2C __attribute__((section(".data")));
extern u8 gMcCardPort[] __attribute__((section(".data")));
extern u8 D_0042DF98[];
extern u8 D_0042DFC8[];

u8 *func_0028BAA8(s32 arg0);
u8 *func_002B24C8(u8 *arg0, s32 arg1, s32 arg2);
void Res_RelocateOffsets(u8 *arg0, u8 *arg1, u8 *arg2);
void func_0026E7F0(u8 *arg0, u8 *arg1, u8 *arg2);
void func_0026EAE0(u8 *arg0, s32 arg1);
void func_0029BB88(u8 *arg0, u8 *arg1);
void func_0028A0B8(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3, s32 arg4);
void func_00248708(u8 *a0, u8 *a1, u8 *a2, u8 *a3);
s32 func_0024ACB8(s32 arg0, s32 arg1);
void McCard_GetInfoSync(s32 port);
void func_00288348(void);
void func_0029C550(s32 arg0);
void func_0029C820(s32 arg0);
void func_0029C7E0(s32 arg0);
void func_0029C810(s32 arg0);
void func_0040A710(s32 arg0);

/* pointer stored in the menu context m */
#define MP(o) (*(u8 **)(m + (o)))
/* word in the menu context m */
#define MW(o) (*(s32 *)(m + (o)))
/* section of a resource pack: pack + (offset word at pack+o, 4-aligned) */
#define SUB(base, o) ((base) + (*(u32 *)((base) + (o)) & ~3u))
#define GMC(o) (*(s32 *)(gMcCardPort + (o)))

/* Relocate the sub-block of `pack` whose offset word is at pack+off and return the (possibly updated) pointer. */
static u8 *RelocSection(u8 *pack, s32 off) {
    u8 sp[0x10] __attribute__((aligned(16)));
    u8 *sec = SUB(pack, off);

    *(u8 **)sp = sec;
    Res_RelocateOffsets(sp, sec, sec);
    return *(u8 **)sp;
}

/* 0x0040B440: menu context setup (alloc 0xBC14), resource sections, memcard buffers, slot tables */
s32 func_0040B440(s32 arg0) {
    u8 *m;
    u8 *pack;
    u8 *r;
    u8 *slots;
    s32 i;
    s32 j;
    s32 k;
    s32 v;

    m = func_0028BAA8(0xBC14);
    D_0042BB78 = m;
    __builtin_memset(m, 0, 0xBC14);
    MP(0) = D_00421394 + (*(u32 *)(D_00421394 + arg0 * 4) & ~3u);
    MP(4) = func_002B24C8(MP(0), 0, 0);
    MW(0x37C8) = *(s32 *)(D_3876A4 + 0x458);
    pack = MP(4);

    MP(0x118) = RelocSection(pack, 0x0C);
    r = RelocSection(MP(4), 0x28);
    MP(0x16C) = *(u8 **)(r + 0x10);
    MP(0x170) = *(u8 **)(r + 0x10) + 0x40;
    r = RelocSection(MP(4), 0x10);
    MP(0x120) = *(u8 **)(r + 0x10);
    r = RelocSection(MP(4), 0x18);
    MP(0x12C) = *(u8 **)(r + 0x10);
    r = RelocSection(MP(4), 0x60);
    MP(0x130) = *(u8 **)(r + 0x10);
    r = RelocSection(MP(4), 0x80);
    MP(0x11C) = *(u8 **)(r + 0x10);
    func_0026E7F0(m + 0x50, SUB(MP(4), 0x7C), m + 0x11C);
    func_0026EAE0(m + 0x50, 0x3C);

    r = RelocSection(MP(4), 0x14);
    MP(0x174) = *(u8 **)(r + 0x10);
    MP(0x178) = *(u8 **)(r + 0x10) + 0x40;
    MP(0x17C) = *(u8 **)(r + 0x10) + 0x80;
    r = RelocSection(MP(4), 0x78);
    MP(0x180) = *(u8 **)(r + 0x10);
    r = RelocSection(MP(4), 0x74);
    MP(0x184) = *(u8 **)(r + 0x10);
    MP(0x188) = *(u8 **)(r + 0x10) + 0x40;
    func_0026E7F0(m + 0xC8, SUB(MP(4), 0x20), m + 0x174);
    func_0026EAE0(m + 0xC8, 0x3C);
    func_0026E7F0(m + 0xF0, SUB(MP(4), 0x24), m + 0x174);
    func_0026EAE0(m + 0xF0, 0x3C);

    r = RelocSection(MP(4), 0x3C);
    MP(0x18C) = *(u8 **)(r + 0x10);
    MP(0x194) = *(u8 **)(r + 0x10) + 0x40;
    MP(0x190) = *(u8 **)(r + 0x10) + 0x80;
    MP(0x198) = *(u8 **)(r + 0x10) + 0xC0;
    func_0026E7F0(m + 0x28, SUB(MP(4), 0x40), m + 0x18C);
    func_0026EAE0(m + 0x28, 0x3C);

    r = RelocSection(MP(4), 0x50);
    MP(0x1A4) = *(u8 **)(r + 0x10);
    MP(0x19C) = *(u8 **)(r + 0x10) + 0x40;
    r = RelocSection(MP(4), 0x58);
    MP(0x1F4) = *(u8 **)(r + 0x10);
    MP(0x1EC) = *(u8 **)(r + 0x10) + 0x40;
    r = RelocSection(MP(4), 0x48);
    MP(0x1A0) = *(u8 **)(r + 0x10);
    MP(0x1F0) = *(u8 **)(r + 0x10);
    r = RelocSection(MP(4), 0x44);
    MP(0x1C8) = *(u8 **)(r + 0x10);
    MP(0x1CC) = *(u8 **)(r + 0x10) + 0x40;
    MP(0x1C4) = *(u8 **)(r + 0x10) + 0x80;
    MP(0x218) = *(u8 **)(r + 0x10);
    MP(0x21C) = *(u8 **)(r + 0x10) + 0x40;
    MP(0x214) = *(u8 **)(r + 0x10) + 0x80;
    func_0026E7F0(m + 0x78, SUB(MP(4), 0x4C), m + 0x19C);
    func_0026EAE0(m + 0x78, 0x3C);
    func_0026E7F0(m + 0xA0, SUB(MP(4), 0x54), m + 0x1EC);
    func_0026EAE0(m + 0xA0, 0x3C);

    MP(0x24) = SUB(MP(4), 0x70);
    func_0029BB88(SUB(MP(4), 0x6C), MP(0x24));
    MW(0x37E4) = -1;
    __builtin_memcpy(m + 0x3B0C, D_0042DF98, 0x2D);
    MW(0x3C10) = 0x18;
    func_0028A0B8(m + 0x37F4, D_0042DFC8, -1, -1, 1);

    /* two copies of the 0x4000-byte buffer at D_00387F2C */
    __builtin_memcpy(m + 0x3C14, D_00387F2C, 0x4000);
    __builtin_memcpy(m + 0x7C14, D_00387F2C, 0x4000);

    if (MW(0x37C8) != 1) {
        *(u8 **)(D_3876A4 + 0x4C8) = 0;
        *(u8 **)(D_3876A4 + 0x4CC) = 0;
    } else {
        u32 flags = *(u32 *)(D_3876A4 + 0x18);

        if ((flags & 0x1000) != 0) {
            McCard_GetInfoSync(1);
            if (GMC(0x30) != 2 || (u32)(GMC(0x2C) + 1) >= 2) {
                func_00288348();
                MW(0x37E8) = 0;
                *(u8 **)(D_3876A4 + 0x4C8) = m + 0x3C14;
                *(u8 **)(D_3876A4 + 0x4CC) = m + 0x7C14;
            } else {
                MW(0x37E8) = 1;
                func_0029C550(0);
                func_0029C820(1);
                func_0029C7E0(1);
                func_0029C810(1);
                func_00288348();
                MW(0x37EC) = 0x78;
            }
            *(u32 *)(D_3876A4 + 0x18) &= ~0x1000u;
        } else {
            if ((flags & 0x2000) != 0) {
                __builtin_memcpy(m + 0x901C, *(u8 **)(D_3876A4 + 0x4D0), 0xB28);
                __builtin_memcpy(m + 0x9B44, *(u8 **)(D_3876A4 + 0x4D4), 0x90C);
            }
            *(u8 **)(D_3876A4 + 0x4C8) = m + 0x3C14;
            *(u8 **)(D_3876A4 + 0x4CC) = m + 0x7C14;
            *(u32 *)(D_3876A4 + 0x18) &= ~0x1000u;
        }
    }

    /* relocate the 0x86 sub-resources of the second pack */
    MP(0x18) = func_002B24C8(SUB(MP(4), 4), 0, 0);
    for (i = 0; i < 0x86; i++) {
        RelocSection(MP(0x18), i * 4 + 4);
    }
    MP(0x360) = SUB(MP(4), 0x2C) + 4;
    MW(0x35C) = *(s32 *)SUB(MP(4), 0x2C);
    func_00248708(m + 0x368, m + 0x36C, m + 0x35C, m + 0x360);
    MW(0x35C) = MW(0x368);
    MP(0x360) = m + 0x36C;
    MP(0x364) = m + 0x1B7C;
    MW(0x37BC) = MW(0x35C) / 7;
    if (MW(0x35C) % 7 != 0) {
        MW(0x37BC) = MW(0x37BC) + 1;
    }
    MP(0x1C) = SUB(MP(4), 0x34);
    MP(0x20) = SUB(MP(4), 0x38);
    MP(0x37DC) = SUB(MP(4), 0x68) + 4;
    MP(0x37E0) = SUB(MP(4), 0x64) + 4;
    MP(8) = func_0028BAA8(0x17800);
    MP(0xC) = func_0028BAA8(0x17800);
    MP(0x10) = func_0028BAA8(0x20560);
    MP(0x14) = func_0028BAA8(0x20560);
    MW(0x37C4) = 1;
    MW(0x240) |= 2;

    /* 2 players x 5 slots: reset a slot whose saved id no longer matches */
    slots = D_3876A4;
    for (i = 0; i < 2; i++) {
        for (j = 0; j <= 4; j++) {
            k = i * 5 + j;
            if (func_0024ACB8(MW(0x360 + i * 4), *(s32 *)(slots + 0x390 + k * 4)) == 0) {
                *(s32 *)(slots + 0x390 + k * 4) = i;
                *(s32 *)(slots + 0x3B8 + k * 4) = 0;
                *(s32 *)(slots + 0x430 + k * 4) = 0;
                *(s32 *)(slots + 0x408 + k * 4) = 0;
            }
        }
    }

    /* split the slot ids into (col, row) and fill the per-player 7-wide tables */
    for (i = 0; i < 2; i++) {
        for (j = 0; j <= 4; j++) {
            s32 q;
            s32 r7;

            k = i * 5 + j;
            v = *(s32 *)(D_3876A4 + 0x390 + k * 4);
            MW(0x244 + k * 4) = v % 7;
            MW(0x26C + k * 4) = v / 7;
            MW(0x30C + k * 4) = *(s32 *)(D_3876A4 + 0x3B8 + k * 4);
            MW(0x334 + k * 4) = *(s32 *)(D_3876A4 + 0x430 + k * 4);
            MW(0x294 + k * 4) = *(s32 *)(D_3876A4 + 0x408 + k * 4);
            q = MW(0x26C + k * 4);
            r7 = MW(0x244 + k * 4);
            MW(0x338C + (q * 7 + i * 0x86 + r7) * 4) = MW(0x294 + k * 4);
        }
        MW(0x2BC + i * 4) = 0;
        MW(0x2C4 + i * 4) = 0;
        func_0040A710(i);
    }

    for (i = 0; i < 2; i++) {
        for (j = 4; j >= 0; j--) {
            u8 *table;
            u8 *entry;
            s32 q;
            s32 r7;
            s32 idx;

            k = i * 5 + j;
            q = MW(0x26C + k * 4);
            r7 = MW(0x244 + k * 4);
            table = MP(0x360 + i * 4);
            idx = MW(0x294 + k * 4);
            entry = table + (q * 7 + r7) * 44;
            *(s32 *)entry = *(s32 *)(entry + idx * 4 + 8);
        }
        func_0040A710(i);
    }
    return 0;
}
