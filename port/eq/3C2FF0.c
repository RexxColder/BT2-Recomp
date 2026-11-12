#include "common.h"

extern u8 *D_004213A8 __attribute__((section(".data")));
extern u8 *D_00421CF4 __attribute__((section(".data")));
extern u8 D_00422C18[];
extern u8 D_00422C88[];
extern u8 D_00422CB8[];

u8 *func_0028BAA8(s32 arg0);
u8 *func_002B24C8(u8 *arg0, u8 *arg1, s32 *arg2);
void func_0026E7F0(s32 arg0, s32 arg1, s32 arg2);
void func_0026EAE0(s32 arg0, s32 arg1);
void func_0029BB88(s32 arg0, s32 arg1);
void func_0028A0B8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void Res_RelocateOffsets(void *arg0, s32 arg1, s32 arg2);
extern u8 *D_3876A4 __attribute__((section(".data")));

#define W(p, o) (*(s32 *)((p) + (o)))
#define P(p, o) (*(u8 **)((p) + (o)))
/* O[dst] = *(s32 *)(O[src] + 0x10) + add */
#define T(dst, src, add) (W(O, dst) = W(P(O, src), 0x10) + (add))
/* base + (base[off] & ~3) */
#define R(off) (base + (W(base, off) & ~3))

u8 *func_003C2FF0(s32 arg0) {
    u32 buf[27];
    u8 *O, *base, *sp0, *sp4, *x;
    s32 i;

    O = func_0028BAA8(0x68C);
    D_00421CF4 = O;
    __builtin_memset(O, 0, 0x68C);
    if (W(D_3876A4, 0x4B4) & 1) {
        W(D_00421CF4, 0x1FC) = W(D_00421CF4, 0x1FC) | 0x20;
    }
    base = D_004213A8;
    O = D_00421CF4;
    P(O, 0) = base + (W(base + arg0 * 4, 0) & ~3);
    O = D_00421CF4;
    P(O, 4) = func_002B24C8(P(O, 0), 0, 0);
    for (i = 0; i < 27; i++) {
        __builtin_memcpy(buf, D_00422C18, 0x6C);
        O = D_00421CF4;
        base = P(O, 4);
        x = base + (W(base + buf[i] * 4, 0) & ~3);
        Res_RelocateOffsets(O + 0xB0 + i * 4, (s32)x, (s32)x);
    }
    O = D_00421CF4;
    T(0x11C, 0xE0, 0x0);
    T(0x120, 0xC8, 0x0);
    T(0x124, 0xFC, 0x0);
    T(0x128, 0xCC, 0x0);
    T(0x12C, 0xD8, 0x0);
    T(0x130, 0xDC, 0x0);
    T(0x134, 0xD8, 0x0);
    T(0x138, 0xD0, 0x0);
    T(0x13C, 0xD4, 0x0);
    if (W(O, 0x1FC) & 0x20) {
        T(0x140, 0x104, 0);
        T(0x144, 0x104, 0);
        T(0x148, 0x104, 0);
    } else {
        T(0x14C, 0x100, 0);
        T(0x150, 0x100, 0);
        T(0x154, 0x100, 0);
    }
    T(0x158, 0x108, 0x40);
    T(0x15C, 0xB4, 0x0);
    T(0x160, 0x108, 0x0);
    T(0x164, 0xC4, 0x0);
    T(0x168, 0xE4, 0x0);
    T(0x16C, 0xB8, 0x40);
    T(0x170, 0xB8, 0x0);
    T(0x174, 0xBC, 0x0);
    T(0x180, 0xC0, 0x0);
    T(0x188, 0xF8, 0x0);
    T(0x194, 0xF0, 0x0);
    T(0x198, 0xF0, 0x40);
    T(0x19C, 0xE8, 0x0);
    T(0x1A0, 0xEC, 0x0);
    T(0x1AC, 0xB0, 0x40);
    T(0x1A8, 0xB0, 0x0);
    T(0x1A4, 0xB0, 0x80);
    T(0x1B0, 0x110, 0x0);
    T(0x1B4, 0x114, 0x0);
    T(0x1B8, 0x118, 0x0);
    base = P(O, 4);
    func_0026E7F0((s32)(O + 0x38), (s32)R(0x6C), (s32)(O + 0x1A4));
    func_0026EAE0((s32)(O + 0x38), 0x3C);
    base = P(O, 4);
    func_0026E7F0((s32)(O + 0x60), (s32)R(4), (s32)(O + 0x11C));
    func_0026EAE0((s32)(O + 0x60), 0x3C);
    base = P(O, 4);
    func_0026E7F0((s32)(O + 0x88), (s32)R(0x84), (s32)(O + 0x1B0));
    base = P(O, 4);
    P(O, 8) = R(0x60);
    P(O, 0xC) = R(0x64);
    P(O, 0x10) = R(0x58);
    P(O, 0x14) = R(0x5C);
    P(O, 0x18) = R(0x7C);
    P(O, 0x1C) = R(0x94) + 4;
    sp0 = R(0xA4);
    sp4 = R(0xA0);
    W(O, 0x20) = W(sp0, 0);
    W(O, 0x28) = W(sp4, 0);
    P(O, 0x24) = sp0 + 4;
    P(O, 0x2C) = sp4 + 4;
    P(O, 0x688) = R(0xA8) + 4;
    W(O, 0x684) = W(R(0xA8), 0);
    func_0029BB88((s32)R(0x80), (s32)P(O, 0x18));
    W(O, 0x214) = -1;
    P(O, 0x220) = R(0x9C);
    W(O, 0x22C) = 0xD74E;
    __builtin_memcpy(O + 0x538, D_00422C88, 0x2D);
    W(O, 0x63C) = 0x18;
    func_0028A0B8((s32)(O + 0x220), (s32)D_00422CB8, -1, -1, 1);
    P(O, 0x30) = func_0028BAA8(0xB000);
    P(O, 0x34) = func_0028BAA8(0x10560);
    O = D_00421CF4;
    W(O, 0x678) = 4;
    return O;
}
