#include "common.h"

typedef struct { u64 lo, hi; } q128;

extern u64 D_0036E300[4];

s32 func_001F3758(void *a0);
void func_00152530(s32 arg0, s32 arg1);
s32 BtlScene_IsCharStopped(s32 arg0);
s32 EftShot_TestBits(s32 arg0, s32 arg1);
s32 func_00208DE8(s32 a0, s32 a1, s32 a2);
s32 func_0012D3A0(u8 *arg0, s32 arg1, s32 arg2);
f32 func_0020A068(s32 arg0);
void func_00129C28(q128 *arg0, q128 *arg1);
s32 func_0020B498(u32 arg0);
void Vec4_Sub(u8 *arg0, u8 *arg1, u8 *arg2);
void Vec3_Normalize(u8 *arg0, u8 *arg1);
void Vec3_Scale(u8 *arg0, u8 *arg1, f32 farg0);
s32 func_0020A758(s32 arg0);
s32 func_0020B3D0(u32 arg0);
void func_001DBF28();
void func_0019F8D0();
void func_00151FB0(u8 *arg0);
void func_0015CE78(s32 arg0, u8 *arg1, s32 *arg2, s32 arg3);
s32 func_0020AB90(u32 arg0);
void func_00126DE0(u8 *arg0);
s32 func_00152200(u8 *arg0, s32 arg1);
s32 BtlTask_SetDead(s32 arg0);
void func_00152930(s32 arg0, s32 arg1);
void func_0015CCB0(u8 *arg0);

#define P(x) ((s32)(u32)(x))

void func_0015D0C8(u8 *task) {
    q128 vec = {0, 0};
    s32 hit[3];
    s32 ev[12];
    u64 col[4];
    s32 advance = 0;
    u8 *world = (u8 *)(u32)func_001F3758(task);
    u8 *st = *(u8 **)(task + 0x38);
    s32 *obj = *(s32 **)(st + 0xB0);
    u8 *gs = *(u8 **)(world + 0x38);
    u8 *base;
    s32 hitGround, i, v;
    f32 f;
    u32 flags;

    if (BtlScene_IsCharStopped(obj[0]) != 0) {
        return;
    }
    func_00152530(P(obj), P(st + 0x860));
    if ((*(u32 *)st & 0x80) == 0) {
        if (EftShot_TestBits(obj[0], 2) != 0) {
            task[1] = 0;
            *(u32 *)st |= 0x80;
        } else if (EftShot_TestBits(obj[0], 4) != 0) {
            task[1] = 2;
            *(u32 *)st |= 0x80;
        }
    }
    if ((*(u32 *)st & 0x80) != 0) {
        switch (task[1]) {
        case 0:
            if (EftShot_TestBits(obj[0], 2) != 0) {
                *(s32 *)(st + 4) = *(s32 *)(st + 0x870);
                func_00208DE8(obj[0], P(st + 0x40), *(s32 *)(st + 4));
                func_0012D3A0(st + 0x30, P(st + 0x40), obj[0]);
                task[1] = 1;
            }
            break;
        case 1:
        case 3:
        case 5:
            advance = 1;
            break;
        case 2:
            f = func_0020A068(obj[0]);
            *(f32 *)(st + 0x24) = f;
            *(f32 *)(st + 0x1C) = *(f32 *)(st + 0x18) * (f * 0.5f + 1.0f);
            func_00208DE8(obj[0], P(st + 0x40), *(s32 *)(st + 4));
            if (EftShot_TestBits(obj[0], 0x40) != 0) {
                *(s32 *)(st + 0xC) = *(s32 *)(st + 0x9B0);
                func_00208DE8(obj[0], P(st + 0x60), *(s32 *)(st + 0xC));
                *(u32 *)st |= 0x40;
            }
            if (EftShot_TestBits(obj[0], 4) != 0) {
                *(u32 *)st |= 0x10;
                *(s32 *)(st + 8) = *(s32 *)(st + 0x8B0);
                func_00208DE8(obj[0], P(st + 0x50), *(s32 *)(st + 8));
                func_00129C28((q128 *)(st + 0x70), (q128 *)(st + 0x50));
                func_00129C28((q128 *)(st + 0x80), (q128 *)(st + 0x70));
                func_00208DE8(obj[0], P(st + 0x90), 0x11);
                v = func_0020B498(obj[0]);
                func_00208DE8(v, P(&vec), 0x2E);
                Vec4_Sub(st + 0x30, (u8 *)&vec, st + 0x80);
                Vec3_Normalize(st + 0x30, st + 0x30);
                Vec3_Scale(st + 0xA0, st + 0x30, *(f32 *)(st + 0x14));
                task[1] = 3;
            }
            break;
        case 4:
            func_00129C28((q128 *)(st + 0x90), (q128 *)(st + 0x80));
            func_00208DE8(obj[0], P(st + 0x80), 0x36);
            func_00208DE8(obj[0], P(st + 0x50), *(s32 *)(st + 8));
            if (EftShot_TestBits(obj[0], 8) != 0) {
                *(u32 *)st |= 9;
                task[1] = 5;
            }
            break;
        default:
            break;
        }
    }

    if (func_0020A758(obj[0]) != 0) {
        v = func_0020B3D0(obj[0]);
        if (EftShot_TestBits(v, 0x40) != 0) {
            *(f32 *)&ev[0] = *(f32 *)(st + 0x80);
            *(f32 *)&ev[1] = *(f32 *)(st + 0x84);
            *(f32 *)&ev[2] = *(f32 *)(st + 0x88);
            *(f32 *)&ev[3] = 1.0f;
            ev[4] = obj[0];
            ev[5] = 0x24;
            ev[6] = 1;
            ev[7] = 1;
            ev[8] = 0;
            ev[9] = 0;
            ev[10] = 0;
            ev[11] = 0;
            for (i = 0; i < 4; i++) {
                col[i] = D_0036E300[i];
            }
            func_001DBF28(ev);
            ev[8] = 3;
            ev[5] = 0x11;
            func_001DBF28(ev);
            func_0019F8D0(col);
        }
    }
    if (EftShot_TestBits(obj[0], 0x80) != 0) {
        flags = *(u32 *)st;
        if ((flags & 8) == 0) {
            *(u32 *)st = flags | 4;
        }
        *(u32 *)st |= 1;
    }
    base = st + 0xB4;
    func_00151FB0(base);
    func_0015CE78(obj[0], task, (s32 *)gs, 0);
    if (func_0020AB90(obj[0]) != 0 && (*(u32 *)st & 0x400) == 0) {
        hit[0] = *(s32 *)(gs + 0x1E80);
        hit[1] = obj[0];
        hit[2] = **(s32 **)(obj + 8);
        func_00126DE0((u8 *)hit);
        *(u32 *)st |= 0x400;
    }
    hitGround = func_00152200(gs, P(base)) != 0;
    if (advance != 0) {
        task[1]++;
    }
    flags = *(u32 *)st;
    if (hitGround == 0 && (flags & 2) != 0) {
        BtlTask_SetDead(P(task));
        return;
    }
    if ((flags & 1) != 0) {
        *(u32 *)st = flags | 2;
    } else if ((*(u32 *)(*(u8 **)(obj + 8) + 0x30) & 1) != 0 && (flags & 0x10) != 0) {
        func_00152930(P(gs), P(base));
        func_0015CCB0(task);
    }
}
