#include "common.h"

extern f32 D_003856F8;
extern f32 D_003856FC;
extern f32 D_00385700;
extern f32 D_00385704;
extern u8 *gBtlCamView;
extern u8 *D_00387AD8;
extern u8 *D_00387AE0;

extern s32 Vec4_Set(f32 *v, f32 x, f32 y, f32 z, f32 w);
void Vec4_Sub(u8 *arg0, u8 *arg1, u8 *arg2);
void Vec3_Normalize(u8 *arg0, u8 *arg1);
void Vec3_Add(u8 *arg0, u8 *arg1, u8 *arg2);
void Mtx_MulVec4(f32 *arg0, f32 *arg1, f32 *arg2);
void func_001F2BB0(s32 arg0, s32 arg1, f32 farg0);
s32 Mtx_ProjectPoints(s32 *arg0, f32 *arg1, f32 *arg2, s32 arg3, s32 arg4);
s32 func_001F2A18(s32 arg0, s32 arg1, s32 arg2);

/* Billboard quad (a GIF packet of 0x80 bytes) at world point (farg0, farg1, farg2), rotated by farg7, half
   size = (arg4, arg5) * arg7 / 4096 / 16, uv corners farg3..farg6; linked into the ordering table. */
void func_001F0418(f32 farg0, f32 farg1, f32 farg2, f32 farg3, f32 farg4, f32 farg5, f32 farg6, f32 farg7,
                   s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7,
                   s32 arg8, s32 arg9, s32 arg10) {
    f32 pos[4];
    f32 dir[4];
    f32 mtx[16];
    f32 quad[16];
    s32 out[16];
    f32 angle = farg7;
    f32 halfW, halfH;
    s32 i, z, depth;
    u8 *pkt;
    u8 *link;
    u8 *prev;
    s32 flag;
    u64 v;

    if (D_003856F8 < angle) {
        angle = angle - D_003856FC;
    } else if (angle < D_00385700) {
        angle = angle + D_00385704;
    }
    halfW = (f32)((u32)(arg4 * arg7) >> 12) * 0.0625f;
    halfH = (f32)((u32)(arg5 * arg7) >> 12) * 0.0625f;

    Vec4_Set(pos, farg0, farg1, farg2, 1.0f);
    Vec4_Sub((u8 *)dir, gBtlCamView + 0x1F0, (u8 *)pos);
    Vec3_Normalize((u8 *)dir, (u8 *)dir);
    func_001F2BB0((s32)(u32)mtx, (s32)(u32)dir, angle);
    Vec4_Set(&quad[0], -halfW, -halfH, 0.0f, 1.0f);
    Vec4_Set(&quad[4], halfW, -halfH, 0.0f, 1.0f);
    Vec4_Set(&quad[8], -halfW, halfH, 0.0f, 1.0f);
    Vec4_Set(&quad[12], halfW, halfH, 0.0f, 1.0f);
    for (i = 0; i < 4; i++) {
        Mtx_MulVec4(&quad[i * 4], mtx, &quad[i * 4]);
        Vec3_Add((u8 *)&quad[i * 4], (u8 *)&quad[i * 4], (u8 *)pos);
        quad[i * 4 + 3] = 1.0f;
    }
    Mtx_ProjectPoints(out, (f32 *)(gBtlCamView + 0x100), quad, 4, 1);

    if (func_001F2A18(out[0], out[1], out[2]) != 0) {
        return;
    }
    if (func_001F2A18(out[4], out[5], out[6]) != 0) {
        return;
    }
    if (func_001F2A18(out[8], out[9], out[10]) != 0) {
        return;
    }
    if (func_001F2A18(out[12], out[13], out[14]) != 0) {
        return;
    }

    flag = (s8)arg8;
    pkt = D_00387AD8;
    D_00387AD8 = pkt + 0x80;
    z = (out[2] >> 8) << 8;
    out[2] = z;
    *(u64 *)(pkt + 0x20) = (u64)((s64)flag << 9) | 0x54;
    *(u64 *)(pkt + 0x28) = *(u64 *)(u32)arg10;
    *(u64 *)(pkt + 0x00) = 0xA0000007ULL;
    *(u64 *)(pkt + 0x10) = 0xC400000000008001ULL;
    *(u64 *)(pkt + 0x18) = (u64)((s64)(flag * 16) + 0xF42424242160LL);
    pkt[0x30] = (u8)arg0;
    pkt[0x31] = (u8)arg1;
    pkt[0x32] = (u8)arg2;
    pkt[0x33] = (u8)arg3;
    *(f32 *)(pkt + 0x34) = 1.0f;
    *(f32 *)(pkt + 0x48) = farg3;
    *(f32 *)(pkt + 0x5C) = farg4;
    *(f32 *)(pkt + 0x68) = farg5;
    *(f32 *)(pkt + 0x6C) = farg6;
    *(f32 *)(pkt + 0x38) = farg3;
    *(f32 *)(pkt + 0x3C) = farg4;
    *(f32 *)(pkt + 0x4C) = farg6;
    *(f32 *)(pkt + 0x58) = farg5;

    *(u16 *)(pkt + 0x40) = (u16)out[0];
    *(u16 *)(pkt + 0x42) = (u16)out[1];
    v = *(u64 *)(pkt + 0x40);
    *(u64 *)(pkt + 0x40) = (v & 0xFF000000FFFFFFFFULL) | ((u64)((u32)out[2] & 0xFFFFFF) << 32);
    pkt[0x47] = 0xFF;
    *(u16 *)(pkt + 0x50) = (u16)out[8];
    *(u16 *)(pkt + 0x52) = (u16)out[9];
    v = *(u64 *)(pkt + 0x50);
    *(u64 *)(pkt + 0x50) = (v & 0xFF000000FFFFFFFFULL) | ((u64)((u32)out[2] & 0xFFFFFF) << 32);
    pkt[0x57] = 0xFF;
    *(u16 *)(pkt + 0x60) = (u16)out[4];
    *(u16 *)(pkt + 0x62) = (u16)out[5];
    v = *(u64 *)(pkt + 0x60);
    *(u64 *)(pkt + 0x60) = (v & 0xFF000000FFFFFFFFULL) | ((u64)((u32)out[2] & 0xFFFFFF) << 32);
    pkt[0x67] = 0xFF;
    *(u16 *)(pkt + 0x70) = (u16)out[12];
    *(u16 *)(pkt + 0x72) = (u16)out[13];
    v = *(u64 *)(pkt + 0x70);
    *(u64 *)(pkt + 0x70) = (v & 0xFF000000FFFFFFFFULL) | ((u64)((u32)out[2] & 0xFFFFFF) << 32);
    pkt[0x77] = 0xFF;

    depth = out[2] >> 8;
    if (depth < 0) {
        link = D_00387AE0 + arg9 * 8;
        prev = *(u8 **)(link + 4);
    } else if (depth < 0x1000) {
        link = D_00387AE0 + (depth * 2 + arg9) * 8;
        prev = *(u8 **)(link + 4);
    } else {
        link = D_00387AE0 + arg9 * 8 + 0xFFF0;
        prev = *(u8 **)(link + 4);
    }
    *(u8 **)(prev + 4) = pkt;
    *(u8 **)(link + 4) = pkt;
}
