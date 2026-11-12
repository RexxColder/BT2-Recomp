#include "common.h"

s32 EftPtcl3_Create(s32 arg0);
void EftPtcl3_SetTexture(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void EftPtcl3_SetType(s32 arg0, s32 arg1);
void func_00129BD0(s32 arg0, s32 arg1, f32 farg0);
void func_00129C28(s32 arg0, s32 arg1);
void *memset(void *arg0, s32 arg1, u32 arg2);

void func_0019AE80(u8 *arg0) {
    s64 spbuf[22];
    u8 *sp;
    u8 *P;
    u8 *Q;
    s32 i;
    s32 s6;
    s32 cr;
    s32 k;
    s32 off;

    sp = (u8 *)spbuf;
    P = (u8 *)*(s32 *)(arg0 + 0x38);
    Q = (u8 *)*(s32 *)P;
    s6 = 0;

    for (i = 0; i < 3; i++) {
        off = i * 4;
        *(f32 *)(sp + 0x50) = *(f32 *)(Q + off);
        *(f32 *)(sp + 0x54) = *(f32 *)(Q + 0xC + off);
        memset(sp + 0x60, 0, 0x10);
        memset(sp + 0x70, 0, 0x10);
        *(s32 *)(sp + 0x80) = *(u8 *)(Q + 0x20 + i);
        *(s32 *)(sp + 0x84) = *(s32 *)(P + 0x4);
        *(s32 *)(sp + 0x88) = *(s32 *)(P + 0x8) + 0x164 * i;
        *(s32 *)(sp + 0x8C) = *(s32 *)(P + 0xC) + s6;
        *(s32 *)(sp + 0x90) = *(s32 *)(P + 0x50);

        /* copy the 0x40-byte block at sp+0x50 to sp+0x00 (two 32-byte steps) */
        *(s64 *)(sp + 0x00) = *(s64 *)(sp + 0x50);
        *(s64 *)(sp + 0x08) = *(s64 *)(sp + 0x58);
        *(s64 *)(sp + 0x10) = *(s64 *)(sp + 0x60);
        *(s64 *)(sp + 0x18) = *(s64 *)(sp + 0x68);
        *(s64 *)(sp + 0x20) = *(s64 *)(sp + 0x70);
        *(s64 *)(sp + 0x28) = *(s64 *)(sp + 0x78);
        *(s64 *)(sp + 0x30) = *(s64 *)(sp + 0x80);
        *(s64 *)(sp + 0x38) = *(s64 *)(sp + 0x88);
        /* the 16 bytes at sp+0x90 go to sp+0x40 */
        *(s64 *)(sp + 0x40) = *(s64 *)(sp + 0x90);
        *(s64 *)(sp + 0x48) = *(s64 *)(sp + 0x98);

        func_00129C28((s32)(sp + 0x10), (s32)(P + 0x30));
        func_00129C28((s32)(sp + 0x20), (s32)(P + 0x40));
        if (*(u8 *)(Q + 0x24 + i) == 0) {
            func_00129BD0((s32)(sp + 0x20), (s32)(sp + 0x20), -1.0f);
        }

        cr = EftPtcl3_Create((s32)sp);
        s6 += 0x50;
        *(s32 *)(P + 0x10 + off) = cr;
        k = *(u8 *)(Q + 0x20 + i);
        EftPtcl3_SetTexture(cr, *(s32 *)(P + 0x4), k, k + *(s32 *)(P + 0x54));
        EftPtcl3_SetType(*(s32 *)(P + 0x10 + off), 2);
    }
}
