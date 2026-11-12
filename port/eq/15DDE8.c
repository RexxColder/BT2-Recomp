#include "common.h"

s32 func_001F3758(s32 arg0);
s32 BtlScene_IsCharStopped(s32 arg0);
void func_0019D6B8(u8 *arg0, s32 arg1);
void func_00152530(u8 *arg0, u8 *arg1);
s32 EftShot_TestBits(s32 arg0, s32 arg1);
void func_00208DE8(s32 arg0, void *arg1, s32 arg2);
void func_00129C28(void *arg0, void *arg1);
s32 func_0012D488(u8 *arg0, u8 *arg1, u8 *arg2, s32 arg3);
s32 func_0012D3A0(u8 *arg0, u8 *arg1, s32 arg2);
f32 func_0020A068(s32 arg0);
s32 func_0015DAE0(u8 *obj, s32 idx);
s32 func_0019D808(u8 *arg0);
void func_0019D6E8(u8 *arg0);
void func_00151FB0(u8 *arg0);
void func_0015D988(s32 arg0, u8 *arg1, s32 *arg2, s32 arg3);
s32 func_00152200(u8 *arg0, u8 *arg1);
extern void BtlTask_SetDead(void *arg0);
void func_00152930(u8 *arg0, u8 *arg1);
void func_0015D7C0(u8 *arg0);

#define FP(p, o) (*(f32 *)((p) + (o)))
#define PP(p, o) (*(u8 **)((p) + (o)))

void func_0015DDE8(u8 *task) {
    u8 tmp[0x10];
    u8 *st;
    u8 *ch;
    u8 *e;
    s32 ctx;
    s32 passThrough;
    s32 i;
    s32 id;
    s32 flags;
    f32 f;

    passThrough = 0;
    ctx = *(s32 *)(func_001F3758((s32)task) + 0x38);
    st = PP(task, 0x38);
    ch = PP(st, 0xC0);
    if (BtlScene_IsCharStopped(*(s32 *)ch)) {
        return;
    }
    for (i = 0; i < *(s32 *)(st + 0x14); i++) {
        func_0019D6B8(PP(st, 0xAC0 + i * 4), 0);
    }
    func_00152530(ch, st + 0x870);

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
                id = *(s32 *)(st + 0x880);
                *(s32 *)(st + 4) = id;
                func_00208DE8(*(s32 *)ch, tmp, id);
                func_00129C28(st + 0x40, tmp);
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
            f = func_0020A068(*(s32 *)ch);
            FP(st, 0x24) = f;
            FP(st, 0x20) = FP(st, 0x1C) * (f + 1.0f);
            func_00208DE8(*(s32 *)ch, tmp, *(s32 *)(st + 4));
            func_00129C28(st + 0x40, tmp);
            if (EftShot_TestBits(*(s32 *)ch, 0x40)) {
                func_00208DE8(*(s32 *)ch, st + 0x60, 0x15);
            }
            if (EftShot_TestBits(*(s32 *)ch, 4)) {
                id = *(s32 *)(st + 0x8C0);
                *(s32 *)(st + 8) = id;
                func_00208DE8(*(s32 *)ch, tmp, id);
                func_00129C28(st + 0x50, tmp);
                func_00129C28(st + 0x80, st + 0x50);
                func_00129C28(st + 0x90, st + 0x80);
                func_00208DE8(*(s32 *)ch, st + 0xA0, 0x11);
                func_0012D488(ch, st + 0x30, st + 0x90, *(s32 *)ch);
                func_00129C28(st + 0xB0, st + 0x30);
                func_00208DE8(*(s32 *)ch, st + 0x70, 0x15);
                func_0015DAE0(task, *(s32 *)(st + 0x10));
                *(s32 *)(st + 0x10) += 1;
                if (!(*(s32 *)(st + 0x10) < *(s32 *)(st + 0x14))) {
                    task[1] = 3;
                }
            }
            break;
        case 4:
            if (EftShot_TestBits(*(s32 *)ch, 8)) {
                *(u32 *)st |= 9;
                task[1] = 5;
            }
            for (i = 0; i < *(s32 *)(st + 0x14); i++) {
                if (func_0019D808(PP(st, 0xAC0 + i * 4))) {
                    break;
                }
            }
            *(u32 *)st |= 9;
            task[1] = 5;
            break;
        default:
            break;
        }
    }

    if (EftShot_TestBits(*(s32 *)ch, 0x80)) {
        flags = *(s32 *)st;
        if (!(flags & 8)) {
            *(s32 *)st = flags | 4;
            for (i = 0; i < *(s32 *)(st + 0x14); i++) {
                func_0019D6E8(PP(st, 0xAC0 + i * 4));
            }
        }
        *(u32 *)st |= 1;
    }
    e = st + 0xC4;
    func_00151FB0(e);
    func_0015D988(*(s32 *)ch, task, (s32 *)ctx, 0);
    i = func_00152200((u8 *)ctx, e) != 0;
    if (passThrough) {
        task[1] += 1;
    }
    flags = *(s32 *)st;
    if (!i) {
        if (flags & 2) {
            BtlTask_SetDead(task);
            return;
        }
    }
    if (flags & 1) {
        *(s32 *)st = flags | 2;
    } else if ((*(u32 *)(PP(ch, 0x20) + 0x30) & 1) && (flags & 0x10)) {
        func_00152930((u8 *)ctx, e);
        func_0015D7C0(task);
    }
}
