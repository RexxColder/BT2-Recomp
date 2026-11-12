#include "common.h"

extern u8 *D_0042A57C __attribute__((section(".data")));
extern u8 *D_0042139C __attribute__((section(".data")));
extern u8 *D_3876A4 __attribute__((section(".data")));
extern u8 *D_003876A0 __attribute__((section(".data")));
extern u8 *D_387F2C __attribute__((section(".data")));
extern u32 D_004300B4 __attribute__((section(".data")));

void *func_0028BAA8(s32 a0);
void *memset(void *arg0, s32 arg1, u32 arg2);
u8 *func_002B24C8(u8 *a0, s32 a1, s32 a2);
void Res_RelocateOffsets(u8 *a0, u8 *a1, u8 *a2);
void func_0026E7F0(u8 *a0, u8 *a1, u8 *a2);
void func_0026EAE0(u8 *a0, s32 a1);
void func_0024B010(u8 *a0, u8 *a1, u8 *a2, u8 *a3, s32 a4);
s32 func_0024B210(u8 *a0);
void func_0024B248(u8 *a0, u8 *a1, u8 *a2, s32 a3);

/* sp0 = P + (word at P+k with low 2 bits cleared), then relocated in place */
#define RB(P, k) \
    do { \
        *(u8 **)(sp + 0x20) = (P) + (*(u32 *)((P) + (k)) & ~3u); \
        Res_RelocateOffsets(sp + 0x20, *(u8 **)(sp + 0x20), *(u8 **)(sp + 0x20)); \
    } while (0)
#define OFF(P, k) ((P) + (*(u32 *)((P) + (k)) & ~3u))

