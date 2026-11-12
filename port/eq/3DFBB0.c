#include "common.h"

extern u8 *D_004213A4 __attribute__((section(".data")));
extern u8 *D_00427334 __attribute__((section(".data")));
extern u8 *D_003876A4;

s32 func_0028BAA8(s32 arg0);
u8 *func_002B24C8(u8 *a0, u8 *a1, s32 a2);
void Res_RelocateOffsets(s32 arg0, s32 arg1, s32 arg2);
void func_0026E7F0(u8 *a0, u8 *a1, u8 *a2);
void func_0026EAE0(u8 *a0, s32 a1);
void func_0024BED8(u8 *a0, s32 a1);

/* 0x003DFBB0 (arg0 = index): allocates the 0xC0-byte block at D_00427334, sets its pointers
   from the table at D_004213A4 and relocates sub-objects of P = block->4 (each relocation
   writes the relocated pointer into sp[0]). Returns D_003876A4->0x4C4. */
s32 func_003DFBB0(s32 arg0) {
    s32 sp[4];
    u8 *obj;
    u8 *P;
    u8 *X;
    s32 r;
    s32 i;

    D_00427334 = (u8 *)func_0028BAA8(0xC0);
    obj = D_00427334;
    for (i = 0; i < 0xC0; i++) {
        obj[i] = 0;
    }
    *(u8 **)(obj + 0x0) = D_004213A4 + (*(s32 *)(D_004213A4 + (arg0 << 2)) & ~3);
    *(u8 **)(obj + 0x4) = func_002B24C8(*(u8 **)(obj + 0x0), 0, 0);

    P = *(u8 **)(obj + 0x4);
    X = P + (*(s32 *)(P + 0x8) & ~3);
    sp[0] = (s32)X;
    Res_RelocateOffsets((s32)sp, (s32)X, (s32)X);
    *(s32 *)(obj + 0x60) = sp[0];

    P = *(u8 **)(obj + 0x4);
    X = P + (*(s32 *)(P + 0x2C) & ~3);
    sp[0] = (s32)X;
    Res_RelocateOffsets((s32)sp, (s32)X, (s32)X);
    *(s32 *)(obj + 0x78) = *(s32 *)((u8 *)sp[0] + 0x10);

    P = *(u8 **)(obj + 0x4);
    X = P + (*(s32 *)(P + 0x1C) & ~3);
    sp[0] = (s32)X;
    Res_RelocateOffsets((s32)sp, (s32)X, (s32)X);
    *(s32 *)(obj + 0x88) = *(s32 *)((u8 *)sp[0] + 0x10);

    P = *(u8 **)(obj + 0x4);
    X = P + (*(s32 *)(P + 0x20) & ~3);
    sp[0] = (s32)X;
    Res_RelocateOffsets((s32)sp, (s32)X, (s32)X);
    *(s32 *)(obj + 0x80) = *(s32 *)((u8 *)sp[0] + 0x10);

    P = *(u8 **)(obj + 0x4);
    X = P + (*(s32 *)(P + 0xC) & ~3);
    sp[0] = (s32)X;
    Res_RelocateOffsets((s32)sp, (s32)X, (s32)X);
    *(s32 *)(obj + 0x90) = *(s32 *)((u8 *)sp[0] + 0x10);

    P = *(u8 **)(obj + 0x4);
    X = P + (*(s32 *)(P + 0x24) & ~3);
    sp[0] = (s32)X;
    Res_RelocateOffsets((s32)sp, (s32)X, (s32)X);
    *(s32 *)(obj + 0x84) = *(s32 *)((u8 *)sp[0] + 0x10);
    *(s32 *)(obj + 0x8C) = *(s32 *)((u8 *)sp[0] + 0x10) + 0x40;

    P = *(u8 **)(obj + 0x4);
    X = P + (*(s32 *)(P + 0x28) & ~3);
    sp[0] = (s32)X;
    Res_RelocateOffsets((s32)sp, (s32)X, (s32)X);
    *(s32 *)(obj + 0x7C) = *(s32 *)((u8 *)sp[0] + 0x10);

    P = *(u8 **)(obj + 0x4);
    X = P + (*(s32 *)(P + 0x34) & ~3);
    sp[0] = (s32)X;
    Res_RelocateOffsets((s32)sp, (s32)X, (s32)X);
    func_0024BED8(P + (*(s32 *)(P + 0x44) & ~3), *(s32 *)((u8 *)sp[0] + 0x10));

    P = *(u8 **)(obj + 0x4);
    X = P + (*(s32 *)(P + 0x30) & ~3);
    sp[0] = (s32)X;
    Res_RelocateOffsets((s32)sp, (s32)X, (s32)X);
    *(s32 *)(obj + 0x74) = *(s32 *)((u8 *)sp[0] + 0x10);
    *(s32 *)(obj + 0x64) = *(s32 *)((u8 *)sp[0] + 0x10) + 0x40;

    P = *(u8 **)(obj + 0x4);
    X = P + (*(s32 *)(P + 0x18) & ~3);
    sp[0] = (s32)X;
    Res_RelocateOffsets((s32)sp, (s32)X, (s32)X);
    *(s32 *)(obj + 0x68) = *(s32 *)((u8 *)sp[0] + 0x10);
    *(s32 *)(obj + 0x6C) = *(s32 *)((u8 *)sp[0] + 0x10);
    *(s32 *)(obj + 0x70) = *(s32 *)((u8 *)sp[0] + 0x10);

    P = *(u8 **)(obj + 0x4);
    func_0026E7F0(obj + 0x38, P + (*(s32 *)(P + 0x4) & ~3), obj + 0x64);
    func_0026EAE0(obj + 0x38, 0x3C);

    P = *(u8 **)(obj + 0x4);
    X = P + (*(s32 *)(P + 0x10) & ~3);
    sp[0] = (s32)X;
    Res_RelocateOffsets((s32)sp, (s32)X, (s32)X);
    *(s32 *)(obj + 0x94) = *(s32 *)((u8 *)sp[0] + 0x10);

    P = *(u8 **)(obj + 0x4);
    func_0026E7F0(obj + 0x10, P + (*(s32 *)(P + 0x14) & ~3), obj + 0x94);
    func_0026EAE0(obj + 0x10, 0x3C);

    P = *(u8 **)(obj + 0x4);
    *(u8 **)(obj + 0xC) = P + (*(s32 *)(P + 0x40) & ~3);
    *(u8 **)(obj + 0x8) = P + (*(s32 *)(P + 0x3C) & ~3);
    *(s32 *)(obj + 0xA0) = 0;

    r = *(s32 *)(D_003876A4 + 0x4C4);
    *(s32 *)(obj + 0x9C) = r;
    return r;
}
