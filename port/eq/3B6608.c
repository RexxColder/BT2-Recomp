#include "common.h"

extern void *Dma_BeginDirect(void);
extern void Dma_EndDirect(s32 arg0);
extern void *memset();
extern void *memcpy();

/* 0x003B6608: builds a 0x80-byte GIF packet (tag 0x10000000_00000001, 0xE, reg) then a quad-draw packet
 * (4 vertices: colour bytes from float quads t0..t3, extra float from p0..p3, shorts from a0/a1/a2/a3). */
void func_003B6608(u8 *a0, u8 *a1, u8 *a2, u8 *a3, f32 *t0, f32 *t1, f32 *t2, f32 *t3,
                   f32 *p0, f32 *p1, f32 *p2, f32 *p3, u64 q4, s64 slot5, s32 flag) {
    u8 sp[0xA0] __attribute__((aligned(16)));
    u8 *s2;
    u32 w;

    *(u8 **)(sp + 0x90) = a3;
    s2 = (u8 *)Dma_BeginDirect();
    *(u64 *)s2 = 0x1000000000000001ull;
    *(u64 *)(s2 + 8) = 0xE;
    s2 += 0x10;
    *(u64 *)s2 = flag ? 0x48 : 0x44;
    *(u64 *)(s2 + 8) = 0x42;
    Dma_EndDirect((s32)(s2 + 0x10));
    s2 = (u8 *)Dma_BeginDirect();
    memset(sp, 0, 0x90);

    *(u64 *)(sp + 0x20) = 0x5C;
    *(u64 *)(sp + 0x10) = 0xE400000000008001ull;
    *(u64 *)(sp + 0x00) = 0xA0000008ull;
    *(u64 *)(sp + 0x18) = 0x42142142142160ull;

    sp[0x30] = (u8)(u32)t0[0];
    sp[0x31] = (u8)(u32)t0[1];
    sp[0x32] = (u8)(u32)t0[2];
    sp[0x33] = (u8)(u32)t0[3];
    *(f32 *)(sp + 0x34) = p0[2];
    sp[0x48] = (u8)(u32)t1[0];
    sp[0x49] = (u8)(u32)t1[1];
    sp[0x4A] = (u8)(u32)t1[2];
    sp[0x4B] = (u8)(u32)t1[3];
    *(f32 *)(sp + 0x4C) = p1[2];
    sp[0x60] = (u8)(u32)t2[0];
    sp[0x61] = (u8)(u32)t2[1];
    sp[0x62] = (u8)(u32)t2[2];
    sp[0x63] = (u8)(u32)t2[3];
    *(f32 *)(sp + 0x64) = p2[2];
    sp[0x78] = (u8)(u32)t3[0];
    sp[0x79] = (u8)(u32)t3[1];
    sp[0x7A] = (u8)(u32)t3[2];
    sp[0x7B] = (u8)(u32)t3[3];

    *(u16 *)(sp + 0x40) = *(u16 *)(a0 + 0);
    *(u16 *)(sp + 0x42) = *(u16 *)(a0 + 4);
    *(u16 *)(sp + 0x58) = *(u16 *)(a1 + 0);
    *(u16 *)(sp + 0x5A) = *(u16 *)(a1 + 4);
    *(u64 *)(sp + 0x40) = (*(u64 *)(sp + 0x40) & 0xFF000000FFFFFFFFull) |
                          ((u64)(*(u32 *)(a0 + 8) & 0xFFFFFF) << 32);
    *(u64 *)(sp + 0x58) = (*(u64 *)(sp + 0x58) & 0xFF000000FFFFFFFFull) |
                          ((u64)(*(u32 *)(a1 + 8) & 0xFFFFFF) << 32);
    *(u64 *)(sp + 0x28) = q4;
    *(f32 *)(sp + 0x7C) = p3[2];
    *(f32 *)(sp + 0x38) = p0[0];
    *(f32 *)(sp + 0x3C) = p0[1];
    *(f32 *)(sp + 0x50) = p1[0];
    *(f32 *)(sp + 0x54) = p1[1];
    *(f32 *)(sp + 0x68) = p2[0];
    *(f32 *)(sp + 0x6C) = p2[1];
    *(f32 *)(sp + 0x80) = p3[0];
    *(f32 *)(sp + 0x84) = p3[1];
    sp[0x47] = 0xFF;

    a3 = *(u8 **)(sp + 0x90);
    *(u16 *)(sp + 0x70) = *(u16 *)(a2 + 0);
    *(u16 *)(sp + 0x72) = *(u16 *)(a2 + 4);
    *(u16 *)(sp + 0x88) = *(u16 *)(a3 + 0);
    *(u16 *)(sp + 0x8A) = *(u16 *)(a3 + 4);
    *(u64 *)(sp + 0x70) = (*(u64 *)(sp + 0x70) & 0xFF000000FFFFFFFFull) |
                          ((u64)(*(u32 *)(a2 + 8) & 0xFFFFFF) << 32);
    *(u64 *)(sp + 0x88) = (*(u64 *)(sp + 0x88) & 0xFF000000FFFFFFFFull) |
                          ((u64)(*(u32 *)(a3 + 8) & 0xFFFFFF) << 32);
    sp[0x5F] = 0xFF;
    sp[0x8F] = 0xFF;
    sp[0x77] = 0xFF;
    memcpy(s2, sp + 0x10, (s32)*(u16 *)sp << 4);
    Dma_EndDirect((s32)(s2 + ((s32)*(u16 *)sp << 4)));
}
