#include "common.h"

s32 func_00174A70(s32 arg0);
s32 func_00174BB8(s32 arg0);
s32 func_00174BF8(s32 arg0);
s32 func_00174C38(s32 arg0);
s32 BtlTask_SetDead(s32 arg0);
extern u8 *gEftTechEvt;

/* 0x00174598 (EftTechEvtTask_UpdateNormal): one update of a tech-event task. The task's record (+0x38) holds a
   counter (+0x14), two flag words (+0x10 and the table row at gEftTechEvt+4 + 16 * index), and a sub-record
   whose +0x20 pointer selects the branch. Bits of func_00174A70's result set row flags 0x2 .. 0x40, and the task
   is set dead (flag 0x80 or 0x8) when a test fails. The asm tail-calls BtlTask_SetDead and returns its value
   (or the row flag word); ctx says void, so this is void and the value is not returned. */
void EftTechEvtTask_UpdateNormal(u8 *task) {
    u8 *rec;
    u8 *p;
    u8 *s0;
    s32 flags;
    s32 v11;
    s32 r;

    rec = *(u8 **)(task + 0x38);
    p = *(u8 **)rec;
    s0 = *(u8 **)(gEftTechEvt + 4) + 16 * *(s32 *)p;

    flags = func_00174A70((s32)rec);
    *(s32 *)(rec + 0x14) += 1;

    if ((flags & 0x200) != 0) {
        *(s32 *)s0 |= 2;
        *(s32 *)(rec + 0x10) |= 2;
    }
    if ((flags & 0x400) != 0) {
        *(s32 *)s0 |= 4;
        if (*(s32 *)(*(u8 **)(p + 0x20) + 4) != 0) {
            *(s32 *)(rec + 0x10) |= 4;
        }
    }
    if ((flags & 0x800) != 0) {
        *(s32 *)s0 |= 8;
        (void)BtlTask_SetDead((s32)task);
        return;
    }

    if (*(s32 *)(*(u8 **)(p + 0x20) + 4) != 0) {
        if (func_00174C38(*(s32 *)p) == 0 || func_00174BB8(*(s32 *)p) != 0) {
            *(s32 *)s0 |= 0x80;
            (void)BtlTask_SetDead((s32)task);
            return;
        }
        v11 = flags & 0x1000;
    } else {
        if (func_00174BB8(*(s32 *)p) != 0) {
            *(s32 *)s0 |= 0x80;
            (void)BtlTask_SetDead((s32)task);
            return;
        }
        if (func_00174BF8(*(s32 *)p) == 0) {
            *(s32 *)s0 |= 8;
            (void)BtlTask_SetDead((s32)task);
            return;
        }
        v11 = flags & 0x1000;
    }

    if (v11 != 0) {
        *(s32 *)s0 |= 0x10;
    }
    if ((flags & 0x2000) != 0) {
        *(s32 *)s0 |= 0x20;
    }
    if ((flags & 0x4000) != 0) {
        *(s32 *)s0 |= 0x40;
    }
    r = *(s32 *)(rec + 0x8);
    if (r <= 0) {
        r = *(s32 *)s0 | 8;
        *(s32 *)s0 = r;
    }
}
