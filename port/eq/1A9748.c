#include "common.h"

#define W(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define F(p, o) (*(f32 *)((u8 *)(p) + (o)))

extern u8 *D_00387840;
extern f32 D_00384ED8;

extern s32 BtlScene_IsCharStopped(s32 arg0);
extern s32 func_00208DE8(s32 a0, u8 *a1, s32 a2);
extern void func_00129C28(u8 *dst, u8 *src);
extern void func_0018E1A8(s32 task, u8 *pos);
extern void EftPtcl3_SetPos(s32 task, u8 *pos);
extern void func_001E7238(u8 *p, u8 *pos);
extern void EftChain2_SetPos(s32 task, u8 *pos);
extern s32 func_001A9050(s32 a0);
extern void Vec4_Set(u8 *dst, f32 x, f32 y, f32 z, f32 w);
extern s32 EftQuad_Create(u8 *arg);
extern void func_0018E5E0(s32 task, s32 type);
extern s32 EftPtcl3_Create(u8 *arg);
extern void EftPtcl3_SetType(s32 task, s32 type);
extern void func_001E70B0(f32 f12, u8 *a0, s32 a1, s32 a2, s32 a3, s32 t0, u8 *t1, u8 *t2, s32 t3);
extern void func_001E7208(u8 *p, s32 a1);
extern void func_0027BCC0(s32 a0, u8 *a1, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16);
extern void func_001A90A0(u8 *obj);
extern s32 func_001E7178(u8 *p);
extern s32 func_001A9000(s32 a0);
extern s32 BtlTask_SetDead(u8 *obj);

/* Effect task update: tracks several sub-effects (particles, quads, chain) at the owner position, creates the
   quad + 2 particle emitters + 1 emitter once (st[1] bit 4), and sets the dead flag when everything is gone. */
