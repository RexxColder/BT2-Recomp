#include "common.h"

s32 BtlTaskList_AddTail(s32 arg0, u8 *arg1, u8 *arg2);
f32 cosf(f32 arg0);
f32 sinf(f32 arg0);
void func_002088F0(s32 arg0, u8 *arg1);
void sceVu0UnitMatrix(u8 *arg0);
void sceVu0RotMatrix(u8 *arg0, u8 *arg1, u8 *arg2);
void sceVu0ApplyMatrix(u8 *arg0, u8 *arg1, u8 *arg2);
extern u8 D_00342560[] __attribute__((section(".data")));
extern f32 D_00384E88;
extern void *D_00387830;
void bt2_fightlog_note(const char *fmt, ...);

s32 func_001A5EF0(s32 arg0, u8 *arg1, s32 arg2) {
    u8 blk[0x80];
    u8 *s0;
    s32 idx;
    s32 v0;
    f32 f20;

    idx = arg0 & 0xFF;
    { static int n; if (n++ < 60) bt2_fightlog_note("EFECTO-1A5EF0 tipo %X lista %p", idx, D_00387830); } /* TEMP: chispas de golpe */
    memset(blk, 0, 0x30);
    v0 = 0;
    if (D_00387830 != NULL) {
        f20 = D_00384E88;
        *(f32 *)(blk + 0x00) = *(f32 *)(arg1 + 0x0);
        *(f32 *)(blk + 0x04) = *(f32 *)(arg1 + 0x4);
        *(f32 *)(blk + 0x08) = *(f32 *)(arg1 + 0x8);
        *(f32 *)(blk + 0x0C) = *(f32 *)(arg1 + 0xC);
        *(f32 *)(blk + 0x10) = 0.0f;
        *(f32 *)(blk + 0x14) = 0.0f;
        *(f32 *)(blk + 0x18) = 1.0f;
        *(f32 *)(blk + 0x1C) = 1.0f;
        *(s32 *)(blk + 0x20) = arg2;
        *(s32 *)(blk + 0x28) = idx;
        *(s32 *)(blk + 0x2C) = 0;
        if (idx == 0xF) {
            *(f32 *)(blk + 0x14) = -sinf(f20);
            *(f32 *)(blk + 0x18) = cosf(f20);
        }
        memset(blk + 0x30, 0, 0x10);
        func_002088F0(arg2, blk + 0x30);
        s0 = blk + 0x40;
        sceVu0UnitMatrix(s0);
        sceVu0RotMatrix(s0, s0, blk + 0x30);
        sceVu0ApplyMatrix(blk + 0x10, s0, blk + 0x10);
        v0 = BtlTaskList_AddTail(*(s32 *)((u8 *)D_00387830 + 0x74C), D_00342560, blk);
    }
    return v0;
}
