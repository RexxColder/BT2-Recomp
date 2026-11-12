#include "common.h"

extern u8 *D_00428F48 __attribute__((section(".data")));
extern u8 *D_004213A0 __attribute__((section(".data")));
extern s32 D_00428FC8[14] __attribute__((aligned(4)));
extern u8 *D_003876A4 __attribute__((section(".data")));

u8 *func_0028BAA8(s32 arg0);
u8 *func_002B24C8(u8 *arg0, s32 arg1, s32 arg2);
void Res_RelocateOffsets(u8 *arg0, u8 *arg1, u8 *arg2);
void func_0026E7F0(u8 *arg0, u8 *arg1, u8 *arg2);

#define G (D_00428F48)
#define GW(o) (*(s32 *)(G + (o)))
#define GP(o) (*(u8 **)(G + (o)))
#define SUB(base, o) ((base) + ((*(u32 *)((base) + (o)) >> 2) << 2))
#define RES(o) (*(s32 *)(GP(o) + 0x10))

void func_003EABC0(s32 arg0) {
    s32 tbl[14];
    s32 i, t0, t1, a1, cnt;
    u8 *v, *p, *a0;

    D_00428F48 = func_0028BAA8(0x1C4);
    memset(D_00428F48, 0, 0x1C4);
    GP(0) = SUB(D_004213A0, arg0 * 4);
    GP(4) = func_002B24C8(GP(0), 0, 0);
    for (i = 0; i < 14; i++) {
        memcpy(tbl, D_00428FC8, 0x38);
        v = SUB(GP(4), tbl[i] * 4);
        Res_RelocateOffsets(G + i * 4 + 0xF0, v, v);
    }
    GW(0x128) = RES(0x108);
    GW(0x12C) = RES(0x108) + 0x80;
    GW(0x130) = RES(0x108) + 0x40;
    GW(0x138) = RES(0xFC);
    GW(0x13C) = RES(0x100);
    GW(0x144) = RES(0x104) + 0x40;
    GW(0x148) = RES(0x104);
    GW(0x150) = RES(0xFC);
    GW(0x154) = RES(0x100);
    GW(0x15C) = RES(0x104) + 0x40;
    GW(0x160) = RES(0x104);
    GW(0x168) = RES(0xFC);
    GW(0x16C) = RES(0x120) + 0x40;
    GW(0x170) = RES(0x118);
    GW(0x174) = RES(0x118) + 0x40;
    GW(0x178) = RES(0x11C);
    GW(0x188) = RES(0x114);
    GW(0x18C) = RES(0x110);
    func_0026E7F0(G + 0x28, SUB(GP(4), 0x20), G + 0x128);
    func_0026E7F0(G + 0x50, SUB(GP(4), 0x10), G + 0x13C);
    func_0026E7F0(G + 0x78, SUB(GP(4), 0x18), G + 0x154);
    v = SUB(GP(4), 0x28);
    func_0026E7F0(G + 0xC8, v, G + 0x16C);
    func_0026E7F0(G + 0xA0, v, G + 0x16C);
    GP(8) = SUB(GP(4), 0x2C);
    GP(0xC) = SUB(GP(4), 0x4C);
    p = SUB(GP(4), 0x30);
    GW(0x14) = *(s32 *)p;
    GP(0x10) = p + 4;
    p = SUB(GP(4), 0x54);
    GW(0x1C) = *(s32 *)p;
    GP(0x18) = p + 4;
    t0 = *(s32 *)(D_003876A4 + 0x484) * 2 + *(s32 *)(D_003876A4 + 0x488);
    t1 = 0;
    i = 0;
    cnt = GW(0x14);
    if (cnt > 0 && t0 > 0) {
        for (;;) {
            a0 = GP(0x10) + i * 16;
            if (*a0 == 0) {
                t1++;
            }
            a1 = t1 < t0;
            if (!a1 && i < GW(0x14) - 1) {
                GP(0x10) = a0 + 0x10;
                break;
            }
            i++;
            if (!(i < GW(0x14))) {
                break;
            }
            if (!a1) {
                break;
            }
        }
    }
    if (i == GW(0x14)) {
        GW(0x10) = 0;
    }
    GW(0x1C0) = -1;
    GP(0x20) = func_0028BAA8(0xD800);
    GP(0x24) = func_0028BAA8(0x10560);
    GW(0x1B8) = 4;
}
