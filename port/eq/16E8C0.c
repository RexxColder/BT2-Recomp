#include "common.h"

typedef struct { u64 lo, hi; } q128;

extern u64 D_0036E650[4];

s32 func_001F3758(void *a0);
void func_00126DE0(u8 *arg0);
s32 func_0020AB90(u32 arg0);
s32 func_00208DE8(s32 a0, s32 a1, s32 a2);
void func_00129C28(q128 *arg0, q128 *arg1);
s32 func_0012D3A0(u8 *arg0, s32 arg1, s32 arg2);
void Vec3_Scale(u8 *arg0, u8 *arg1, f32 farg0);
void Vec4_Scale(u8 *arg0, u8 *arg1, f32 farg0);
void func_0020D3B0(s32 arg0, f32 farg0, s32 arg1);
s32 func_0020B3D0(u32 arg0);
void func_0019F8D0();
void func_001DBF28();
s32 func_0016E588(s32 arg0);
void func_00152260(s32 arg0, s32 arg1);
void func_00151FB0(u8 *arg0);
void func_0016D9A0(s32 arg0, u8 *arg1, s32 *arg2);
s32 func_00152200(u8 *arg0, s32 arg1);
s32 func_0020A758(s32 arg0);
void func_0016E670(u8 *arg0);
void func_00152930(s32 arg0, s32 arg1);
s32 BtlScene_IsCharStopped(s32 arg0);
s32 EftShot_TestBits(s32 arg0, s32 arg1);
s32 BtlTask_SetDead(s32 arg0);
void EftCam_StopIfRunning(void);

#define P(x) ((s32)(u32)(x))

void func_0016E8C0(u8 *task) {
    q128 tmp;
    q128 vec;
    s32 hit[3];
    u64 col[4];
    s32 ev[12];
    f32 fx[4];
    s32 advance = 0;
    u8 *world = (u8 *)(u32)func_001F3758(task);
    u8 *st = *(u8 **)(task + 0x38);
    u8 *gs = *(u8 **)(world + 0x38);
    s32 **objp = (s32 **)(st + 0xB0);
    s32 *obj = *objp;
    s32 stopped, gotDead, ground, i;
    u32 flags;

    stopped = BtlScene_IsCharStopped(obj[0]);
    if (stopped != 0) {
        return;
    }
    if (func_0020AB90(obj[0]) != 0 && (*(u32 *)st & 0x100) == 0) {
        hit[0] = *(s32 *)(gs + 0x1E80);
        hit[1] = obj[0];
        hit[2] = **(s32 **)(obj + 8);
        func_00126DE0((u8 *)hit);
        *(u32 *)st |= 0x100;
    }

    switch (task[1]) {
    case 0:
        if (EftShot_TestBits(obj[0], 2) != 0) {
            *(s32 *)(st + 4) = *(s32 *)(st + 0x870);
            func_00208DE8(obj[0], P(&tmp), *(s32 *)(st + 4));
            func_00129C28((q128 *)(st + 0x40), &tmp);
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
        func_00208DE8(obj[0], P(&tmp), *(s32 *)(st + 4));
        func_00129C28((q128 *)(st + 0x40), &tmp);
        if (EftShot_TestBits(obj[0], 0x40) != 0) {
            *(s32 *)(st + 0xC) = *(s32 *)(st + 0x9B0);
            func_00208DE8(obj[0], P(&tmp), *(s32 *)(st + 0xC));
            func_00129C28((q128 *)(st + 0x60), &tmp);
            *(u32 *)st |= 0x20;
        }
        if (EftShot_TestBits(obj[0], 4) != 0) {
            *(s32 *)(st + 8) = *(s32 *)(st + 0x8B0);
            func_00208DE8(obj[0], P(&tmp), *(s32 *)(st + 8));
            func_00129C28((q128 *)(st + 0x50), &tmp);
            func_00129C28((q128 *)(st + 0x70), (q128 *)(st + 0x50));
            func_00129C28((q128 *)(st + 0x80), (q128 *)(st + 0x70));
            func_00129C28((q128 *)(st + 0x90), (q128 *)(st + 0x80));
            func_0012D3A0(st + 0x30, P(st + 0x80), obj[0]);
            Vec3_Scale(st + 0xA0, st + 0x30, *(f32 *)(st + 0x18));
            *(u32 *)st |= 0x80;
            task[1] = 3;
        }
        break;
    case 4:
        if ((*(u32 *)(*(u8 **)(obj + 8) + 0x30) & 0x10) != 0) {
            Vec4_Scale((u8 *)&vec, st + 0x30, -1.0f);
            func_0020D3B0(obj[0], 4.0f, P(&vec));
        }
        func_00208DE8(obj[0], P(&tmp), *(s32 *)(st + 8));
        func_00129C28((q128 *)(st + 0x50), &tmp);
        func_00129C28((q128 *)(st + 0x90), (q128 *)(st + 0x80));
        if (EftShot_TestBits(func_0020B3D0(obj[0]), 0x40) != 0) {
            for (i = 0; i < 4; i++) {
                col[i] = D_0036E650[i];
            }
            func_0019F8D0(col);
            fx[0] = *(f32 *)(st + 0x50);
            fx[1] = *(f32 *)(st + 0x54);
            fx[2] = *(f32 *)(st + 0x58);
            fx[3] = 1.0f;
            ev[0] = *(s32 *)&fx[0];
            ev[1] = *(s32 *)&fx[1];
            ev[2] = *(s32 *)&fx[2];
            ev[3] = *(s32 *)&fx[3];
            ev[4] = obj[0];
            ev[5] = 0x47;
            ev[6] = 1;
            ev[7] = 1;
            ev[8] = 0;
            ev[9] = 0;
            ev[10] = 0;
            ev[11] = 0;
            func_001DBF28(ev);
            ev[8] = 3;
            func_001DBF28(ev);
            ev[8] = 10;
            func_001DBF28(ev);
            ev[8] = 14;
            func_001DBF28(ev);
            ev[8] = 21;
            func_001DBF28(ev);
        }
        if (EftShot_TestBits(obj[0], 8) != 0) {
            *(u32 *)st |= 9;
            task[1] = 5;
        }
        break;
    default:
        break;
    }

    gotDead = func_0016E588(P(task));
    if (EftShot_TestBits(obj[0], 0x80) != 0) {
        flags = *(u32 *)st;
        if ((flags & 8) == 0) {
            *(u32 *)st = flags | 4;
        }
        *(u32 *)st |= 1;
    }
    func_00152260(obj[0], P(st + 0x860));
    func_00151FB0(st + 0xB4);
    func_0016D9A0(obj[0], task, (s32 *)gs);
    ground = func_00152200(gs, P(st + 0xB4)) != 0;
    if (func_0020A758(obj[0]) != 0) {
        func_0016E670(task);
    }
    if (advance != 0) {
        task[1]++;
    }
    flags = *(u32 *)st;
    if ((*(u32 *)(*(u8 **)(obj + 8) + 0x30) & 1) != 0 && (flags & 0x80) != 0) {
        func_00152930(P(gs), P(st + 0xB4));
        flags = *(u32 *)st;
    }
    if (gotDead == 0 && ground == 0 && (flags & 2) != 0) {
        BtlTask_SetDead(P(task));
        return;
    }
    if ((flags & 1) != 0) {
        if ((flags & 0x100) != 0) {
            EftCam_StopIfRunning();
            flags = *(u32 *)st;
        }
        *(u32 *)st = flags | 2;
    }
}
