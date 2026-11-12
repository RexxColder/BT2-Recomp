#include "common.h"

s32 func_001F3758(s32 arg0);
s32 BtlScene_IsCharStopped(s32 arg0);
s32 EftShot_TestBits(s32 arg0, s32 arg1);
void func_00151FB0(u8 *arg0);
void func_0015AED0(s32 arg0, void *arg1, s32 *arg2);
s32 func_00152200(s32 arg0, u8 *arg1);
void func_00152530(u8 *arg0, u8 *arg1);
void func_00152930(s32 arg0, void *arg1);
void func_0015AFE0(u8 *arg0);
void func_0015B6D8(void *arg0);
s32 func_0015B6C0(s32 arg0, s32 arg1, s32 *arg2);
void func_00208DE8(s32 arg0, void *arg1, s32 arg2);
void func_0012D3A0(s32 arg0, s32 arg1, s32 arg2);
void func_00129C28(s32 arg0, s32 arg1);
s32 BtlTask_SetDead(s32 arg0);

/* 0x0015B280 (per-task update of an effect shot). The task (a0) holds a state byte at +1 (switch 0..5, jtbl_0036E270)
 * and its sub-record at +0x38 (flags word at +0, the shot table pointer at +0xA0, vectors at +0x20/+0x30/+0x50/+0x870).
 * The shot record (*(sub+0xA0)) is tested for the event bits 2, 0x40, 4, 8 and 0x80; the tail applies the flag bits
 * and may kill the task. */
void func_0015B280(u8 *task) {
    u8 *s1;
    u8 *s2;
    u8 *s5;
    u8 *s0;
    u8 *sh;
    u8 *p20;
    u8 *other;
    f32 sv[4];
    s32 s4;
    s32 s6 = 0;
    s32 v0;
    s32 v1;
    s32 f;

    other = (u8 *)func_001F3758((s32)task);
    s1 = *(u8 **)(task + 0x38);
    s5 = *(u8 **)(other + 0x38);
    s2 = *(u8 **)(s1 + 0xA0);
    sh = *(u8 **)s2;

    if (BtlScene_IsCharStopped((s32)sh) != 0) {
        return;
    }

    s0 = s1 + 0x850;
    func_00152530(s2, s0);
    if ((*(s32 *)s0 & 1) != 0) {
        func_00208DE8((s32)sh, sv, 3);
        *(f32 *)(s1 + 0x870) = sv[0];
        *(f32 *)(s1 + 0x874) = sv[1] - 50.0f;
        *(f32 *)(s1 + 0x878) = sv[2];
    }

    switch (*(u8 *)(task + 1)) {
    case 0:
        if (EftShot_TestBits((s32)sh, 2) != 0) {
            v0 = func_0015B6C0((s32)sh, 2, (s32 *)s2);
            *(s32 *)(s1 + 4) = v0;
            s0 = s1 + 0x30;
            func_00208DE8((s32)sh, sv, v0);
            func_00129C28((s32)(s1 + 0x30), (s32)sv);
            func_0012D3A0((s32)(s1 + 0x20), (s32)(s1 + 0x30), (s32)sh);
            *(u8 *)(task + 1) = 1;
        }
        break;

    case 2:
        func_00208DE8((s32)sh, sv, *(s32 *)(s1 + 4));
        func_00129C28((s32)(s1 + 0x30), (s32)sv);
        if (EftShot_TestBits((s32)sh, 0x40) != 0) {
            v0 = func_0015B6C0((s32)sh, 0x40, (s32 *)s2);
            *(s32 *)(s1 + 0xC) = v0;
            func_00208DE8((s32)sh, sv, v0);
            func_00129C28((s32)(s1 + 0x50), (s32)sv);
            *(s32 *)s1 = *(s32 *)s1 | 0x20;
        }
        if (EftShot_TestBits((s32)sh, 4) != 0) {
            func_0015AFE0(task);
            *(u8 *)(task + 1) = 3;
        }
        break;

    case 4:
        func_0015B6D8(task);
        if (EftShot_TestBits((s32)sh, 8) != 0) {
            *(s32 *)s1 = *(s32 *)s1 | 9;
            *(u8 *)(task + 1) = 5;
        }
        break;

    case 1:
    case 3:
    case 5:
        s6 = 1;
        break;

    default:
        break;
    }

    if (EftShot_TestBits((s32)sh, 0x80) != 0) {
        f = *(s32 *)s1;
        if ((f & 8) == 0) {
            f = f | 4;
        }
        f = f | 1;
        *(s32 *)s1 = f;
        s0 = s1 + 0xA4;
    }

    func_00151FB0(s0);
    func_0015AED0((s32)sh, task, (s32 *)s5);
    s4 = func_00152200((s32)s5, s0) != 0;
    if (s6 != 0) {
        *(u8 *)(task + 1) = *(u8 *)(task + 1) + 1;
    }

    p20 = *(u8 **)(s2 + 0x20);
    v1 = (s32)p20;
    if ((*(s32 *)(p20 + 0x30) & 1) != 0) {
        v1 = *(s32 *)s1;
        if ((v1 & 0x100) != 0) {
            func_00152930((s32)s5, s0);
            v1 = *(s32 *)s1;
        }
    }

    if (s4 == 0 && (v1 & 2) != 0) {
        BtlTask_SetDead((s32)task);
        return;
    }
    if ((v1 & 1) != 0) {
        *(s32 *)s1 = v1 | 2;
    }
}
