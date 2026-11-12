#include "common.h"

typedef struct { u64 lo, hi; } q128;

extern u8 *func_001F3758(void *a0);
extern s32 func_0020B3D0(s32 a0);
extern s32 BtlScene_IsCharStopped(s32 a0);
extern s32 func_0020AB90(u32 a0);
extern s32 func_00157410(u8 *a0);
extern void func_00126DE0(u8 *a0);
extern s32 func_00208DE8(s32 a0, s32 a1, s32 a2);
extern void EftRay_StartHit(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4);
extern f32 D_003846AC;
extern s32 EftShot_TestBits(s32 arg0, s32 arg1);
extern s32 func_001573F8(s32 a0, s32 a1, u8 *a2);
extern void func_00129C28(q128 *arg0, q128 *arg1);
extern s32 func_0012D3A0(u8 *arg0, s32 arg1, s32 arg2);
extern void Vec3_Scale(u8 *arg0, u8 *arg1, f32 farg0);
extern void func_00152260(s32 arg0, s32 arg1);
extern void func_00151FB0(u8 *arg0);
extern void func_00156A60(s32 arg0, void *arg1, s32 *arg2);
extern s32 func_00152200(u8 *arg0, s32 arg1);
extern s32 func_0020A758(s32 arg0);
extern void func_001574B8(u8 *arg0);
extern void func_00156B70(void *arg0);
extern void func_00152930(u8 *arg0, u8 *arg1);
extern void func_001569D0(u8 *arg0);
extern void BtlTask_SetDead(void *arg0);

void func_00156E78(u8 *task) {
    u8 sp[0x30];
    u8 *shotObj;
    u8 *st;
    u8 *ent;
    u8 *aux;
    s32 obj;
    s32 isAlive;
    s32 advance = 0;
    s32 flags;
    s32 t;

    shotObj = func_001F3758(task);
    st = *(u8 **)(task + 0x38);
    aux = *(u8 **)(shotObj + 0x38);
    ent = *(u8 **)(st + 0xB0);
    obj = func_0020B3D0(*(s32 *)ent);
    if (BtlScene_IsCharStopped(*(s32 *)ent) != 0) {
        return;
    }
    if (func_0020AB90(*(u32 *)ent) != 0 && func_00157410(ent) != 0) {
        *(s32 *)(sp + 0x20) = func_00157410(ent);
        *(s32 *)(sp + 0x24) = *(s32 *)ent;
        *(s32 *)(sp + 0x28) = **(s32 **)(ent + 0x20);
        __builtin_memcpy(sp + 0x10, sp + 0x20, 8);
        *(s32 *)(sp + 0x18) = *(s32 *)(sp + 0x28);
        func_00126DE0(sp + 0x10);
        *(s32 *)st |= 0x40;
    }
    flags = *(s32 *)st;
    if (flags & 0x40) {
        *(s32 *)(st + 0x14) += 1;
    }
    if (*(s32 *)(st + 0x14) == 0x125 && !(flags & 0x100)) {
        func_00208DE8(obj, (s32)sp, 3);
        EftRay_StartHit(obj, (s32)sp, 0, 0, D_003846AC);
        *(s32 *)st |= 0x100;
    }
    switch (task[1]) {
    case 0:
        if (EftShot_TestBits(*(s32 *)ent, 2) != 0) {
            t = func_001573F8(*(s32 *)ent, 2, ent);
            *(s32 *)(st + 4) = t;
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
        func_00208DE8(*(s32 *)ent, (s32)sp, *(s32 *)(st + 4));
        func_00129C28((q128 *)(st + 0x40), (q128 *)sp);
        if (EftShot_TestBits(*(s32 *)ent, 0x40) != 0) {
            t = func_001573F8(*(s32 *)ent, 0x40, ent);
            *(s32 *)(st + 0xC) = t;
            func_00208DE8(*(s32 *)ent, (s32)sp, t);
            func_00129C28((q128 *)(st + 0x60), (q128 *)sp);
            *(s32 *)st |= 0x10;
        }
        if (EftShot_TestBits(*(s32 *)ent, 4) != 0) {
            t = func_001573F8(*(s32 *)ent, 4, ent);
            *(s32 *)(st + 8) = t;
            func_00208DE8(*(s32 *)ent, (s32)sp, t);
            func_00129C28((q128 *)(st + 0x50), (q128 *)sp);
            func_00129C28((q128 *)(st + 0x70), (q128 *)(st + 0x50));
            func_00129C28((q128 *)(st + 0x80), (q128 *)(st + 0x70));
            func_00129C28((q128 *)(st + 0x90), (q128 *)(st + 0x80));
            func_0012D3A0(st + 0x30, (s32)(st + 0x80), *(s32 *)ent);
            Vec3_Scale(st + 0xA0, st + 0x30, *(f32 *)(st + 0x18));
            *(s32 *)st |= 0x80;
            task[1] = 3;
        }
        break;
    default:
        break;
    }
    if (EftShot_TestBits(*(s32 *)ent, 0x20) != 0) {
        func_00208DE8(*(s32 *)ent, (s32)(st + 0x80), 0x1F);
    }
    if (EftShot_TestBits(*(s32 *)ent, 0x80) != 0) {
        *(s32 *)st |= 5;
    }
    func_00152260(*(s32 *)ent, (s32)(st + 0x860));
    func_00151FB0(st + 0xB4);
    func_00156A60(*(s32 *)ent, task, (s32 *)aux);
    isAlive = func_00152200(aux, (s32)(st + 0xB4)) != 0;
    if (func_0020A758(*(s32 *)ent) != 0) {
        func_001574B8(task);
        func_00156B70(task);
    }
    if (advance) {
        task[1] += 1;
    }
    flags = *(s32 *)st;
    if ((*(s32 *)(*(u8 **)(ent + 0x20) + 0x30) & 1) && (flags & 0x80)) {
        func_00152930(aux, st + 0xB4);
        func_001569D0(task);
        flags = *(s32 *)st;
    }
    if (!isAlive && (flags & 2)) {
        BtlTask_SetDead(task);
        return;
    }
    if (flags & 1) {
        *(s32 *)st = flags | 2;
    }
}
