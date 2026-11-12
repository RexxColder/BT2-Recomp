#include "common.h"

typedef struct { u64 lo, hi; } q128;

extern u8 *func_001F3758(void *a0);
extern s32 BtlScene_IsCharStopped(s32 a0);
extern void func_00152530(u8 *arg0, u8 *arg1);
extern s32 EftShot_TestBits(s32 arg0, s32 arg1);
extern s32 func_00208DE8(s32 a0, s32 a1, s32 a2);
extern void func_00129C28(q128 *arg0, q128 *arg1);
extern s32 func_0012D3A0(u8 *arg0, s32 arg1, s32 arg2);
extern s32 func_0012D488(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3);
extern void func_0012D5D8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 farg0, f32 farg1);
extern void Vec3_Scale(u8 *arg0, u8 *arg1, f32 farg0);
extern void Vec3_Add(void *arg0, void *arg1, void *arg2);
extern void func_00151FB0(u8 *arg0);
extern void func_00171B38(s32 arg0, u8 *arg1, u8 *arg2);
extern s32 func_00152200(u8 *arg0, s32 arg1);
extern void func_00152930(u8 *arg0, u8 *arg1);
extern void func_00171970(void *arg0);
extern void BtlTask_SetDead(void *arg0);

void func_00171DF8(u8 *task) {
    u8 sp[0x10];
    u8 *shotObj;
    u8 *st;
    u8 *ent;
    u8 *aux;
    s32 advance = 0;
    s32 alive;
    s32 flags;
    s32 t;

    shotObj = func_001F3758(task);
    st = *(u8 **)(task + 0x38);
    aux = *(u8 **)(shotObj + 0x38);
    ent = *(u8 **)(st + 0xB0);
    if (BtlScene_IsCharStopped(*(s32 *)ent) != 0) {
        return;
    }
    func_00152530(ent, st + 0x860);
    if (!(*(s32 *)st & 0x80)) {
        if (EftShot_TestBits(*(s32 *)ent, 2) != 0) {
            task[1] = 0;
            *(s32 *)st |= 0x80;
        } else if (EftShot_TestBits(*(s32 *)ent, 4) != 0) {
            task[1] = 2;
            *(s32 *)st |= 0x80;
        }
    }
    if (*(s32 *)st & 0x80) {
        switch (task[1]) {
        case 0:
            if (EftShot_TestBits(*(s32 *)ent, 2) != 0) {
                t = *(s32 *)(st + 0x870);
                *(s32 *)(st + 0xC) = t;
                func_00208DE8(*(s32 *)ent, (s32)sp, t);
                func_00129C28((q128 *)(st + 0x40), (q128 *)sp);
                func_0012D3A0(st + 0x30, (s32)(st + 0x40), *(s32 *)ent);
                task[1] = 1;
            }
            break;
        case 1:
        case 3:
        case 5:
            advance = 1;
            break;
        case 2:
            func_00208DE8(*(s32 *)ent, (s32)sp, *(s32 *)(st + 0xC));
            func_00129C28((q128 *)(st + 0x40), (q128 *)sp);
            if (EftShot_TestBits(*(s32 *)ent, 0x40) != 0) {
                t = *(s32 *)(st + 0x9B0);
                *(s32 *)(st + 0x14) = t;
                func_00208DE8(*(s32 *)ent, (s32)sp, t);
                func_00129C28((q128 *)(st + 0x60), (q128 *)sp);
                *(s32 *)st |= 0x40;
            }
            if (EftShot_TestBits(*(s32 *)ent, 4) != 0) {
                t = *(s32 *)(st + 0x8B0);
                *(s32 *)st |= 0x10;
                *(s32 *)(st + 0x10) = t;
                func_00208DE8(*(s32 *)ent, (s32)sp, t);
                func_00129C28((q128 *)(st + 0x50), (q128 *)sp);
                func_00129C28((q128 *)(st + 0x70), (q128 *)(st + 0x50));
                func_00129C28((q128 *)(st + 0x80), (q128 *)(st + 0x70));
                func_00129C28((q128 *)(st + 0x90), (q128 *)(st + 0x80));
                func_0012D488(ent, st + 0x30, (s32)(st + 0x80), *(s32 *)ent);
                Vec3_Scale(st + 0xA0, st + 0x30, *(f32 *)(st + 0x18));
                task[1] = 3;
            }
            break;
        case 4:
            func_00129C28((q128 *)(st + 0x90), (q128 *)(st + 0x80));
            if (!(*(s32 *)(*(u8 **)(*(u8 **)(st + 0xB0) + 0x20) + 0x30) & 2) && !(*(s32 *)st & 0x20)) {
                f32 spd = *(f32 *)(*(u8 **)(ent + 0x20) + 0x18);
                if (0.0f < spd) {
                    func_0012D5D8((s32)(st + 0x30), (s32)(st + 0x80), (s32)(st + 0x30), *(s32 *)ent,
                                  *(f32 *)(st + 0x18), spd);
                    Vec3_Scale(st + 0xA0, st + 0x30, *(f32 *)(st + 0x18));
                }
                Vec3_Add(st + 0x80, st + 0x80, st + 0xA0);
            }
            func_00208DE8(*(s32 *)ent, (s32)sp, *(s32 *)(st + 0x10));
            func_00129C28((q128 *)(st + 0x50), (q128 *)sp);
            if (EftShot_TestBits(*(s32 *)ent, 8) != 0) {
                *(s32 *)st |= 0x109;
                task[1] = 5;
            }
            break;
        default:
            break;
        }
    }
    if (EftShot_TestBits(*(s32 *)ent, 0x80) != 0) {
        flags = *(s32 *)st;
        if (!(flags & 8)) {
            flags |= 4;
        }
        *(s32 *)st = flags | 0x100;
    }
    func_00151FB0(st + 0xB4);
    func_00171B38(*(s32 *)ent, task, aux);
    alive = func_00152200(aux, (s32)(st + 0xB4)) != 0;
    if (advance) {
        task[1] += 1;
    }
    flags = *(s32 *)st;
    if (!alive && (flags & 2)) {
        BtlTask_SetDead(task);
        return;
    }
    if (flags & 0x100) {
        *(s32 *)st = flags | 2;
    } else if ((*(s32 *)(*(u8 **)(ent + 0x20) + 0x30) & 1) && (flags & 0x10)) {
        func_00152930(aux, st + 0xB4);
        func_00171970(task);
    }
}
