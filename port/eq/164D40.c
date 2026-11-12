#include "common.h"

extern f32 D_003847A4;

u8 *func_001F3758(u8 *arg0);
s32 BtlScene_IsCharStopped(u8 *arg0);
s32 EftShot_TestBits(u8 *arg0, s32 arg1);
s32 EftShot_GetAttrKind(u8 *arg0, u64 arg1);
void func_00152530(u8 *arg0, u8 *arg1);
void func_00151FB0(u8 *arg0);
s32 func_00152200(u8 *arg0, u8 *arg1);
s32 BtlTask_SetDead(u8 *arg0);
s32 func_00208DE8(u8 *a0, u8 *a1, s32 a2);
s32 func_0012D488(u8 *arg0, u8 *arg1, u8 *arg2, u8 *arg3);
void func_001C1258(u8 *arg0, s32 arg1);
u8 *func_001AE300(s32 arg0, u8 *arg1, s32 arg2, s32 arg3, f32 fa, f32 fb);
void func_001AE5E8(u8 *arg0);
s32 func_001C1420(u8 *arg0);
void func_001AE578(u8 *arg0, s32 arg1);
void func_001AE3E8(u8 *arg0, u8 *arg1, u8 *arg2, s32 arg3, f32 fa, f32 fb, f32 fc);
s32 func_001AE4D0(u8 *arg0);
void func_001C1460(u8 *arg0, s32 arg1);
s32 func_001C1210(u8 *arg0);
void func_001C1480(u8 *arg0, s32 arg1);
void func_001AE5C8(u8 *arg0);
void func_00164AA0(u8 *arg0, u8 *arg1, u8 *arg2);

/* 0x00164D40: per-frame update of a multi-part shot effect task. S = task+0x38; S+4 = part count, S+8 = current part,
   S+0xA80 = part effect pointers, S+0xA88 = part object pointers (index offset by 2: the array at 0xA80 is
   the one stored in phase 0), S+0x80 = shot O. task[1] = phase (jtbl_0036E4F0). */
s32 func_00164D40(u8 *task) {
    u8 sp[16];
    u8 *S = *(u8 **)(task + 0x38);
    u8 *O;
    u8 *own;
    u8 *tmp;
    u8 *vec;
    u8 **partsA = (u8 **)(S + 0xA80);
    u8 **partsB = (u8 **)(S + 0xA88);
    s32 wait = 0;
    s32 i;
    s32 cnt;
    s32 idx;
    s32 attr;
    u32 fl;
    s32 alive;
    s32 r;

    own = *(u8 **)(func_001F3758(task) + 0x38);
    O = *(u8 **)(S + 0x80);
    for (i = 0; i < *(s32 *)(S + 4); i++) {
        func_001C1258(partsB[i], 0);
    }
    r = BtlScene_IsCharStopped(*(u8 **)O);
    if (r != 0) {
        return r;
    }
    if ((*(u32 *)S & 0x40) == 0) {
        if (EftShot_TestBits(*(u8 **)O, 2) != 0) {
            task[1] = 0;
            *(u32 *)S |= 0x40;
        } else if (EftShot_TestBits(*(u8 **)O, 4) != 0) {
            task[1] = 2;
            *(u32 *)S |= 0x40;
        }
    }
    if ((*(u32 *)S & 0x40) != 0) {
        switch (task[1]) {
        case 0:
            if (EftShot_TestBits(*(u8 **)O, 2) != 0) {
                attr = EftShot_GetAttrKind(*(u8 **)O, 2);
                idx = *(s32 *)(S + 8);
                partsA[idx] = func_001AE300(attr, *(u8 **)O, 0, S[8] & 1, 9.0f, -1.0f);
                idx = *(s32 *)(S + 8);
                if (idx == *(s32 *)(S + 4) - 1) {
                    func_001AE5E8(partsA[idx]);
                    idx = *(s32 *)(S + 8);
                }
                func_001C1258(partsB[idx], 2);
                idx = *(s32 *)(S + 8);
                r = func_001C1420(partsB[idx]);
                func_001AE578(partsA[*(s32 *)(S + 8)], r + 16);
                *(s32 *)(S + 8) = *(s32 *)(S + 8) + 1;
                if (*(s32 *)(S + 8) == *(s32 *)(S + 4)) {
                    task[1] = 1;
                }
            }
            break;
        case 1:
            *(s32 *)(S + 8) = 0;
            wait = 1;
            break;
        case 2:
            __builtin_memset(sp, 0, 16);
            if (EftShot_TestBits(*(u8 **)O, 4) != 0) {
                vec = S + 0x20;
                attr = EftShot_GetAttrKind(*(u8 **)O, 4);
                func_00208DE8(*(u8 **)O, sp, attr);
                func_0012D488(O, vec, sp, *(u8 **)O);
                func_001AE3E8(partsA[*(s32 *)(S + 8)], O, vec, 1, *(f32 *)(S + 0xC), D_003847A4,
                              (f32)*(s32 *)*(u8 **)(O + 0x24) / 30.0f);
                func_001C1258(partsB[*(s32 *)(S + 8)], 4);
                *(s32 *)(S + 8) = *(s32 *)(S + 8) + 1;
                if (*(s32 *)(S + 8) == *(s32 *)(S + 4)) {
                    task[1] = 3;
                }
            }
            break;
        case 3:
        case 5:
            wait = 1;
            break;
        case 4:
            cnt = 0;
            for (i = 0; i < *(s32 *)(S + 4); i++) {
                if (func_001AE4D0(partsA[i]) == 0) {
                    cnt = cnt + 1;
                }
            }
            if (cnt == *(s32 *)(S + 4)) {
                cnt = 0;
                for (i = 0; i < *(s32 *)(S + 4); i++) {
                    func_001C1460(partsB[i], 1);
                    if (func_001C1210(partsB[i]) == 0) {
                        cnt = cnt + 1;
                    }
                }
                if (cnt == *(s32 *)(S + 4)) {
                    *(u32 *)S |= 1;
                    task[1] = 5;
                }
            }
            break;
        default:
            break;
        }
    }
    if (EftShot_TestBits(*(u8 **)O, 0x80) != 0) {
        *(u32 *)S |= 5;
    }
    for (i = 0; i < *(s32 *)(S + 4); i++) {
        func_001C1480(partsB[i], *(u32 *)S & 4);
        if ((*(u32 *)S & 4) != 0) {
            func_001AE5C8(partsA[i]);
        }
    }
    func_00152530(O, S + 0x830);
    tmp = S + 0x84;
    func_00151FB0(tmp);
    func_00164AA0(*(u8 **)O, task, own);
    alive = func_00152200(own, tmp) != 0;
    if (wait != 0) {
        task[1] = task[1] + 1;
    }
    fl = *(u32 *)S;
    if (alive == 0 && (fl & 2) != 0) {
        return BtlTask_SetDead(task);
    }
    if ((fl & 1) != 0) {
        *(u32 *)S = fl | 2;
    }
    return fl | 2;
}
