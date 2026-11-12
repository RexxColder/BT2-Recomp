#include "common.h"

extern u8 *D_00421C94 __attribute__((section(".data")));
extern u8 *D_004213A8 __attribute__((section(".data")));
extern s32 D_00421D40[12];
extern u8 D_00421D70[];
extern u8 D_00421DA0[];
extern u8 *D_003876A4 __attribute__((section(".data")));

u8 *func_0028BAA8(s32 arg0);
u8 *func_002B24C8(u8 *arg0, s32 arg1, s32 arg2);
void Res_RelocateOffsets(u8 *arg0, u8 *arg1, u8 *arg2);
void func_0026E7F0(u8 *arg0, u8 *arg1, u8 *arg2);
void func_0026EAE0(u8 *arg0, s32 arg1);
void func_0029BB88(u8 *arg0, u8 *arg1);
void func_0028A0B8(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3, s32 arg4);

#define G (D_00421C94)
#define GW(o) (*(s32 *)(G + (o)))
#define GP(o) (*(u8 **)(G + (o)))
#define SUB(base, o) ((base) + ((*(u32 *)((base) + (o)) >> 2) << 2))

s32 func_003BE778(s32 arg0) {
    s32 tbl[12];
    s32 i;
    u8 *base;
    u8 *v;

    D_00421C94 = func_0028BAA8(0x550);
    memset(D_00421C94, 0, 0x550);
    if (*(u32 *)(D_003876A4 + 0x4B4) & 1) {
        GW(0x52C) = GW(0x52C) | 4;
    }
    base = D_004213A8;
    GP(0) = SUB(base, arg0 * 4);
    GP(4) = func_002B24C8(GP(0), 0, 0);
    for (i = 0; i < 12; i++) {
        memcpy(tbl, D_00421D40, 0x30);
        v = SUB(GP(4), tbl[i] * 4);
        Res_RelocateOffsets(G + i * 4 + 0x498, v, v);
    }
    GW(0x4EC) = *(s32 *)(GP(0x4B4) + 0x10);
    if (GW(0x52C) & 4) {
        GW(0x4C8) = *(s32 *)(GP(0x4BC) + 0x10);
        GW(0x4CC) = *(s32 *)(GP(0x4BC) + 0x10);
        GW(0x4D0) = *(s32 *)(GP(0x4BC) + 0x10);
    } else {
        GW(0x4D4) = *(s32 *)(GP(0x4B8) + 0x10);
        GW(0x4D8) = *(s32 *)(GP(0x4B8) + 0x10);
        GW(0x4DC) = *(s32 *)(GP(0x4B8) + 0x10);
    }
    GW(0x4E4) = *(s32 *)(GP(0x4C0) + 0x10) + 0x40;
    GW(0x4E8) = *(s32 *)(GP(0x49C) + 0x10);
    GW(0x4E0) = *(s32 *)(GP(0x4C0) + 0x10);
    GW(0x4F0) = *(s32 *)(GP(0x4B0) + 0x10);
    GW(0x508) = *(s32 *)(GP(0x4A8) + 0x10);
    GW(0x50C) = *(s32 *)(GP(0x4A8) + 0x10) + 0x40;
    GW(0x504) = *(s32 *)(GP(0x4A0) + 0x10);
    GW(0x510) = *(s32 *)(GP(0x4A4) + 0x10);
    GW(0x51C) = *(s32 *)(GP(0x498) + 0x10) + 0x40;
    GW(0x518) = *(s32 *)(GP(0x498) + 0x10);
    GW(0x514) = *(s32 *)(GP(0x498) + 0x10) + 0x80;
    func_0026E7F0(G + 0x448, SUB(GP(4), 0x14), G + 0x514);
    func_0026EAE0(G + 0x448, 0x3C);
    func_0026E7F0(G + 0x470, SUB(GP(4), 4), G + 0x4C8);
    func_0026EAE0(G + 0x470, 0x3C);
    GP(0x10) = SUB(GP(4), 0x5C);
    GP(0x14) = SUB(GP(4), 0x60);
    GP(8) = SUB(GP(4), 0x24);
    GP(0xC) = SUB(GP(4), 0xC);
    GP(0x18) = SUB(GP(4), 0x44);
    func_0029BB88(SUB(GP(4), 0x48), GP(0x18));
    GP(0x28) = SUB(GP(4), 0x64);
    GW(0x34) = 0xD74E;
    memcpy(G + 0x340, D_00421D70, 0x2D);
    GW(0x444) = 0x18;
    func_0028A0B8(G + 0x28, D_00421DA0, -1, -1, 1);
    GW(0x534) = -1;
    return -1;
}
