#include "common.h"

void func_00129C38(u8 *arg0, u8 *arg1);
void EftRibbon_SetEnd(u8 *ribbon, u8 *pos, s32 arg2);
void EftRibbon_Stop(u8 *ribbon);
void EftRibbon_StopAndKill(u8 *ribbon);
void func_001AA848(u8 *src, u8 *dst);
void func_001AA4B0(u8 *task);

/* 0x001AB9E8: task state change handler (S = task+0x38). task+4 bits 0x3F = finish, 0xC0 = turn. S+0xD4 = ribbon. */
void func_001AB9E8(u8 *task) {
    u8 *S = *(u8 **)(task + 0x38);
    u32 ev = *(u32 *)(task + 4);
    u32 fl;

    if ((ev & 0x3F) != 0) {
        fl = *(u32 *)S | 0x10;
        *(s32 *)(S + 0xC) = 0;
        *(u32 *)S = fl;
        if ((fl & 0x100) == 0) {
            func_00129C38(S + 0x90, task + 0x10);
            *(u32 *)S |= 0x100;
        }
        if (*(u8 **)(S + 0xD4) != 0) {
            EftRibbon_SetEnd(*(u8 **)(S + 0xD4), S + 0x90, 1);
            EftRibbon_Stop(*(u8 **)(S + 0xD4));
            *(s32 *)(S + 0xD4) = 0;
        }
        return;
    }
    if ((ev & 0xC0) == 0) {
        return;
    }
    if ((*(u32 *)S & 8) != 0) {
        return;
    }
    func_001AA848(task, S);
    fl = *(u32 *)S;
    *(f32 *)(S + 0x90) = *(f32 *)(task + 0x10);
    *(f32 *)(S + 0x94) = *(f32 *)(task + 0x14);
    *(f32 *)(S + 0x98) = *(f32 *)(task + 0x18);
    if ((fl & 0x80) == 0) {
        if (*(u8 **)(S + 0xD4) != 0) {
            EftRibbon_StopAndKill(*(u8 **)(S + 0xD4));
            *(s32 *)(S + 0xD4) = 0;
        }
        func_001AA4B0(task);
        fl = *(u32 *)S;
    }
    *(u32 *)S = fl | 0x200;
    *(u32 *)(task + 4) &= ~0xC0u;
}