void func_003F8160(s32 a0) {
    u8 sp[0x28];
    u8 *obj;
    u8 *P;
    u8 *q;
    u8 *s1;
    s32 i;
    f32 f;
    f32 g;
    u32 w;

    *(u32 *)(sp + 0x20) = 0;
    obj = (u8 *)func_0028BAA8(0xF4);
    D_0042A57C = obj;
    memset(obj, 0, 0xF4);

    w = *(u32 *)(D_0042139C + a0 * 4);
    *(u8 **)(obj + 0x0) = D_0042139C + (w & ~3u);
    *(u8 **)(obj + 0x4) = func_002B24C8(*(u8 **)(obj + 0x0), 0, 0);

    P = *(u8 **)(D_0042A57C + 4);
    RB(P, 0x3C);
    *(u32 *)(D_0042A57C + 0x68) = *(u32 *)(sp + 0x20);

    P = *(u8 **)(D_0042A57C + 4);
    RB(P, 0x8C);
    *(u32 *)(D_0042A57C + 0x84) = *(u32 *)(*(u8 **)(sp + 0x20) + 0x10);

    P = *(u8 **)(D_0042A57C + 4);
    RB(P, 0x88);
    *(u32 *)(D_0042A57C + 0x8C) = *(u32 *)(*(u8 **)(sp + 0x20) + 0x10);

    P = *(u8 **)(D_0042A57C + 4);
    RB(P, 0x84);
    *(u32 *)(D_0042A57C + 0xA0) = *(u32 *)(*(u8 **)(sp + 0x20) + 0x10);
    *(u32 *)(D_0042A57C + 0x80) = *(u32 *)(*(u8 **)(sp + 0x20) + 0x10) + 0x40;

    P = *(u8 **)(D_0042A57C + 4);
    RB(P, 0x80);
    *(u32 *)(D_0042A57C + 0x74) = *(u32 *)(*(u8 **)(sp + 0x20) + 0x10);

    P = *(u8 **)(D_0042A57C + 4);
    RB(P, 0x94);
    *(u32 *)(D_0042A57C + 0x6C) = *(u32 *)(*(u8 **)(sp + 0x20) + 0x10);
    *(u32 *)(D_0042A57C + 0x70) = *(u32 *)(*(u8 **)(sp + 0x20) + 0x10) + 0x40;

    P = *(u8 **)(D_0042A57C + 4);
    RB(P, 0x1C);
    *(u32 *)(D_0042A57C + 0x78) = *(u32 *)(*(u8 **)(sp + 0x20) + 0x10);
    *(u32 *)(D_0042A57C + 0x7C) = *(u32 *)(*(u8 **)(sp + 0x20) + 0x10);

    P = *(u8 **)(D_0042A57C + 4);
    RB(P, 0x60);
    *(u32 *)(D_0042A57C + 0x88) = *(u32 *)(*(u8 **)(sp + 0x20) + 0x10);

    obj = D_0042A57C;
    s1 = obj + 0x40;
    P = *(u8 **)(obj + 4);
    func_0026E7F0(s1, OFF(P, 0x5C), obj + 0x6C);
    func_0026EAE0(s1, 0x3C);

    P = *(u8 **)(D_0042A57C + 4);
    RB(P, 0x44);
    *(u32 *)(D_0042A57C + 0xA8) = *(u32 *)(*(u8 **)(sp + 0x20) + 0x10);
    *(u32 *)(D_0042A57C + 0xA4) = *(u32 *)(*(u8 **)(sp + 0x20) + 0x10) + 0x40;

    P = *(u8 **)(D_0042A57C + 4);
    RB(P, 0x48);
    *(u32 *)(D_0042A57C + 0xAC) = *(u32 *)(*(u8 **)(sp + 0x20) + 0x10);

    obj = D_0042A57C;
    s1 = obj + 0x18;
    P = *(u8 **)(obj + 4);
    func_0026E7F0(s1, OFF(P, 0x40), obj + 0xA4);
    func_0026EAE0(s1, 0x3C);

    P = *(u8 **)(D_0042A57C + 4);
    *(u8 **)(D_0042A57C + 8) = func_002B24C8(OFF(P, 0x6C), 0, 0);

    for (i = 0; i < 0x86;) {
        u8 *t = *(u8 **)(D_0042A57C + 8);
        w = *(u32 *)(t + i * 4 + 4);
        i++;
        q = t + (w & ~3u);
        *(u8 **)(sp + 0x20) = q;
        Res_RelocateOffsets(sp + 0x20, q, q);
    }

    obj = D_0042A57C;
    P = *(u8 **)(obj + 4);
    *(u8 **)(obj + 0x10) = OFF(P, 0x64);
    obj = D_0042A57C; P = *(u8 **)(obj + 4);
    *(u8 **)(obj + 0x14) = OFF(P, 0x68);
    obj = D_0042A57C; P = *(u8 **)(obj + 4);
    *(u8 **)(obj + 0xE4) = OFF(P, 0x70) + 4;
    obj = D_0042A57C; P = *(u8 **)(obj + 4);
    *(u8 **)(obj + 0xE8) = OFF(P, 0x74) + 4;
    obj = D_0042A57C; P = *(u8 **)(obj + 4);
    *(u8 **)(obj + 0xEC) = OFF(P, 0xA4);
    obj = D_0042A57C; P = *(u8 **)(obj + 4);
    *(u8 **)(obj + 0xC) = OFF(P, 0x50);
    obj = D_0042A57C; P = *(u8 **)(obj + 4);
    *(u8 **)(obj + 0xF0) = OFF(P, 0x90);

    if (*(s32 *)(D_3876A4 + 0x48) >= 0) {
        obj = D_0042A57C;
        *(s32 *)(obj + 0xC4) = 2;
        q = *(u8 **)(obj + 8);
        q = q + (*(u32 *)(q + *(s32 *)(D_3876A4 + 0x44) * 4 + 4) & ~3u);
        *(u8 **)(sp + 0x20) = q;
        *(u32 *)(obj + 0x94) = *(u32 *)(q + 0x10);
        obj = D_0042A57C;
        q = *(u8 **)(obj + 8);
        q = q + (*(u32 *)(q + *(s32 *)(D_3876A4 + 0x48) * 4 + 4) & ~3u);
        *(u8 **)(sp + 0x20) = q;
        *(u32 *)(obj + 0x98) = *(u32 *)(q + 0x10);
    } else {
        obj = D_0042A57C;
        *(s32 *)(obj + 0xC4) = 1;
        q = *(u8 **)(obj + 8);
        q = q + (*(u32 *)(q + *(s32 *)(D_3876A4 + 0x44) * 4 + 4) & ~3u);
        *(u8 **)(sp + 0x20) = q;
        *(u32 *)(obj + 0x94) = *(u32 *)(q + 0x10);
    }

    f = (f32)*(s32 *)(D_3876A4 + 0x84);
    w = *(u32 *)(D_003876A0 + 0x484);
    if (w & 1) {
        g = *(f32 *)(*(u8 **)(D_0042A57C + 0xEC) + 0xC);
        f = f * g;
    } else if (w & 8) {
        g = *(f32 *)(*(u8 **)(D_0042A57C + 0xEC) + 8);
        f = f * g;
    }
    obj = D_0042A57C;
    g = *(f32 *)(*(u8 **)(obj + 0xEC) + *(s32 *)(D_3876A4 + 0x58) * 4 + 0x10);
    f = f * g;
    *(s32 *)(obj + 0xC0) = (s32)f;
    obj = D_0042A57C;
    *(u32 *)(obj + 0xB4) |= 0x10;

    if (*(s32 *)(D_0042A57C + 0xC4) > 0) {
        s32 o1 = 0x40, o2 = 0xD0, o4 = 0;
        for (i = 0; ; ) {
            u8 *st = D_3876A4;
            if ((*(u32 *)(st + 0x40) & (1u << i)) != 0) {
                u32 idx;
                obj = D_0042A57C;
                idx = *(u32 *)(st + o1 + 0xC);
                func_0024B010(*(u8 **)(obj + 0xE4), *(u8 **)(obj + 0xE8),
                              D_387F2C + idx * 34 + 0x1408, sp, 0x14);
                *(s32 *)(D_0042A57C + o2 + 4) = func_0024B210(sp);
                obj = D_0042A57C;
                idx = *(u32 *)(D_3876A4 + o1 + 0xC);
                func_0024B248(*(u8 **)(obj + 0xE4), D_387F2C + idx * 34 + 0x1408,
                              *(u8 **)(obj + 0xEC), *(s32 *)(obj + 0xC0));
                obj = D_0042A57C;
                idx = *(u32 *)(D_3876A4 + o1 + 0xC);
                func_0024B010(*(u8 **)(obj + 0xE4), *(u8 **)(obj + 0xE8),
                              D_387F2C + idx * 34 + 0x1408, sp, 0x14);
                *(s32 *)(D_0042A57C + o4 + 0xD8) = func_0024B210(sp);
                obj = D_0042A57C;
                if (*(s32 *)(obj + 4 + o2) < *(s32 *)(obj + 4 + o4 + 0xD4)) {
                    D_004300B4 |= (4u << i);
                }
            } else {
                *(s32 *)(D_0042A57C + o2 + 4) = 8;
            }
            i++;
            o1 += 4; o2 += 8; o4 += 8;
            if (!(i < *(s32 *)(D_0042A57C + 0xC4))) break;
        }
    }
}
