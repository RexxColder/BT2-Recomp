#include "common.h"

void func_0012D868(u8 *arg0, u8 *arg1, u8 *arg2, s32 arg3, u8 *arg4, u8 *arg5);
s32 func_0012C250(u8 *arg0, u8 *arg1, s32 arg2, u8 arg3, u8 arg4, u8 arg5, s64 arg6, s32 arg7);
s32 func_0012C9E8(u8 *arg0, u8 *arg1, s64 *arg2, s32 arg3, s32 arg4);

#define F(off) (*(f32 *)(sp + (off)))
#define Q(off) (*(u64 *)(sp + (off)))

/* Builds a quad render packet: copies the 0x40-byte arg1 and the three 16-byte vectors arg2/arg3/arg4
   into a local frame, transforms with func_0012D868 (matrix arg0), derives a depth key from the
   transform output and emits the quad twice (before and after the transform results are reused) through
   func_0012C250 (arg6 == 0) or func_0012C9E8 (arg6 != 0). */
void func_001866A8(f32 *arg0, u8 *arg1, u8 *arg2, u8 *arg3, u8 *arg4, s32 arg5, u8 arg6, s64 *arg7) {
    u8 sp[0x400];   /* el original reserva 0x360 (addiu sp,-0x360; regs desde ~0x320): el buffer en sp+0x170 llega a 0x320 */
    s32 key;
    s32 i;

    Q(0x00) = *(u64 *)(arg1 + 0x00);
    Q(0x08) = *(u64 *)(arg1 + 0x08);
    Q(0x10) = *(u64 *)(arg1 + 0x10);
    Q(0x18) = *(u64 *)(arg1 + 0x18);
    Q(0x20) = *(u64 *)(arg1 + 0x20);
    Q(0x28) = *(u64 *)(arg1 + 0x28);
    Q(0x30) = *(u64 *)(arg1 + 0x30);
    Q(0x38) = *(u64 *)(arg1 + 0x38);
    Q(0x40) = *(u64 *)(arg2 + 0);
    Q(0x48) = *(u64 *)(arg2 + 8);
    Q(0x50) = *(u64 *)(arg3 + 0);
    Q(0x58) = *(u64 *)(arg3 + 8);
    Q(0x60) = *(u64 *)(arg4 + 0);
    Q(0x68) = *(u64 *)(arg4 + 8);

    F(0xF0) = F(0x40);
    F(0xF4) = F(0x44);
    F(0xF8) = 1.0f;
    F(0xFC) = 1.0f;
    F(0x100) = F(0x48);
    F(0x104) = F(0x4C);
    F(0x110) = F(0x50);
    F(0x114) = F(0x54);
    F(0x120) = F(0x58);
    F(0x124) = F(0x5C);
    F(0x12C) = 1.0f;

    for (i = 0; i < 16; i++) {
        F(0x70 + 4 * i) = arg0[i];
    }
    F(0x108) = 1.0f;
    F(0x10C) = 1.0f;
    F(0x118) = 1.0f;
    F(0x11C) = 1.0f;
    F(0x128) = 1.0f;

    func_0012D868(sp + 0xB0, sp, sp + 0x70, 4, sp + 0x130, sp + 0xF0);

    for (i = 0; i < 12; i++) {
        F(0x170 + 4 * i) = F(0x70 + 4 * i);
    }
    F(0x200) = F(0xF0);
    F(0x204) = F(0xF4);
    F(0x208) = F(0xF8);
    key = (*(s32 *)(sp + 0xB8) + *(s32 *)(sp + 0xE8) + (*(s32 *)(sp + 0xD8) + *(s32 *)(sp + 0xC8))) >> 10;
    F(0x20C) = F(0xFC);
    F(0x210) = F(0x100);
    F(0x214) = F(0x104);
    F(0x218) = F(0x108);
    F(0x21C) = F(0x10C);
    F(0x220) = F(0x110);
    F(0x224) = F(0x114);
    F(0x228) = F(0x118);
    F(0x22C) = F(0x11C);
    for (i = 0; i < 3; i++) {
        F(0x290 + 16 * i) = F(0x60);
        F(0x294 + 16 * i) = F(0x64);
        F(0x298 + 16 * i) = F(0x68);
        F(0x29C + 16 * i) = F(0x6C);
    }

    if (arg6 == 0) {
        func_0012C250(sp + 0x170, sp, arg5, 1, 0, 0, *arg7, key);
    } else {
        func_0012C9E8(sp + 0x170, sp, arg7, arg5, 0xFFFFFF);
    }

    for (i = 0; i < 12; i++) {
        F(0x170 + 4 * i) = F(0x80 + 4 * i);
    }
    for (i = 0; i < 5; i++) {
        F(0x200 + 4 * i) = F(0x100 + 4 * i);
    }
    for (i = 0; i < 7; i++) {
        F(0x214 + 4 * i) = F(0x114 + 4 * i);
    }
    for (i = 0; i < 3; i++) {
        F(0x290 + 16 * i) = F(0x60);
        F(0x294 + 16 * i) = F(0x64);
        F(0x298 + 16 * i) = F(0x68);
        F(0x29C + 16 * i) = F(0x6C);
    }

    if (arg6 == 0) {
        func_0012C250(sp + 0x170, sp, arg5, 1, 0, 0, *arg7, key);
    } else {
        func_0012C9E8(sp + 0x170, sp, arg7, arg5, 0xFFFFFF);
    }
}
