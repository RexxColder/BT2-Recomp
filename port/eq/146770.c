#include "common.h"

extern void Vec4_Set(void *arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3);
extern void func_00129BB8(f32 farg0, void *arg0, void *arg1);
extern void Mtx_StoreIdentity(void *arg0);
extern void sceVu0TransposeMatrix(void *arg0, void *arg1);
extern void Vu0Screen_StoreMtx(void *arg0);
extern void func_00129C50(void *arg0, void *arg1, void *arg2);
extern void func_00129B28(void *arg0, void *arg1, void *arg2);
extern void func_00145AE0(s32 *arg0, f32 *arg1, f32 *arg2);
extern u8 *gEftWeather;
extern u8 *gBtlCamView;
extern u8 *D_00387AD8;
extern u8 *D_00387AE0;
extern u32 D_0036DDE0[4];

/* Weather streak/quad submit: builds two corner vectors scaled by the weather size, projects
   count box corners (48-byte records) and queues one 0xA0-byte GIF packet per visible pair
   into the depth-sorted OT list (D_00387AE0). */
void func_00146770(u8 *rec, s32 count) {
    f32 mtx[16];
    f32 screen[16];
    u32 rgbaA[2];
    u32 rgbaB[2];
    f32 lo[4];
    f32 hi[4];
    f32 pa[4];
    f32 pb[4];
    s32 outA[4];
    s32 outB[4];
    u8 *table;

    rgbaA[0] = D_0036DDE0[0];
    rgbaA[1] = D_0036DDE0[1];
    rgbaB[0] = D_0036DDE0[2];
    rgbaB[1] = D_0036DDE0[3];
    Vec4_Set(lo, -1.0f, -1.0f, 0.0f, 0.0f);
    Vec4_Set(hi, 1.0f, 1.0f, 0.0f, 0.0f);
    func_00129BB8(*(f32 *)(gEftWeather + 0x2AC), lo, lo);
    func_00129BB8(*(f32 *)(gEftWeather + 0x2AC), hi, hi);
    Mtx_StoreIdentity(mtx);
    if (gBtlCamView) {
        sceVu0TransposeMatrix(mtx, gBtlCamView);
    }
    Vu0Screen_StoreMtx(screen);
    func_00129C50(lo, mtx, lo);
    func_00129C50(hi, mtx, hi);
    table = gEftWeather + 8;

    for (; count > 0; count--) {
        func_00129B28(pa, lo, rec);
        func_00129B28(pb, hi, rec);
        func_00145AE0(outA, screen, pa);
        if (outA[2] <= 0) {
            continue;
        }
        func_00145AE0(outB, screen, pb);
        if (outB[2] <= 0) {
            continue;
        }
        {
            u64 *p = (u64 *)D_00387AD8;
            u8 *bucket;
            u8 *prev;
            s32 depth;

            D_00387AD8 = (u8 *)p + 0xA0;
            p[0] = 0xA0000009ULL;
            p[2] = 0x1000000000008008ULL;
            p[3] = 14;
            p[4] = 0x5E;
            p[7] = 6;
            p[5] = 0;
            p[6] = *(u64 *)(table + *(s32 *)(rec + 0x2C) * 16);
            p[9] = 1;
            p[8] = *(u64 *)(rec + 0x20);
            p[11] = 2;
            p[10] = (u64)rgbaA[0] | ((u64)rgbaA[1] << 32);
            p[13] = 4;
            p[12] = (u64)(s64)outA[0] | ((u64)(s64)outA[2] << 32) | ((u64)(s64)outA[1] << 16) |
                    0xFF00000000000000ULL;
            p[15] = 1;
            p[14] = *(u64 *)(rec + 0x20);
            rec += 0x30;
            p[17] = 2;
            p[16] = (u64)rgbaB[0] | ((u64)rgbaB[1] << 32);
            p[19] = 4;
            p[18] = (u64)(s64)outB[0] | ((u64)(s64)outA[2] << 32) | ((u64)(s64)outB[1] << 16) |
                    0xFF00000000000000ULL;

            depth = outA[2] >> 8;
            if (depth < 0) {
                bucket = D_00387AE0;
            } else if (depth < 0x1000) {
                bucket = D_00387AE0 + depth * 16;
            } else {
                bucket = D_00387AE0 + 0xFFF0;
            }
            prev = *(u8 **)(bucket + 4);
            *(u8 **)(prev + 4) = (u8 *)p;
            *(u8 **)(bucket + 4) = (u8 *)p;
        }
    }
}
