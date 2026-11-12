#include "common.h"

extern u8 *D_0042A574 __attribute__((section(".data")));
extern u8 *D_0042139C __attribute__((section(".data")));
extern u8 *D_003876A4 __attribute__((section(".data")));
extern s32 D_0042ABA8[16] __attribute__((aligned(4)));

u8 *func_0028BAA8(s32 arg0);
u8 *func_002B24C8(u8 *arg0, s32 arg1, s32 arg2);
void Res_RelocateOffsets(u8 *arg0, u8 *arg1, u8 *arg2);
void func_0026E7F0(u8 *arg0, u8 *arg1, u8 *arg2);
void func_0026EAE0(u8 *arg0, s32 arg1);
void func_0024BED8(u8 *arg0, s32 arg1);

#define G (D_0042A574)
#define GW(o) (*(s32 *)(G + (o)))
#define GP(o) (*(u8 **)(G + (o)))
#define SUB(base, o) ((base) + ((*(u32 *)((base) + (o)) >> 2) << 2))
#define RES(o) (*(s32 *)(GP(o) + 0x10))

void func_003F4318(s32 arg0) {
    s32 tbl[16];
    s32 i;
    u8 *v;
    u8 *h;

    D_0042A574 = func_0028BAA8(0x140);
    memset(D_0042A574, 0, 0x140);
    GP(0) = SUB(D_0042139C, arg0 * 4);
    GP(4) = func_002B24C8(GP(0), 0, 0);
    for (i = 0; i < 16; i++) {
        memcpy(tbl, D_0042ABA8, 0x40);
        v = SUB(GP(4), tbl[i] * 4);
        Res_RelocateOffsets(G + i * 4 + 0x6C, v, v);
    }
    GW(0x104) = RES(0x74) + 0x40;
    GW(0x108) = RES(0x74);
    GW(0x10C) = RES(0x78);
    GW(0x110) = RES(0x70);
    GW(0xAC) = RES(0x7C);
    GW(0xB0) = RES(0x7C);
    GW(0xB4) = RES(0x80);
    GW(0xB8) = RES(0x80) + 0x40;
    GW(0xBC) = RES(0xA4) + 0x40;
    GW(0xC0) = RES(0x94);
    GW(0xC4) = RES(0x8C);
    GW(0xC8) = RES(0xA4);
    GW(0xCC) = RES(0x90) + 0x40;
    GW(0xD0) = RES(0xA0);
    GW(0xD4) = RES(0x84);
    GW(0xD8) = RES(0x9C) + 0x40;
    GW(0xDC) = RES(0x9C);
    GW(0xE4) = RES(0xA4) + 0x140;
    GW(0xE8) = RES(0x98);
    GW(0xEC) = RES(0xA4) + 0x80;
    GW(0xF0) = RES(0x90);
    GW(0xF8) = RES(0xA4) + 0xC0;
    GW(0x100) = RES(0xA4) + 0x100;
    GW(0xE0) = RES(0x88);
    func_0026E7F0(G + 0x1C, SUB(GP(4), 0x34), G + 0x104);
    func_0026EAE0(G + 0x1C, 0x3C);
    func_0026E7F0(G + 0x44, SUB(GP(4), 4), G + 0xAC);
    func_0026EAE0(G + 0x44, 0x3C);
    GP(8) = SUB(GP(4), 0x48);
    GP(0xC) = SUB(GP(4), 0x50);
    GP(0x10) = SUB(GP(4), 0x4C);
    GP(0x14) = SUB(GP(4), 0x58);
    GP(0x18) = SUB(GP(4), 0x5C) + 4;
    GP(0x13C) = SUB(GP(4), 0x60) + 4;
    GP(0x12C) = SUB(GP(4), 0x1C);
    func_0024BED8(SUB(GP(4), 0x54), RES(0xA8));
    GW(0x118) = -1;
    h = D_003876A4;
    GW(0x138) = *(s16 *)(h + 0x78) * 10000 + *(s16 *)(h + 0x7A) * 100 + *(s16 *)(h + 0x7C);
    if (0x176D7 < GW(0x138)) {
        GW(0x138) = 0x176D7;
    }
}
