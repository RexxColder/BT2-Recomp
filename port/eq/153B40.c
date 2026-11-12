#include "common.h"

u8 *func_001F3758(void *a0);
s32 BtlScene_IsCharStopped(s32 id);
void func_00152530(u8 *owner, u8 *dst);
s32 EftShot_TestBits(s32 id, s32 bits);
s32 func_00208DE8(s32 a0, s32 a1, s32 a2);
void func_00129C28(u8 *dst, u8 *src);
s32 func_0012D3A0(u8 *arg0, u8 *arg1, s32 arg2);
f32 func_0020A068(s32 arg0);
s32 func_001539D8(u8 *task);
void func_00151FB0(u8 *arg0);
void func_001535A0(s32 a0, u8 *a1, u8 *a2, u8 a3);
s32 func_00152200(u8 *arg0, u8 *arg1);
s32 BtlTask_SetDead(u8 *task);
void func_00152930(u8 *a0, u8 *a1);
void func_001533D8(u8 *task);

/* Per-frame update of a shot task: state byte task[1] (0..5) drives which fighter node is sampled. */
void func_00153B40(u8 *task) {
    u8 q[16];
    u8 *other;
    u8 *eff;
    u8 *otherEff;
    u8 *owner;
    s32 id;
    s32 advance = 0;
    s32 busy;
    s32 hit;
    s32 flags;
    u8 *hitBuf;

    other = func_001F3758(task);
    eff = *(u8 **)(task + 0x38);
    otherEff = *(u8 **)(other + 0x38);
    owner = *(u8 **)(eff + 0xA0);
    id = *(s32 *)owner;
    if (BtlScene_IsCharStopped(id) != 0) {
        return;
    }
    func_00152530(owner, eff + 0x850);
    if ((*(u32 *)eff & 0x80) == 0) {
        if (EftShot_TestBits(*(s32 *)owner, 2) != 0) {
            task[1] = 0;
            *(u32 *)eff |= 0x80;
        } else if (EftShot_TestBits(*(s32 *)owner, 4) != 0) {
            task[1] = 2;
            *(u32 *)eff |= 0x80;
        }
    }
    if ((*(u32 *)eff & 0x80) != 0) {
        switch (task[1]) {
        case 0:
            if (EftShot_TestBits(*(s32 *)owner, 2) != 0) {
                *(s32 *)(eff + 4) = *(s32 *)(eff + 0x860);
                func_00208DE8(*(s32 *)owner, (s32)q, *(s32 *)(eff + 0x860));
                func_00129C28(eff + 0x30, q);
                func_0012D3A0(eff + 0x20, eff + 0x30, *(s32 *)owner);
                task[1] = 1;
            }
            break;
        case 1:
        case 3:
        case 5:
            advance = 1;
            break;
        case 2: {
            f32 v = func_0020A068(*(s32 *)owner);
            *(f32 *)(eff + 0x1C) = v;
            *(f32 *)(eff + 0x18) = *(f32 *)(eff + 0x14) * (v + 1.0f);
            func_00208DE8(*(s32 *)owner, (s32)q, *(s32 *)(eff + 4));
            func_00129C28(eff + 0x30, q);
            if (EftShot_TestBits(*(s32 *)owner, 0x40) != 0) {
                *(s32 *)(eff + 0xC) = *(s32 *)(eff + 0x9A0);
                func_00208DE8(*(s32 *)owner, (s32)q, *(s32 *)(eff + 0x9A0));
                func_00129C28(eff + 0x50, q);
                *(u32 *)eff |= 0x40;
            }
            if (EftShot_TestBits(*(s32 *)owner, 4) != 0) {
                *(s32 *)(eff + 8) = *(s32 *)(eff + 0x8A0);
                func_00208DE8(*(s32 *)owner, (s32)q, *(s32 *)(eff + 0x8A0));
                func_00129C28(eff + 0x40, q);
                func_00129C28(eff + 0x60, eff + 0x40);
                func_00129C28(eff + 0x70, eff + 0x60);
                task[1] = 3;
            }
            break;
        }
        case 4:
            func_00208DE8(*(s32 *)owner, (s32)q, *(s32 *)(eff + 8));
            func_00129C28(eff + 0x40, q);
            if (EftShot_TestBits(*(s32 *)owner, 8) != 0) {
                *(u32 *)eff |= 9;
                task[1] = 5;
            }
            break;
        default:
            break;
        }
    }
    busy = func_001539D8(task);
    if ((*(u32 *)eff & 0x200) != 0 && busy == 0) {
        *(u32 *)eff |= 1;
    }
    hitBuf = eff + 0xA4;
    if (EftShot_TestBits(*(s32 *)owner, 0x80) != 0) {
        flags = *(s32 *)eff;
        if ((flags & 8) == 0) {
            *(s32 *)eff = flags | 4;
            flags |= 4;
        }
        *(s32 *)eff = flags | 1;
    }
    func_00151FB0(hitBuf);
    func_001535A0(*(s32 *)owner, task, otherEff, 0);
    hit = func_00152200(otherEff, hitBuf) != 0;
    if (advance != 0) {
        task[1] += 1;
    }
    flags = *(s32 *)eff;
    if (busy == 0 && hit == 0 && (flags & 2) != 0) {
        BtlTask_SetDead(task);
        return;
    }
    if ((flags & 1) != 0) {
        *(s32 *)eff = flags | 2;
    } else if ((*(u32 *)(*(u8 **)(owner + 0x20) + 0x30) & 1) != 0 && (flags & 0x10) != 0) {
        func_00152930(otherEff, hitBuf);
        func_001533D8(task);
    }
}
