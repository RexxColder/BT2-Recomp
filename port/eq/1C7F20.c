#include "common.h"

void func_0012D868(s32 *arg0, f32 *arg1, f32 *arg2, s32 arg3, f32 *arg4, f32 *arg5);
void func_0012C468(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);

#define FS(o) (*(f32 *)(sp + (o)))
#define WS(o) (*(s32 *)(sp + (o)))

/* 0x001C7F20: builds two 4x4 point sets on the stack from two matrices and 5 vec4 pairs, runs func_0012D868
   over them and calls func_0012C468 twice with the resulting point arrays. */
void func_001C7F20(u8 *m0, u8 *m1, s64 *pts, s64 *uv0, s64 *uv1, s64 *uv2, s32 unused, u8 *out, s32 idx, s32 arg9) {
    u8 sp[0x2C0];
    u8 *dst = out + (idx << 4);
    s64 *tex = (s64 *)uv1;
    u8 *colp;
    s32 sum;
    s32 i;
    f32 one = 1.0f;

    (void)unused;
    *(s64 *)(sp + 0x00) = pts[0];
    *(s64 *)(sp + 0x08) = pts[1];
    *(s64 *)(sp + 0x10) = pts[2];
    *(s64 *)(sp + 0x18) = pts[3];
    *(s64 *)(sp + 0x20) = pts[4];
    *(s64 *)(sp + 0x28) = pts[5];
    *(s64 *)(sp + 0x30) = pts[6];
    *(s64 *)(sp + 0x38) = pts[7];
    *(s64 *)(sp + 0x40) = uv0[0];
    *(s64 *)(sp + 0x48) = uv0[1];
    *(s64 *)(sp + 0x50) = tex[0];
    *(s64 *)(sp + 0x58) = tex[1];
    *(s64 *)(sp + 0x60) = ((s64 *)uv2)[0];
    *(s64 *)(sp + 0x68) = ((s64 *)uv2)[1];
    colp = sp + 0x60;

    FS(0xF0) = FS(0x40);
    FS(0xF4) = FS(0x44);
    FS(0x70) = *(f32 *)(m0 + 0x30);
    FS(0x74) = *(f32 *)(m0 + 0x34);
    FS(0x78) = *(f32 *)(m0 + 0x38);
    FS(0x80) = *(f32 *)(m0 + 0x40);
    FS(0x84) = *(f32 *)(m0 + 0x44);
    FS(0x88) = *(f32 *)(m0 + 0x48);
    FS(0x100) = FS(0x48);
    FS(0x104) = FS(0x4C);
    FS(0x110) = FS(0x50);
    FS(0x114) = FS(0x54);
    FS(0x120) = FS(0x58);
    FS(0x124) = FS(0x5C);
    FS(0xF8) = one;
    FS(0x108) = one;
    FS(0x118) = one;
    FS(0x128) = one;
    FS(0x90) = *(f32 *)(m1 + 0x30);
    WS(0xFC) = 0;
    WS(0x10C) = 0;
    WS(0x11C) = 0;
    WS(0x12C) = 0;
    FS(0x94) = *(f32 *)(m1 + 0x34);
    FS(0x98) = *(f32 *)(m1 + 0x38);
    FS(0xA0) = *(f32 *)(m1 + 0x40);
    FS(0xA4) = *(f32 *)(m1 + 0x44);
    FS(0xA8) = *(f32 *)(m1 + 0x48);
    FS(0x7C) = one;
    FS(0xAC) = one;
    FS(0x9C) = one;
    FS(0x8C) = one;
    func_0012D868((s32 *)(sp + 0xB0), (f32 *)sp, (f32 *)(sp + 0x70), 4, (f32 *)(sp + 0x130), (f32 *)(sp + 0xF0));

    for (i = 0; i < 12; i++) {
        FS(0x170 + i * 4) = FS(0x70 + i * 4);
    }
    FS(0x200) = FS(0xF0);
    FS(0x204) = FS(0xF4);
    sum = WS(0xB8) + WS(0xE8);
    FS(0x208) = FS(0xF8);
    sum = sum + (WS(0xD8) + WS(0xC8));
    sum = sum >> 10;
    for (i = 0; i < 9; i++) {
        FS(0x20C + i * 4) = FS(0xFC + i * 4);
    }
    FS(0x290) = *(f32 *)colp;
    FS(0x294) = FS(0x64);
    FS(0x298) = FS(0x68);
    FS(0x29C) = FS(0x6C);
    FS(0x2A0) = *(f32 *)colp;
    FS(0x2A4) = FS(0x64);
    FS(0x2A8) = FS(0x68);
    FS(0x2AC) = FS(0x6C);
    FS(0x2B0) = *(f32 *)colp;
    FS(0x2B4) = FS(0x64);
    FS(0x2B8) = FS(0x68);
    FS(0x2BC) = FS(0x6C);
    func_0012C468((s32)(sp + 0x170), (s32)sp, (s32)dst, 0, sum, arg9);

    for (i = 0; i < 6; i++) {
        FS(0x188 + i * 4) = FS(0x98 + i * 4);
    }
    FS(0x200) = FS(0x100);
    for (i = 0; i < 6; i++) {
        FS(0x170 + i * 4) = FS(0x80 + i * 4);
    }
    for (i = 0; i < 4; i++) {
        FS(0x204 + i * 4) = FS(0x104 + i * 4);
    }
    for (i = 0; i < 7; i++) {
        FS(0x214 + i * 4) = FS(0x114 + i * 4);
    }
    FS(0x290) = *(f32 *)colp;
    FS(0x294) = FS(0x64);
    FS(0x298) = FS(0x68);
    FS(0x29C) = FS(0x6C);
    FS(0x2A0) = *(f32 *)colp;
    FS(0x2A4) = FS(0x64);
    FS(0x2A8) = FS(0x68);
    FS(0x2AC) = FS(0x6C);
    FS(0x2B0) = *(f32 *)colp;
    FS(0x2B4) = FS(0x64);
    FS(0x2B8) = FS(0x68);
    FS(0x2BC) = FS(0x6C);
    func_0012C468((s32)(sp + 0x170), (s32)sp, (s32)dst, 0, sum, arg9);
}
