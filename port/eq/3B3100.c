#include "common.h"

extern u8 *D_00421380 __attribute__((section(".data")));
extern u8 *D_0042138C __attribute__((section(".data")));
extern u8 *D_3876A4 __attribute__((section(".data")));

extern s32 func_00100D58();
extern u8 *func_0028BAA8();
extern u8 *func_002B24C8();
extern s32 func_00325370();
extern s64 GetTimerSystemTime();
extern void Res_RelocateOffsets();
extern s32 func_0024BED8();
extern s32 func_0026E7F0();
extern s32 func_0026EAE0();
extern s32 func_00249560();
extern void *memset();

/* 0x003B3100: MainMenu_StartBallLoops - allocate ctx D_00421380 (0x120), load resource, relocate sub-blocks */
void MainMenu_StartBallLoops(s32 arg0) {
    u8 sp[0x10] __attribute__((aligned(16)));
    s32 i;

    *(u32 *)sp = 0;
    if (D_0042138C == 0) {
        func_00100D58(*(s32 *)(D_3876A4 + 4) + 1, 0, 1);
        do {
            D_0042138C = (u8 *)func_00100D58(0, 0, 0);
        } while (D_0042138C == 0);
    }
    D_00421380 = func_0028BAA8(0x120);
    memset(D_00421380, 0, 0x120);
    *(u8 **)D_00421380 = D_0042138C + (*(u32 *)(D_0042138C + arg0 * 4) >> 2) * 4;
    *(u8 **)(D_00421380 + 4) = func_002B24C8(*(u8 **)D_00421380, 0, 0, D_00421380);
    func_00325370((s32)GetTimerSystemTime());
    {
        u8 *a = *(u8 **)(D_00421380 + 4);
        u8 *v = a + (*(u32 *)(a + 0x50) >> 2) * 4;
        *(u8 **)sp = v;
        Res_RelocateOffsets(sp, v, v);
    }
    {
        u8 *a = *(u8 **)(D_00421380 + 4);
        func_0024BED8(a + (*(u32 *)(a + 0x5C) >> 2) * 4, *(s32 *)(*(u8 **)sp + 0x10), a);
    }
    {
        u8 *a = *(u8 **)(D_00421380 + 4);
        u8 *v = a + (*(u32 *)(a + 0x38) >> 2) * 4;
        *(u8 **)sp = v;
        Res_RelocateOffsets(sp, v, v);
    }
    *(u8 **)(D_00421380 + 0x8C) = *(u8 **)(*(u8 **)sp + 0x10);
    *(u8 **)(D_00421380 + 0x90) = *(u8 **)(*(u8 **)sp + 0x10) + 0x40;
    {
        u8 *a = *(u8 **)(D_00421380 + 4);
        u8 *v = a + (*(u32 *)(a + 0x34) >> 2) * 4;
        *(u8 **)sp = v;
        Res_RelocateOffsets(sp, v, v);
    }
    *(u8 **)(D_00421380 + 0x98) = *(u8 **)(*(u8 **)sp + 0x10);
    {
        u8 *a = *(u8 **)(D_00421380 + 4);
        u8 *v = a + (*(u32 *)(a + 0x30) >> 2) * 4;
        *(u8 **)sp = v;
        Res_RelocateOffsets(sp, v, v);
    }
    *(u8 **)(D_00421380 + 0x88) = *(u8 **)(*(u8 **)sp + 0x10);
    {
        u8 *a = *(u8 **)(D_00421380 + 4);
        u8 *v = a + (*(u32 *)(a + 0x2C) >> 2) * 4;
        *(u8 **)sp = v;
        Res_RelocateOffsets(sp, v, v);
    }
    *(u8 **)(D_00421380 + 0x9C) = *(u8 **)(*(u8 **)sp + 0x10);
    {
        u8 *a = *(u8 **)(D_00421380 + 4);
        u8 *v = a + (*(u32 *)(a + 0x28) >> 2) * 4;
        *(u8 **)sp = v;
        Res_RelocateOffsets(sp, v, v);
    }
    *(u8 **)(D_00421380 + 0x94) = *(u8 **)(*(u8 **)sp + 0x10);
    {
        u8 *a = *(u8 **)(D_00421380 + 4);
        u8 *v = a + (*(u32 *)(a + 0x8) >> 2) * 4;
        *(u8 **)sp = v;
        Res_RelocateOffsets(sp, v, v);
    }
    *(u8 **)(D_00421380 + 0xA0) = *(u8 **)(*(u8 **)sp + 0x10);
    func_0026E7F0(D_00421380 + 0x38, *(u8 **)(D_00421380 + 4) + (*(u32 *)(*(u8 **)(D_00421380 + 4) + 0x4) >> 2) * 4, D_00421380 + 0x88);
    func_0026EAE0(D_00421380 + 0x38, 0x3C);
    {
        u8 *a = *(u8 **)(D_00421380 + 4);
        u8 *v = a + (*(u32 *)(a + 0x58) >> 2) * 4;
        *(u8 **)sp = v;
        Res_RelocateOffsets(sp, v, v);
    }
    *(u8 **)(D_00421380 + 0xC8) = *(u8 **)(*(u8 **)sp + 0x10);
    {
        u8 *a = *(u8 **)(D_00421380 + 4);
        u8 *v = a + (*(u32 *)(a + 0x3C) >> 2) * 4;
        *(u8 **)sp = v;
        Res_RelocateOffsets(sp, v, v);
    }
    *(u8 **)(D_00421380 + 0xE0) = *(u8 **)(*(u8 **)sp + 0x10);
    *(u8 **)(D_00421380 + 0xC4) = *(u8 **)(*(u8 **)sp + 0x10) + 0x40;
    {
        u8 *a = *(u8 **)(D_00421380 + 4);
        u8 *v = a + (*(u32 *)(a + 0x44) >> 2) * 4;
        *(u8 **)sp = v;
        Res_RelocateOffsets(sp, v, v);
    }
    *(u8 **)(D_00421380 + 0xCC) = *(u8 **)(*(u8 **)sp + 0x10);
    *(u8 **)(D_00421380 + 0xD0) = *(u8 **)(*(u8 **)sp + 0x10);
    *(u8 **)(D_00421380 + 0xD4) = *(u8 **)(*(u8 **)sp + 0x10);
    *(u8 **)(D_00421380 + 0xD8) = *(u8 **)(*(u8 **)sp + 0x10);
    *(u8 **)(D_00421380 + 0xDC) = *(u8 **)(*(u8 **)sp + 0x10);
    func_0026E7F0(D_00421380 + 0x60, *(u8 **)(D_00421380 + 4) + (*(u32 *)(*(u8 **)(D_00421380 + 4) + 0x48) >> 2) * 4, D_00421380 + 0xC4);
    func_0026EAE0(D_00421380 + 0x60, 0x3C);
    {
        u8 *a = *(u8 **)(D_00421380 + 4);
        u8 *v = a + (*(u32 *)(a + 0x10) >> 2) * 4;
        *(u8 **)sp = v;
        Res_RelocateOffsets(sp, v, v);
    }
    *(u8 **)(D_00421380 + 0xA8) = *(u8 **)(*(u8 **)sp + 0x10);
    *(u8 **)(D_00421380 + 0xB8) = *(u8 **)(*(u8 **)sp + 0x10) + 0x40;
    {
        u8 *a = *(u8 **)(D_00421380 + 4);
        u8 *v = a + (*(u32 *)(a + 0x14) >> 2) * 4;
        *(u8 **)sp = v;
        Res_RelocateOffsets(sp, v, v);
    }
    *(u8 **)(D_00421380 + 0xBC) = *(u8 **)(*(u8 **)sp + 0x10);
    *(u8 **)(D_00421380 + 0xC0) = *(u8 **)(*(u8 **)sp + 0x10) + 0x40;
    {
        u8 *a = *(u8 **)(D_00421380 + 4);
        u8 *v = a + (*(u32 *)(a + 0x18) >> 2) * 4;
        *(u8 **)sp = v;
        Res_RelocateOffsets(sp, v, v);
    }
    *(u8 **)(D_00421380 + 0xAC) = *(u8 **)(*(u8 **)sp + 0x10) + 0x80;
    *(u8 **)(D_00421380 + 0xB0) = *(u8 **)(*(u8 **)sp + 0x10);
    *(u8 **)(D_00421380 + 0xB4) = *(u8 **)(*(u8 **)sp + 0x10) + 0x40;
    {
        u8 *a = *(u8 **)(D_00421380 + 4);
        u8 *v = a + (*(u32 *)(a + 0x1C) >> 2) * 4;
        *(u8 **)sp = v;
        Res_RelocateOffsets(sp, v, v);
    }
    *(u8 **)(D_00421380 + 0xA4) = *(u8 **)(*(u8 **)sp + 0x10);
    func_0026E7F0(D_00421380 + 0x10, *(u8 **)(D_00421380 + 4) + (*(u32 *)(*(u8 **)(D_00421380 + 4) + 0xC) >> 2) * 4, D_00421380 + 0xA4);
    func_0026EAE0(D_00421380 + 0x10, 0x3C);
    *(u8 **)(D_00421380 + 0xC) = *(u8 **)(D_00421380 + 4) + (*(u32 *)(*(u8 **)(D_00421380 + 4) + 0x40) >> 2) * 4;
    *(u8 **)(D_00421380 + 8) = *(u8 **)(D_00421380 + 4) + (*(u32 *)(*(u8 **)(D_00421380 + 4) + 0x4C) >> 2) * 4;
    *(s32 *)(D_00421380 + 0xE8) = *(s32 *)(D_3876A4 + 0x28);
    *(s32 *)(D_00421380 + 0xF0) = *(s32 *)(D_00421380 + 0xE8) - 2;
    if (*(s32 *)(D_00421380 + 0xF0) < 0) {
        *(s32 *)(D_00421380 + 0xF0) = *(s32 *)(D_00421380 + 0xF0) + 0xA;
    }
    *(s32 *)(D_00421380 + 0xEC) = 8;
    *(s32 *)(D_00421380 + 0xF4) = 0;
    for (i = 0; i < 2; i++) {
        func_00249560(D_00421380 + i * 4 + 0x110);
    }
}
