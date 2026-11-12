#include "common.h"

u8 *func_0012B9B0(void);
s32 func_0012BEC0(u8 *arg0, s32 arg1, u8 *arg2);
s32 func_0012A108(u8 *a0, u8 *a1, u8 *a2, u8 *a3, u8 *t0, s32 t1);
void func_001448C8(u8 *a0, u8 *a1, u8 *a2, u8 *a3, u8 *t0, u8 *t1, u8 *t2, u8 *t3, u8 *st0, s32 st1, s64 st2);
void func_00129C28(u8 *arg0, u8 *arg1);

#define FS(o) (*(f32 *)(sp + (o)))

/* 0x00144EE0: clips a triangle (positions p0..p2, uvs, colors; 16-byte vec4 copies on the stack) against the five
   planes returned by func_0012B9B0 with func_0012BEC0, then draws the resulting polygon as a fan of triangles through
   func_001448C8. Returns 0 when the fan was drawn, the func_0012A108 result when the polygon has fewer than 3 points
   and 0 when nothing is left. */
s32 func_00144EE0(u8 *m, u8 *p0, u8 *p1, u8 *p2, u8 *p3, u8 *p4, u8 *uv0, u8 *uv1, u8 *uv2, u8 *uv3, s32 arg10,
                  s64 arg11) {
    u8 sp[0x580];   /* tamano de locales del original (antes 0x570) */
    u8 *planes;
    s32 planeCnt = 4;
    s32 n = 3;
    s32 i;
    s32 r;
    f32 fx;
    f32 fy;

    __builtin_memcpy(sp + 0x20, m, 0x40);
    __builtin_memcpy(sp + 0x60, p0, 16);
    __builtin_memcpy(sp + 0x70, p1, 16);
    __builtin_memcpy(sp + 0x80, p2, 16);
    __builtin_memcpy(sp + 0x90, p3, 16);
    __builtin_memcpy(sp + 0xA0, p4, 16);
    __builtin_memcpy(sp + 0xB0, uv0, 16);
    __builtin_memcpy(sp + 0xC0, uv1, 16);
    __builtin_memcpy(sp + 0xD0, uv2, 16);
    __builtin_memcpy(sp + 0xE0, uv3, 16);
    __builtin_memset(sp + 0xF0, 0, 0x1B0);
    planes = func_0012B9B0();
    __builtin_memset(sp + 0x2A0, 0, 0x90);
    __builtin_memset(sp + 0x330, 0, 0x90);
    __builtin_memset(sp + 0x3C0, 0, 0x90);
    __builtin_memset(sp + 0x450, 0, 0x90);
    __builtin_memset(sp + 0x4E0, 0, 0x90);
    func_00129C28(sp + 0xF0, sp + 0x60);
    func_00129C28(sp + 0x100, sp + 0x70);
    func_00129C28(sp + 0x110, sp + 0x80);
    func_00129C28(sp + 0x180, sp + 0x90);
    func_00129C28(sp + 0x190, sp + 0xA0);
    func_00129C28(sp + 0x1A0, sp + 0xB0);
    fx = (f32)(s32)FS(0x90);
    fy = (f32)(s32)FS(0x94);
    FS(0x1A0) = FS(0x1A0) - fx;
    FS(0x1A4) = FS(0x1A4) - fy;
    FS(0x180) = FS(0x180) - fx;
    FS(0x190) = FS(0x190) - fx;
    FS(0x184) = FS(0x184) - fy;
    FS(0x194) = FS(0x194) - fy;
    func_00129C28(sp + 0x210, sp + 0xC0);
    func_00129C28(sp + 0x220, sp + 0xD0);
    func_00129C28(sp + 0x230, sp + 0xE0);
    do {
        n = func_0012BEC0(planes, n, sp + 0xF0);
        planes = planes + 0x10;
        planeCnt = planeCnt - 1;
    } while (planeCnt >= 0);
    if (n == 0) {
        return 0;
    }
    for (i = 0; i < n; i++) {
        func_00129C28(sp + 0x330 + i * 16, sp + 0xF0 + i * 16);
        func_00129C28(sp + 0x3C0 + i * 16, sp + 0x210 + i * 16);
        func_00129C28(sp + 0x450 + i * 16, sp + 0x180 + i * 16);
        FS(0x33C + i * 16) = 1.0f;
        FS(0x458 + i * 16) = 1.0f;
        *(s32 *)(sp + 0x45C + i * 16) = 0;
    }
    r = func_0012A108(sp + 0x2A0, sp + 0x4E0, sp + 0x20, sp + 0x330, sp + 0x450, n);
    if (n > 2) {
        for (i = 2; i < n; i++) {
            func_001448C8(sp + 0x2A0, sp + 0x2A0 + (i - 1) * 16, sp + 0x2A0 + i * 16, sp + 0x4E0,
                          sp + 0x4E0 + (i - 1) * 16, sp + 0x4E0 + i * 16, sp + 0x3C0, sp + 0x3C0 + (i - 1) * 16,
                          sp + 0x3C0 + i * 16, arg10, arg11);
        }
        return 0;
    }
    return r;
}
