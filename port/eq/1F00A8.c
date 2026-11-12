#include "common.h"

extern void sceVu0RotTransPers(void *arg0, u8 *arg1, void *arg2, s32 arg3);
extern s32 func_001F2A18(s32 arg0, s32 arg1, s32 arg2);
extern u8 *gBtlCamView;
extern u8 *D_00387AD8;
extern u8 *D_00387AE0;

s32 func_001F00A8(s32 r, s32 g, s32 b, s32 a, s64 sx, s64 sy, s32 x0, s32 y0,
                  s32 dx, s32 dy, s32 flagByte, s32 slot, u8 *texq,
                  f32 fx, f32 fy, f32 fz) {
    s32 sp[4];
    f32 pos[4];
    u8 *cam = gBtlCamView;
    u8 *pkt;
    u8 *link;
    u8 *prev;
    f32 camScale = *(f32 *)(cam + 0x224);
    f32 q;
    s32 inv;
    u32 hw;
    u32 hh;
    s32 depth;
    s64 v;
    s64 line;

    if (sx == 0 || sy == 0) {
        return 0;
    }
    pos[3] = 1.0f;
    pos[0] = fx;
    pos[1] = fy;
    pos[2] = fz;
    sceVu0RotTransPers(sp, cam + 0x100, pos, 1);
    q = (camScale * 4096.0f) / (f32)sp[3];
    if (q >= 2147483648.0f) {
        inv = (s32)(q - 2147483648.0f) | (s32)0x80000000;
    } else {
        inv = (s32)q;
    }
    hw = (u32)((s32)sx * inv) >> 12;
    hh = (u32)((s32)sy * inv) >> 12;
    if (hw < 2 || hh < 2) {
        return 0;
    }
    if (func_001F2A18(sp[0] - hw, sp[1] - hh, sp[2]) != 0) return 1;
    if (func_001F2A18(sp[0] - hw, sp[1] + hh, sp[2]) != 0) return 1;
    if (func_001F2A18(sp[0] + hw, sp[1] + hh, sp[2]) != 0) return 1;
    if (func_001F2A18(sp[0] + hw, sp[1] - hh, sp[2]) != 0) return 1;

    pkt = D_00387AD8;
    D_00387AD8 = pkt + 0x60;
    line = (s64)(s8)flagByte;
    *(s64 *)(pkt + 0x20) = (line << 9) | 0x40 | 0x116;
    *(s64 *)(pkt + 0x28) = *(s64 *)texq;
    *(s64 *)(pkt + 0x00) = 0xA0000005LL;
    *(s64 *)(pkt + 0x10) = (s64)0x8400000000008001LL;
    *(s64 *)(pkt + 0x18) = (line << 4) + 0xF4343160LL;
    pkt[0x30] = r;
    pkt[0x31] = g;
    pkt[0x32] = b;
    pkt[0x33] = a;
    *(f32 *)(pkt + 0x34) = 1.0f;
    *(u16 *)(pkt + 0x38) = x0 << 4;
    *(u16 *)(pkt + 0x3A) = y0 << 4;
    *(u16 *)(pkt + 0x48) = (x0 + dx) << 4;
    *(u16 *)(pkt + 0x4A) = (y0 + dy) << 4;
    *(u16 *)(pkt + 0x40) = (u16)sp[0] - hw;
    *(u16 *)(pkt + 0x42) = (u16)sp[1] - hh;
    v = *(s64 *)(pkt + 0x40);
    *(s64 *)(pkt + 0x40) = (v & (s64)0xFF000000FFFFFFFFULL) | ((s64)(sp[2] & 0xFFFFFF) << 32);
    pkt[0x47] = 0xFF;
    *(u16 *)(pkt + 0x50) = (u16)sp[0] + hw;
    *(u16 *)(pkt + 0x52) = (u16)sp[1] + hh;
    v = *(s64 *)(pkt + 0x50);
    *(s64 *)(pkt + 0x50) = (v & (s64)0xFF000000FFFFFFFFULL) | ((s64)(sp[2] & 0xFFFFFF) << 32);
    pkt[0x57] = 0xFF;

    depth = sp[2] >> 8;
    if (depth < 0) {
        link = D_00387AE0 + slot * 8;
        prev = *(u8 **)(link + 4);
    } else if (depth < 0x1000) {
        link = D_00387AE0 + (depth * 2 + slot) * 8;
        prev = *(u8 **)(link + 4);
    } else {
        link = D_00387AE0 + slot * 8 + 0xFFF0;
        prev = *(u8 **)(link + 4);
    }
    *(u8 **)(prev + 4) = pkt;
    *(u8 **)(link + 4) = pkt;
    return 0;
}
