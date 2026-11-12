#include "common.h"

extern u8 *D_004213B0 __attribute__((section(".data")));
extern u8 *D_0042138C __attribute__((section(".data")));
extern u8 *D_3876A4 __attribute__((section(".data")));
extern u8 D_00421A50[] __attribute__((section(".data")));

void *func_28BAA8(s32 a0);
void *memset(void *arg0, s32 arg1, u32 arg2);
void *memcpy(void *dst, const void *src, u32 n);
u8 *func_2B24C8(u8 *a0, u8 *a1, s32 a2);
s64 GetTimerSystemTime(void);
void func_325370(s64 arg0);
void Res_RelocateOffsets(u8 *a0, u8 *a1, u8 *a2);
void func_26E7F0(u8 *a0, u8 *a1, u8 *a2);
void func_26EAE0(u8 *a0, s32 a1);
extern u8 D_00421A80[] __attribute__((section(".data")));
void func_28A0B8(u8 *a0, u8 *a1, s32 a2, s32 a3, s32 t0);
void func_29BB88(u8 *arg0, u8 *arg1);

/* the word at P+k is an offset (low 2 bits cleared); sp0 = P + offset,
   then relocated in place through &sp0 */
#define RELOC_BLOCK(sp0, P, k) \
    do { \
        (sp0) = (P) + (*(u32 *)((P) + (k)) & ~3u); \
        Res_RelocateOffsets((u8 *)&(sp0), (sp0), (sp0)); \
    } while (0)

