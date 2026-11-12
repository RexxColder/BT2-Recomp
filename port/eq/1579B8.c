#include "common.h"

typedef struct { u64 lo, hi; } q128;

s32 func_001F3758(void *a0);
s32 func_001582E8(s32 arg0);
s32 func_00158048(s32 arg0, s32 arg1, s32 arg2);
void func_00126DE0(u8 *arg0);
s32 func_0020AB90(u32 arg0);
s32 func_00208DE8(s32 a0, s32 a1, s32 a2);
void func_00129C28(q128 *arg0, q128 *arg1);
s32 func_0012D3A0(u8 *arg0, s32 arg1, s32 arg2);
void Vec3_Scale(u8 *arg0, u8 *arg1, f32 farg0);
void Vec4_Scale(u8 *arg0, u8 *arg1, f32 farg0);
void Vec3_Add(u8 *arg0, u8 *arg1, u8 *arg2);
void func_0020D3B0(s32 arg0, f32 farg0, s32 arg1);
void func_00158108(void *arg0);
s32 func_00158328(s32 arg0);
s32 func_00191728(u8 *arg0);
s32 func_00191688(u8 *arg0);
void func_00152260(s32 arg0, s32 arg1);
void func_00208F18(s32 arg0, s32 arg1, s32 arg2);
void func_001585B0(s32 arg0, s32 arg1, s32 arg2);
void func_00151FB0(u8 *arg0);
void func_00157718(s32 arg0, void *arg1, s32 *arg2);
s32 func_00152200(u8 *arg0, s32 arg1);
void func_00152930(s32 arg0, s32 arg1);
void func_00157688(u8 *arg0);
s32 BtlScene_IsCharStopped(s32 arg0);
s32 EftShot_TestBits(s32 arg0, s32 arg1);
s32 BtlTask_SetDead(s32 arg0);

#define P(x) ((s32)(u32)(x))

void func_001579B8(u8 *task) {
    q128 tmp;
    q128 hit[1];
    q128 vec;
    q128 pa;
    q128 pb;
    q128 pc;
    q128 dir;
    s32 advance = 0;
    s32 aliveFx = 0;
    u8 *world = (u8 *)(u32)func_001F3758(task);
    u8 *st = *(u8 **)(task + 0x38);
    u8 *gs = *(u8 **)(world + 0x38);
    s32 *obj = *(s32 **)(st + 0xA0);
    u8 *base = st + 0x60;
    u8 *slot;
    s32 gotGround, i, v;
    u32 flags;

    if (BtlScene_IsCharStopped(obj[0]) != 0) {
        return;
    }
    if (func_0020AB90(obj[0]) != 0 && func_001582E8(P(obj)) != 0) {
        s32 *h = (s32 *)hit;
        h[0] = func_001582E8(P(obj));
        h[1] = obj[0];
        h[2] = **(s32 **)(obj + 8);
        func_00126DE0((u8 *)hit);
        *(u32 *)st |= 0x40;
    }
    if ((*(u32 *)st & 0x40) != 0) {
        *(s32 *)(st + 0x14) += 1;
    }

    switch (task[1]) {
    case 0:
        if (EftShot_TestBits(obj[0], 2) != 0) {
            v = func_00158048(obj[0], 2, P(obj));
            *(s32 *)(st + 4) = v;
            func_00208DE8(obj[0], P(&tmp), v);
            func_00129C28((q128 *)(st + 0x30), &tmp);
            func_0012D3A0(st + 0x20, P(st + 0x30), obj[0]);
            task[1] = 1;
        }
        break;
    case 1:
    case 3:
    case 5:
        advance = 1;
        break;
    case 2:
        func_00208DE8(obj[0], P(&tmp), *(s32 *)(st + 4));
        func_00129C28((q128 *)(st + 0x30), &tmp);
        if (EftShot_TestBits(obj[0], 0x40) != 0) {
            v = func_00158048(obj[0], 0x40, P(obj));
            *(s32 *)(st + 0xC) = v;
            func_00208DE8(obj[0], P(&tmp), v);
            func_00129C28((q128 *)(st + 0x50), &tmp);
            *(u32 *)st |= 0x10;
        }
        if (EftShot_TestBits(obj[0], 4) != 0) {
            v = func_00158048(obj[0], 4, P(obj));
            *(s32 *)(st + 8) = v;
            func_00208DE8(obj[0], P(&tmp), v);
            func_00129C28((q128 *)(st + 0x40), &tmp);
            func_00129C28((q128 *)(st + 0x60), (q128 *)(st + 0x40));
            func_00129C28((q128 *)(st + 0x70), (q128 *)(st + 0x60));
            func_00129C28((q128 *)(st + 0x80), (q128 *)(st + 0x70));
            func_0012D3A0(st + 0x20, P(st + 0x70), obj[0]);
            Vec3_Scale(st + 0x90, st + 0x20, *(f32 *)(st + 0x18));
            *(u32 *)st |= 0x80;
            task[1] = 3;
        }
        break;
    case 4:
        if ((*(u32 *)(*(u8 **)(obj + 8) + 0x30) & 0x10) != 0) {
            Vec4_Scale((u8 *)&vec, st + 0x20, -1.0f);
            func_0020D3B0(obj[0], 4.0f, P(&vec));
        }
        func_00158108(task);
        break;
    default:
        break;
    }

    if (EftShot_TestBits(obj[0], 4) != 0) {
        func_0012D3A0(st + 0x20, P(base), obj[0]);
        func_00158328(P(task));
    }
    slot = st + 0xF40;
    for (i = 1; i >= 0; i--) {
        if (func_00191728(*(u8 **)(slot + 4)) != 0) {
            aliveFx = 1;
        } else {
            *(u32 *)(slot + 4) = 0;
        }
        slot += 8;
    }
    if (EftShot_TestBits(obj[0], 0x80) != 0) {
        *(u32 *)st |= 5;
        slot = st + 0xF40;
        for (i = 1; i >= 0; i--) {
            func_00191688(*(u8 **)(slot + 4));
            *(u32 *)(slot + 4) = 0;
            slot += 8;
        }
    }
    func_00152260(obj[0], P(st + 0x850));
    func_00208F18(obj[0], P(&dir), 0x31);
    Vec3_Scale((u8 *)&pc, (u8 *)&dir, 1.0f);
    Vec3_Add((u8 *)&pa, base, (u8 *)&pc);
    Vec3_Scale((u8 *)&pc, (u8 *)&dir, -1.0f);
    Vec3_Add((u8 *)&pb, base, (u8 *)&pc);
    func_001585B0(obj[0], P(st + 0xAA0), P(&pa));
    func_001585B0(obj[0], P(st + 0xCF0), P(&pb));
    func_00151FB0(st + 0xA4);
    func_00157718(obj[0], task, (s32 *)gs);
    gotGround = func_00152200(gs, P(st + 0xA4)) != 0;
    if (advance != 0) {
        task[1]++;
    }
    if ((*(u32 *)(*(u8 **)(obj + 8) + 0x30) & 1) != 0 && (*(u32 *)st & 0x80) != 0) {
        func_00152930(P(gs), P(st + 0xA4));
        func_00157688(task);
    }
    flags = *(u32 *)st;
    if (aliveFx == 0 && gotGround == 0 && (flags & 2) != 0) {
        BtlTask_SetDead(P(task));
        return;
    }
    if ((flags & 1) != 0) {
        *(u32 *)st = flags | 2;
    }
}
