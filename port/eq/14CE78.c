#include "common.h"

s32 func_001F3758(s32 arg0);
s32 BtlScene_IsCharStopped(s32 arg0);
void func_00152530(u8 *arg0, u8 *arg1);
s32 EftShot_TestBits(s32 arg0, s32 arg1);
void func_00208DE8(s32 arg0, void *arg1, s32 arg2);
void func_00129C28(void *arg0, void *arg1);
s32 func_0012D3A0(u8 *arg0, u8 *arg1, s32 arg2);
s32 func_0012D488(u8 *arg0, u8 *arg1, u8 *arg2, s32 arg3);
void func_0012D5D8(u8 *arg0, u8 *arg1, u8 *arg2, s32 arg3, f32 farg0, f32 farg1);
void Vec3_Scale(u8 *arg0, u8 *arg1, f32 farg0);
void Vec3_Add(void *arg0, void *arg1, void *arg2);
void func_0014C580(u8 *task);
s32 func_00182B10(s32 arg0);
void func_00182AB8(s32 arg0);
void func_00151FB0(u8 *arg0);
void func_0014C398(s32 arg0, u8 *task, void *arg2, s32 arg3);
s32 func_00152200(u8 *arg0, u8 *arg1);
extern void BtlTask_SetDead(void *arg0);

#define FP(p, o) (*(f32 *)((p) + (o)))
#define PP(p, o) (*(u8 **)((p) + (o)))

void func_0014CE78(u8 *task) {
    u8 *st;
    u8 *ch;
    u8 *e;
    u8 *prm;
    s32 ctx;
    s32 passThrough;
    s32 i;
    s32 id;
    s32 cnt;
    u32 flags;

    passThrough = 0;
    ctx = *(s32 *)(func_001F3758((s32)task) + 0x38);
    st = PP(task, 0x38);
    ch = PP(st, 0xB0);
    if (BtlScene_IsCharStopped(*(s32 *)ch)) {
        return;
    }
    func_00152530(ch, st + 0x860);

    if (!(*(u32 *)st & 0x80)) {
        if (EftShot_TestBits(*(s32 *)ch, 2)) {
            task[1] = 0;
        } else {
            if (EftShot_TestBits(*(s32 *)ch, 4)) {
                task[1] = 2;
            } else {
                goto after_state;
            }
        }
        *(u32 *)st |= 0x80;
    }
after_state:
    if (*(u32 *)st & 0x80) {
        switch (task[1]) {
        case 0:
            if (EftShot_TestBits(*(s32 *)ch, 2)) {
                id = *(s32 *)(st + 0x870);
                *(s32 *)(st + 4) = id;
                func_00208DE8(*(s32 *)ch, st + 0x40, id);
                func_0012D3A0(st + 0x30, st + 0x40, *(s32 *)ch);
                task[1] = 1;
            }
            break;
        case 1:
        case 3:
        case 5:
            passThrough = 1;
            break;
        case 2:
            func_00208DE8(*(s32 *)ch, st + 0x40, *(s32 *)(st + 4));
            if (EftShot_TestBits(*(s32 *)ch, 0x40)) {
                id = *(s32 *)(st + 0x9B0);
                *(s32 *)(st + 0xC) = id;
                func_00208DE8(*(s32 *)ch, st + 0x60, id);
                *(u32 *)st |= 0x40;
            }
            if (EftShot_TestBits(*(s32 *)ch, 4)) {
                id = *(s32 *)(st + 0x8B0);
                *(s32 *)(st + 8) = id;
                func_00208DE8(*(s32 *)ch, st + 0x50, id);
                func_00129C28(st + 0x70, st + 0x50);
                func_00129C28(st + 0x80, st + 0x70);
                func_00208DE8(*(s32 *)ch, st + 0x90, 0x11);
                func_0012D488(ch, st + 0x30, st + 0x80, *(s32 *)ch);
                Vec3_Scale(st + 0xA0, st + 0x30, FP(st, 0x10));
                task[1] = 3;
            }
            break;
        case 4:
            func_00129C28(st + 0x90, st + 0x80);
            prm = PP(PP(st, 0xB0), 0x20);
            if (!(*(u32 *)(prm + 0x30) & 2) && !(*(u32 *)st & 0x20)) {
                if (0.0f < FP(prm, 0x18)) {
                    func_0012D5D8(st + 0x30, st + 0x80, st + 0x30, *(s32 *)ch, FP(st, 0x10), FP(prm, 0x18));
                    Vec3_Scale(st + 0xA0, st + 0x30, FP(st, 0x10));
                }
                Vec3_Add(st + 0x80, st + 0x80, st + 0xA0);
            }
            func_00208DE8(*(s32 *)ch, st + 0x50, *(s32 *)(st + 8));
            if (EftShot_TestBits(*(s32 *)ch, 8)) {
                task[1] = 5;
            }
            break;
        default:
            break;
        }
        if (EftShot_TestBits(*(s32 *)ch, 4)) {
            func_0014C580(task);
        }
    }

    cnt = *(s32 *)(st + 0xB14);
    if (cnt != 0) {
        if (*(s16 *)(PP(ch, 0x20) + 0x34) == cnt) {
            for (i = 0; i < *(s32 *)(st + 0xB14); i++) {
                if (*(s32 *)(st + 0xAB0 + i * 4) != 0) {
                    if (func_00182B10(*(s32 *)(st + 0xAB0 + i * 4))) {
                        func_00182AB8(*(s32 *)(st + 0xAB0 + i * 4));
                        *(s32 *)(st + 0xAB0 + i * 4) = 0;
                        *(s32 *)(st + 0xB10) -= 1;
                    }
                }
            }
            if (*(s32 *)(st + 0xB10) == 0) {
                *(u32 *)st |= 0x209;
            }
        }
    }

    if (EftShot_TestBits(*(s32 *)ch, 0x80)) {
        flags = *(u32 *)st;
        if (!(flags & 8)) {
            flags |= 0x204;
            *(u32 *)st = flags;
        }
        *(u32 *)st = flags | 1;
    }
    e = st + 0xB4;
    func_00151FB0(e);
    func_0014C398(*(s32 *)ch, task, (void *)ctx, 0);
    i = func_00152200((u8 *)ctx, e) != 0;
    if (passThrough) {
        task[1] += 1;
    }
    if (!i) {
        if (*(u32 *)st & 2) {
            BtlTask_SetDead(task);
            return;
        }
    }
    if ((*(u32 *)st & 0x201) == 0x201) {
        *(u32 *)st |= 2;
    }
}
