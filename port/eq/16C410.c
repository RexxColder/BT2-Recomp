#include "common.h"

u8 *func_001F3758(u8 *arg0);
s32 BtlScene_IsCharStopped(u8 *arg0);
s32 EftShot_TestBits(u8 *arg0, s32 arg1);
void func_00152530(u8 *arg0, u8 *arg1);
void func_00151FB0(u8 *arg0);
s32 func_00152200(u8 *arg0, u8 *arg1);
s32 BtlTask_SetDead(u8 *arg0);
void EftCam_StopIfRunning(void);
void func_00129BB8(u8 *arg0, u8 *arg1, f32 farg0);
void func_0012D3A0(u8 *arg0, u8 *arg1, u8 *arg2);
s32 func_00208DE8(u8 *a0, u8 *a1, s32 a2);
void func_0020D3B0(u8 *arg0, f32 farg0, u8 *arg1);
s32 func_0016CA20(u8 *arg0, s32 arg1, u8 *arg2);
void func_0016CAE0(u8 *arg0, s32 arg1);
void func_0016B6D8(u8 *arg0);
void func_0016CBB8(u8 *arg0);
void func_0016CD90(u8 *arg0);
void func_0016CEA0(u8 *arg0);
s32 func_0020A758(u8 *arg0);
s32 func_0016B2E8(u8 *arg0);
void func_0016BED8(u8 *arg0);
void func_0016BE40(u8 *arg0);
void func_0016B540(u8 *arg0, u8 *arg1, u8 *arg2);
void func_0016B908(u8 *arg0);
void func_0016B9A0(u8 *arg0);
void func_0016BB88(u8 *arg0);
void func_0016BD28(u8 *arg0);

/* 0x0016C410: per-frame update of a shot effect task (S = task+0x38, O = S+0xB0). task[1] = phase (jtbl_0036E620).
   In phase 4 the shot kind (word at O->0x20->0) selects the handler. */
s32 func_0016C410(u8 *task) {
    u8 sp[16];
    u8 *S = *(u8 **)(task + 0x38);
    u8 *O;
    u8 *own;
    u8 *prm;
    s32 wait = 0;
    s32 r;
    s32 kind;
    s32 dead = 0;
    s32 alive = 0;
    u32 fl;

    own = *(u8 **)(func_001F3758(task) + 0x38);
    O = *(u8 **)(S + 0xB0);
    r = BtlScene_IsCharStopped(*(u8 **)O);
    if (r != 0) {
        return r;
    }
    func_0016BE40(task);
    if ((*(u32 *)S & 0x80) != 0) {
        *(s32 *)(S + 0x18) = *(s32 *)(S + 0x18) + 1;
    }
    func_00152530(O, S + 0x860);
    switch (task[1]) {
    case 0:
        if (EftShot_TestBits(*(u8 **)O, 2) != 0) {
            r = func_0016CA20(*(u8 **)O, 2, O);
            *(s32 *)(S + 4) = r;
            func_00208DE8(*(u8 **)O, S + 0x40, r);
            func_0012D3A0(S + 0x30, S + 0x40, *(u8 **)O);
            task[1] = 1;
        }
        break;
    case 1:
    case 3:
    case 5:
        wait = 1;
        break;
    case 2:
        func_00208DE8(*(u8 **)O, S + 0x40, *(s32 *)(S + 4));
        if (EftShot_TestBits(*(u8 **)O, 0x40) != 0) {
            r = func_0016CA20(*(u8 **)O, 0x40, O);
            *(s32 *)(S + 0xC) = r;
            func_00208DE8(*(u8 **)O, S + 0x60, r);
            *(u32 *)S |= 0x20;
        }
        if (EftShot_TestBits(*(u8 **)O, 4) != 0) {
            func_0016B6D8(task);
            task[1] = 3;
        }
        break;
    case 4:
        prm = *(u8 **)(O + 0x20);
        if ((*(u32 *)(prm + 0x30) & 0x10) != 0) {
            func_00129BB8(sp, S + 0x30, -1.0f);
            func_0020D3B0(*(u8 **)O, 4.0f, sp);
            prm = *(u8 **)(O + 0x20);
        }
        kind = *(s32 *)prm;
        switch (kind) {
        case 62:
        case 151:
        case 155:
        case 156:
        case 157:
        case 158:
        case 163:
        case 184:
        case 309:
        case 342:
        case 344:
        case 356:
            func_0016CAE0(task, 0);
            break;
        case 132:
        case 357:
            func_0016CBB8(task);
            break;
        case 306:
            func_0016CD90(task);
            break;
        case 345:
        case 346:
        case 353:
            func_0016CEA0(task);
            break;
        default:
            break;
        }
        if (EftShot_TestBits(*(u8 **)O, 8) != 0) {
            *(u32 *)S |= 9;
            task[1] = 5;
        }
        break;
    default:
        break;
    }
    if (EftShot_TestBits(*(u8 **)O, 0x80) != 0) {
        fl = *(u32 *)S;
        if ((fl & 8) == 0) {
            fl = fl | 4;
        }
        *(u32 *)S = fl | 1;
    }
    dead = func_0016B2E8(task);
    func_0016BED8(task);
    if (own[0x1E80] != 0) {
        func_00151FB0(S + 0xB4);
        func_0016B540(*(u8 **)O, task, own);
        alive = func_00152200(own, S + 0xB4) != 0;
    }
    if (func_0020A758(*(u8 **)O) != 0) {
        func_0016B908(task);
        func_0016B9A0(task);
        func_0016BB88(task);
        func_0016BD28(task);
    }
    if (wait != 0) {
        task[1] = task[1] + 1;
    }
    fl = *(u32 *)S;
    if (dead == 0 && alive == 0 && (fl & 2) != 0) {
        return BtlTask_SetDead(task);
    }
    if ((fl & 1) == 0) {
        return fl & 0x80;
    }
    if ((fl & 0x80) != 0) {
        EftCam_StopIfRunning();
        fl = *(u32 *)S & ~0x80u;
        *(u32 *)S = fl;
    }
    *(u32 *)S = fl | 2;
    return fl | 2;
}
