#include "common.h"

void *memset(void *arg0, s32 arg1, s32 arg2);
void func_0026FBD0(void *arg0);
void Flash_CxformIdentity(void *arg0);
void func_0026CF60(void *arg0, u8 *arg1, s32 *arg2);
void func_0026CFE0(void *arg0, u8 *arg1, s32 *arg2);
void func_0026C4F8(void *arg0, s32 arg1, void *arg2, void *arg3, s32 arg4);
void func_0026C578(void *arg0, s32 arg1, s32 arg2);
void func_0026C5F0(void *arg0, s32 arg1, void *arg2, void *arg3, void *arg4, s32 arg5);
void func_0026C6F8(void *arg0, void *arg1, void *arg2);

void func_0026D250(u8 *arg0, u8 *arg1, s32 *arg2) {
    u8 fr[0x90];   /* tamano de locales del original (antes 0x88) */
    u8 *s5;
    u8 *s3;
    u8 *s4;
    u8 *tgt;
    s32 a2v;
    s32 v0;
    s32 v1;
    s32 cnt;
    u8 b;
    u8 sp80;
    u16 idx;
    u16 lenv;

    s5 = fr + 0x20;
    s3 = fr + 0x40;
    func_0026FBD0(fr);
    Flash_CxformIdentity(s5);
    memset(s3, 0, 0x40);

    a2v = *arg2;
    sp80 = arg1[a2v];
    *arg2 = a2v + 1;
    fr[0x82] = arg1[a2v + 1];
    fr[0x83] = arg1[a2v + 2];
    *arg2 = a2v + 3;

    if ((sp80 & 2) != 0) {
        fr[0x84] = arg1[a2v + 3];
        *arg2 = a2v + 4;
        fr[0x86] = arg1[a2v + 4];
        fr[0x87] = arg1[a2v + 5];
        *arg2 = a2v + 6;

        if ((sp80 & 4) != 0) {
            func_0026CF60(fr, arg1, arg2);
        }
        if ((sp80 & 8) != 0) {
            func_0026CFE0(s5, arg1, arg2);
        }
        if ((sp80 & 0x20) != 0) {
            v0 = *arg2;
            cnt = 0;
            b = arg1[v0];
            *arg2 = v0 + 1;
            s3[0] = b;
            if (b != 0) {
                do {
                    v0 = *arg2;
                    cnt += 1;
                    b = arg1[v0];
                    *arg2 = v0 + 1;
                    s3[cnt] = b;
                } while (b != 0);
            }
        }

        v1 = fr[0x84];
        idx = (u16)(fr[0x82] | (fr[0x83] << 8));
        lenv = (u16)(fr[0x86] | (fr[0x87] << 8));
        tgt = *(u8 **)(arg0 + 0x14) + (u32)idx * 12 - 12;
        if (v1 == 2) {
            func_0026C578(tgt, lenv, *(s32 *)arg0);
        } else if (v1 < 3) {
            if (v1 == 1) {
                func_0026C4F8(tgt, lenv, fr, s5, *(s32 *)arg0);
            }
        } else {
            if (v1 == 3) {
                func_0026C5F0(tgt, lenv, s3, fr, s5, *(s32 *)arg0);
            }
        }
    } else {
        s3 = NULL;
        s4 = NULL;
        if ((sp80 & 4) != 0) {
            func_0026CF60(fr, arg1, arg2);
            s3 = fr;
        }
        if ((sp80 & 8) != 0) {
            func_0026CFE0(s5, arg1, arg2);
            s4 = s5;
        }
        idx = (u16)(fr[0x82] | (fr[0x83] << 8));
        tgt = *(u8 **)(arg0 + 0x14) + (u32)idx * 12 - 12;
        func_0026C6F8(tgt, s3, s4);
    }
}