void func_001A9748(u8 *obj) {
    u8 sp[0x60];
    u8 q[0x40];
    u8 pp[0x50];
    u8 *gtab;
    u8 *st;
    u8 *tab;
    u8 *rec;
    u8 *pos;
    u8 *arr1;
    u8 *emit;
    s32 aliveAny = 0;
    s32 flags;
    s32 i;
    s32 task;

    gtab = D_00387840 + 8;
    st = *(u8 **)(obj + 0x38);
    tab = *(u8 **)gtab;
    if (BtlScene_IsCharStopped(W(st, 0))) {
        flags = W(st, 4);
    } else {
        rec = gtab + W(st, 8) * 0x840 + 8;
        pos = st + 0x10;
        func_00208DE8(W(st, 0), pos, 3);
        func_00208DE8(W(st, 0), st + 0x20, 0);

        for (i = 0; i < 2; i++) {
            func_00129C28(sp, pos);
            F(sp, 4) = F(sp, 4) + F(tab, 0x34 + i * 4) * F(st, 0xC);
            func_0018E1A8(W(st, 0x30 + i * 4), sp);
        }
        for (i = 0; i < 3; i++) {
            func_00129C28(sp, pos);
            F(sp, 4) = F(sp, 4) + F(tab, 0x24 + i * 4) * F(st, 0xC);
            EftPtcl3_SetPos(W(st, 0x38 + i * 4), sp);
        }
        func_00129C28(sp, pos);
        F(sp, 4) = F(sp, 4) + F(tab, 0x3C) * F(st, 0xC);
        func_001E7238(st + 0x4C, sp);
        if (W(st, 8) == 1) {
            func_00129C28(sp, pos);
            F(sp, 4) = F(sp, 4) + F(tab, 0x48) * F(st, 0xC);
            EftChain2_SetPos(W(st, 0x54), sp);
        }

        if (func_001A9050(W(st, 0)) == 1) {
            flags = W(st, 4);
            if (!(flags & 4)) {
                arr1 = rec + 0x1C8;
                emit = st + 8;

                /* quad argument block */
                for (i = 0; i < 0x40; i++) {
                    q[i] = 0;
                }
                W(q, 0x00) = W(rec, 0x98) + 0xB4;
                W(q, 0x04) = W(rec, 0x9C) + 0x40;
                *(u8 **)(q + 0x08) = rec + 8;
                F(q, 0x30) = F(st, 0xC);
                F(q, 0x34) = F(tab, 8);
                W(q, 0x38) = W(st, 0);
                Vec4_Set(q + 0x20, 0.0f, 1.0f, 0.0f, 1.0f);
                func_00129C28(q + 0x10, pos);
                F(q, 0x14) = F(q, 0x14) + F(tab, 0x38) * F(st, 0xC);
                task = EftQuad_Create(q);
                W(st, 0x34) = task;
                func_0018E5E0(task, 2);

                /* first particle emitter */
                for (i = 0; i < 0x50; i++) {
                    pp[i] = 0;
                }
                F(pp, 0x00) = F(tab, 0xC);
                F(pp, 0x04) = F(st, 0xC);
                W(pp, 0x30) = 3;
                *(u8 **)(pp + 0x34) = arr1;
                W(pp, 0x38) = W(rec, 0x2D8) + 0x42C;
                W(pp, 0x3C) = W(rec, 0x2DC) + 0xF0;
                W(pp, 0x40) = W(st, 0);
                func_00129C28(pp + 0x10, pos);
                F(pp, 0x14) = F(pp, 0x14) + F(tab, 0x30) * F(st, 0xC);
                Vec4_Set(pp + 0x20, 0.0f, -1.0f, 0.0f, 1.0f);
                task = EftPtcl3_Create(pp);
                W(emit, 0x3C) = task;
                EftPtcl3_SetType(task, 2);
                W(emit, 0x3C) = 0;

                /* second particle emitter */
                for (i = 0; i < 0x50; i++) {
                    pp[i] = 0;
                }
                F(pp, 0x00) = F(tab, 0x20);
                F(pp, 0x04) = F(st, 0xC);
                W(pp, 0x30) = 4;
                *(u8 **)(pp + 0x34) = arr1;
                W(pp, 0x38) = W(rec, 0x2D8) + 0x590;
                W(pp, 0x3C) = W(rec, 0x2DC) + 0x140;
                W(pp, 0x40) = W(st, 0);
                func_00129C28(pp + 0x10, pos);
                F(pp, 0x14) = F(pp, 0x14) + F(tab, 0x4C) * F(st, 0xC);
                Vec4_Set(pp + 0x20, 0.0f, -1.0f, 0.0f, 1.0f);
                task = EftPtcl3_Create(pp);
                W(emit, 0x40) = task;
                EftPtcl3_SetType(task, 2);
                W(emit, 0x40) = 0;

                /* sprite effect at st+0x50 */
                func_00129C28(sp + 0x50, pos);
                F(sp, 0x54) = F(sp, 0x54) + F(tab, 0x14) * F(st, 0xC);
                func_001E70B0(F(tab, 0x10) * F(st, 0xC), st + 0x50, W(rec, 0x714), 0, 0, 0, sp + 0x50, rec + 0x500, W(st, 0));
                func_001E7208(st + 0x50, 2);
                func_0027BCC0(W(st, 0), pos, D_00384ED8, 10.0f, 50.0f, 10.0f, 0.5f);
                func_001A90A0(obj);
                flags = W(st, 4);
            }
            W(st, 4) = flags | 4;
        }

        for (i = 0; i < 2; i++) {
            if (func_001E7178(st + 0x4C + i * 4)) {
                aliveAny = 1;
            }
        }
        if (func_001A9000(W(st, 0))) {
            flags = W(st, 4);
        } else {
            flags = W(st, 4);
            if (!(flags & 1)) {
                func_001A90A0(obj);
                W(st, 4) = W(st, 4) | 1;
                flags = W(st, 4);
            }
            if (!aliveAny) {
                W(st, 4) = flags | 2;
                flags = flags | 2;
            }
        }
    }
    if (flags & 2) {
        BtlTask_SetDead(obj);
    }
}
