#include "common.h"

u8 *func_001F3758(u8 *arg0);
s32 BtlScene_IsCharStopped(u8 *arg0);
void func_00129C38(u8 *arg0, u8 *arg1);
void func_0015E6A8(u8 *arg0, u8 *arg1, u8 *arg2, s32 arg3);

/* 0x0015EFB8: per-frame hit/flag update of a shot task (S = task+0x38, O = S+0xC0). */
void func_0015EFB8(u8 *task) {
    u8 *S = *(u8 **)(task + 0x38);
    u8 *own = *(u8 **)(func_001F3758(task) + 0x38);
    u8 *O = *(u8 **)(S + 0xC0);
    u16 fl;

    if (BtlScene_IsCharStopped(*(u8 **)O) != 0) {
        return;
    }
    fl = *(u16 *)(task + 8);
    if ((fl & 1) != 0) {
        func_00129C38(S + 0x90, task + 0x10);
        if ((*(u32 *)S & 0x20) == 0) {
            func_0015E6A8(*(u8 **)O, task, own, 1);
            *(u32 *)S |= 0x20;
        }
        fl = *(u16 *)(task + 8);
    }
    if ((fl & 4) != 0) {
        *(u32 *)S |= 1;
    }
}