void func_003B84B8(s32 a0) {
    u8 *obj;
    u8 *P;
    u8 *sp0;
    u32 w;
    s32 t;

    obj = (u8 *)func_28BAA8(0x45C8);
    D_004213B0 = obj;
    memset(obj, 0, 0x45C8);

    w = *(u32 *)(D_0042138C + a0 * 4);
    *(u8 **)(obj + 0x0) = D_0042138C + (w & ~3u);
    *(u8 **)(obj + 0x4) = func_2B24C8(*(u8 **)(obj + 0x0), 0, 0);
    t = (s32)GetTimerSystemTime();
    func_325370((s64)t);

    P = *(u8 **)(obj + 0x4);
    RELOC_BLOCK(sp0, P, 0x14);
    *(u8 **)(obj + 0x60) = sp0;

    RELOC_BLOCK(sp0, P, 0x48);
    *(s32 *)(obj + 0x64) = *(s32 *)(sp0 + 0x10);
    *(s32 *)(obj + 0x68) = *(s32 *)(sp0 + 0x10) + 0x40;
    *(s32 *)(obj + 0x6C) = *(s32 *)(sp0 + 0x10) + 0x80;

    RELOC_BLOCK(sp0, P, 0x44);
    *(s32 *)(obj + 0x70) = *(s32 *)(sp0 + 0x10);

    RELOC_BLOCK(sp0, P, 0x10);
    *(s32 *)(obj + 0x74) = *(s32 *)(sp0 + 0x10);
    *(s32 *)(obj + 0x78) = *(s32 *)(sp0 + 0x10) + 0x40;

    RELOC_BLOCK(sp0, P, 0x28);
    *(s32 *)(obj + 0x7C) = *(s32 *)(sp0 + 0x10);

    RELOC_BLOCK(sp0, P, 0x50);
    *(s32 *)(obj + 0x80) = *(s32 *)(sp0 + 0x10);

    RELOC_BLOCK(sp0, P, 0x3C);
    *(s32 *)(obj + 0x84) = *(s32 *)(sp0 + 0x10);

    RELOC_BLOCK(sp0, P, 0x4C);
    *(s32 *)(obj + 0x88) = *(s32 *)(sp0 + 0x10);

    RELOC_BLOCK(sp0, P, 0x2C);
    *(s32 *)(obj + 0x8C) = *(s32 *)(sp0 + 0x10);

    RELOC_BLOCK(sp0, P, 0x18);
    *(s32 *)(obj + 0x90) = *(s32 *)(sp0 + 0x10);

    RELOC_BLOCK(sp0, P, 0x24);
    *(s32 *)(obj + 0x94) = *(s32 *)(sp0 + 0x10);

    RELOC_BLOCK(sp0, P, 0x1C);
    *(s32 *)(obj + 0x98) = *(s32 *)(sp0 + 0x10);

    RELOC_BLOCK(sp0, P, 0x2C);
    *(s32 *)(obj + 0x8C) = *(s32 *)(sp0 + 0x10);

    RELOC_BLOCK(sp0, P, 0x6C);
    *(s32 *)(obj + 0xA0) = *(s32 *)(sp0 + 0x10);
    *(s32 *)(obj + 0x9C) = *(s32 *)(sp0 + 0x10) + 0x40;
    *(s32 *)(obj + 0xA4) = *(s32 *)(sp0 + 0x10) + 0x80;

    RELOC_BLOCK(sp0, P, 0x68);
    *(s32 *)(obj + 0xAC) = *(s32 *)(sp0 + 0x10);
    *(s32 *)(obj + 0xA8) = *(s32 *)(sp0 + 0x10) + 0x40;
    *(s32 *)(obj + 0xB0) = *(s32 *)(sp0 + 0x10) + 0x80;

    func_26E7F0(obj + 0x10, P + (*(u32 *)(P + 0x8) & ~3u), obj + 0x64);
    func_26EAE0(obj + 0x10, 0x3C);

    RELOC_BLOCK(sp0, P, 0x38);
    *(s32 *)(obj + 0xBC) = *(s32 *)(sp0 + 0x10);

    RELOC_BLOCK(sp0, P, 0x40);
    *(s32 *)(obj + 0xB8) = *(s32 *)(sp0 + 0x10);

    RELOC_BLOCK(sp0, P, 0xC);
    *(s32 *)(obj + 0xC0) = *(s32 *)(sp0 + 0x10);

    RELOC_BLOCK(sp0, P, 0x34);
    *(s32 *)(obj + 0xC4) = *(s32 *)(sp0 + 0x10);

    func_26E7F0(obj + 0x38, P + (*(u32 *)(P + 0x30) & ~3u), obj + 0xB4);
    func_26EAE0(obj + 0x38, 0x3C);

    *(u8 **)(obj + 0x45C0) = P + (*(u32 *)(P + 0x84) & ~3u) + 4;
    *(s32 *)(obj + 0x45C4) = *(s32 *)(P + (*(u32 *)(P + 0x84) & ~3u));
    *(u8 **)(obj + 0x8) = P + (*(u32 *)(P + 0x64) & ~3u);

    func_29BB88(P + (*(u32 *)(P + 0x60) & ~3u), *(u8 **)(obj + 0x8));

    *(u8 **)(obj + 0xC) = P + (*(u32 *)(P + 0x5C) & ~3u);

    *(u8 **)(obj + 0x40F8) = P + (*(u32 *)(P + 0x78) & ~3u);

    *(s32 *)(obj + 0x4104) = 0xD74E;

    memcpy(obj + 0x4410, D_00421A50, 0x2D);

    *(s32 *)(obj + 0x4514) = 0x18;

    func_28A0B8(obj + 0x40F8, D_00421A80, -1, -1, 1);

    RELOC_BLOCK(sp0, P, 0x20);
    *(u8 **)(obj + 0xC8) = sp0;

    *(u8 **)(obj + 0xE4) = P + (*(u32 *)(P + 0x4) & ~3u);

    if ((*(s32 *)(D_3876A4 + 0x18) & 0x8) != 0 || (*(s32 *)(D_3876A4 + 0x18) & 0x800) != 0) {
        *(s32 *)(obj + 0xD4) = 3;
        *(s32 *)(obj + 0xD0) = 2;
    } else {
        *(s32 *)(obj + 0xD4) = 2;
    }
}
