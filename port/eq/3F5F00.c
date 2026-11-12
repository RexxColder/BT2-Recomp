#include "common.h"

extern u8 *D_0042A578 __attribute__((section(".data")));
extern u8 *D_0042139C __attribute__((section(".data")));
extern u8 *D_3876A4 __attribute__((section(".data")));

void *func_0028BAA8(s32 a0);
void *memset(void *arg0, s32 arg1, u32 arg2);
u8 *func_002B24C8(u8 *a0, s32 a1, s32 a2);
void Res_RelocateOffsets(u8 *a0, u8 *a1, u8 *a2);
void func_0026E7F0(u8 *a0, u8 *a1, u8 *a2);
void func_0026EAE0(u8 *a0, s32 a1);
s32 func_0024B598(u8 *a0, s32 a1);
void func_003F5750(void);

/* sp0 = P + (word at P+k with low 2 bits cleared), relocated in place */
#define RB(k) \
    do { \
        u8 *P_ = *(u8 **)(D_0042A578 + 4); \
        *(u8 **)sp = P_ + (*(u32 *)(P_ + (k)) & ~3u); \
        Res_RelocateOffsets(sp, *(u8 **)sp, *(u8 **)sp); \
    } while (0)
#define OFF(k) ({ u8 *P_ = *(u8 **)(D_0042A578 + 4); P_ + (*(u32 *)(P_ + (k)) & ~3u); })
#define W(o) (*(u32 *)(D_0042A578 + (o)))
#define SP0 (*(u8 **)sp)

void func_003F5F00(s32 a0) {
    u8 sp[0x10];
    u8 *obj;
    u8 *a;
    s32 i;
    u32 w;

    *(u32 *)sp = 0;
    obj = (u8 *)func_0028BAA8(0x1D4);
    D_0042A578 = obj;
    memset(obj, 0, 0x1D4);

    w = *(u32 *)(D_0042139C + a0 * 4);
    *(u8 **)(obj + 0) = D_0042139C + (w & ~3u);
    *(u8 **)(obj + 4) = func_002B24C8(*(u8 **)(obj + 0), 0, 0);

    RB(0x14); W(0xB0) = *(u32 *)sp;
    RB(0x58); W(0xE4) = *(u32 *)(SP0 + 0x10);
    RB(0x30); W(0xBC) = *(u32 *)(SP0 + 0x10);
    RB(0x30); W(0xBC) = *(u32 *)(SP0 + 0x10);
    RB(0x38); W(0xE0) = *(u32 *)(SP0 + 0x10);
    RB(0x0C); W(0xCC) = *(u32 *)(SP0 + 0x10);
    RB(0x10); W(0xF0) = *(u32 *)(SP0 + 0x10);
    RB(0x34); W(0xD4) = *(u32 *)(SP0 + 0x10);
    RB(0x3C); W(0xF4) = *(u32 *)(SP0 + 0x10);
    RB(0x2C); W(0xB4) = *(u32 *)(SP0 + 0x10);
    W(0xD8) = *(u32 *)(SP0 + 0x10) + 0x40;
    RB(0x28); W(0xC8) = *(u32 *)(SP0 + 0x10);
    RB(0x18); W(0xDC) = *(u32 *)(SP0 + 0x10);
    RB(0x44); W(0xC4) = *(u32 *)(SP0 + 0x10);
    RB(0x4C); W(0xB8) = *(u32 *)(SP0 + 0x10);
    RB(0x48); W(0xC0) = *(u32 *)(SP0 + 0x10);

    obj = D_0042A578;
    func_0026E7F0(obj + 0x88, OFF(0x08), obj + 0xB4);
    func_0026EAE0(obj + 0x88, 0x3C);

    RB(0x1C); W(0xF8) = *(u32 *)(SP0 + 0x10);

    obj = D_0042A578;
    func_0026E7F0(obj + 0x60, OFF(0x24), obj + 0xF8);
    func_0026EAE0(obj + 0x60, 0x3C);
    obj = D_0042A578;
    func_0026E7F0(obj + 0x10, OFF(0x20), obj + 0xF8);
    func_0026EAE0(obj + 0x10, 0x3C);

    RB(0x6C); W(0xFC) = *(u32 *)(SP0 + 0x10);
    RB(0x68); W(0x100) = *(u32 *)(SP0 + 0x10);
    RB(0x60); W(0x134) = *(u32 *)(SP0 + 0x10);

    obj = D_0042A578;
    func_0026E7F0(obj + 0x38, OFF(0x64), obj + 0xFC);
    func_0026EAE0(obj + 0x38, 0x3C);

    *(u8 **)(D_0042A578 + 8) = func_002B24C8(OFF(0x70), 0, 0);

    for (i = 0; i < 0x86;) {
        u8 *t = *(u8 **)(D_0042A578 + 8);
        w = *(u32 *)(t + i * 4 + 4);
        i++;
        a = t + (w & ~3u);
        SP0 = a;
        Res_RelocateOffsets(sp, a, a);
    }

    W(0x0C) = (u32)OFF(0x54);
    W(0x1CC) = (u32)OFF(0x40);
    W(0x1D0) = (u32)OFF(0x50);
    W(0x1C4) = (u32)OFF(0x04) + 4;
    W(0x1C8) = (u32)OFF(0x5C) + 4;
    W(0x144) = 1;

    for (i = 0; i < 0xF; i++) {
        if (func_0024B598(*(u8 **)(D_0042A578 + 0x1C4), i)) {
            if (*(s32 *)(D_3876A4 + 0x64) == i) {
                W(0x140) = W(0x188);
            }
            obj = D_0042A578;
            w = *(u32 *)(obj + 0x188);
            *(s32 *)(obj + w * 4 + 0x14C) = i;
            *(u32 *)(obj + 0x188) = w + 1;
        }
    }

    obj = D_0042A578;
    W(0x19C) = *(u32 *)(*(u8 **)(obj + 0x1C4) + *(s32 *)(obj + *(s32 *)(obj + 0x140) * 4 + 0x14C) * 56 + 8) - 1;
    W(0x1A0) = W(0x19C) - 1;
    obj = D_0042A578;
    W(0x1A4) = *(u32 *)(*(u8 **)(obj + 0x1C4) + *(s32 *)(obj + *(s32 *)(obj + 0x140) * 4 + 0x14C) * 56 + 8) + 1;
    obj = D_0042A578;
    W(0x1A8) = *(u32 *)(*(u8 **)(obj + 0x1C4) + *(s32 *)(obj + *(s32 *)(obj + 0x140) * 4 + 0x14C) * 56 + 8) + 2;
    func_003F5750();
}
