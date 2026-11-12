#include "common.h"

s32 BtlScene_IsCharStopped(u8 *arg0);
void func_00196048(u8 *arg0);
void func_001962A0(u8 *arg0, u8 *arg1, u8 *arg2);
void func_00151FB0(u8 *arg0);
void func_00195A90(u8 *arg0, u8 *arg1, u8 *arg2);
s32 func_00152200(u8 *arg0, u8 *arg1);
void func_001968B0(u8 *arg0);
void func_00196B28(u8 *arg0);
s32 BtlTask_SetDead(u8 *arg0);
s32 func_001961B8(u8 *arg0);

/* 0x00195E70: per-frame update of a task (S = task+0x38, O = S+0xAF0). flags at S+0xB70. */
s32 func_00195E70(u8 *task) {
    u8 *S = *(u8 **)(task + 0x38);
    u8 *O = *(u8 **)(S + 0xAF0);
    s32 r;
    s32 alive;
    u32 fl;

    r = BtlScene_IsCharStopped(*(u8 **)O);
    if (r != 0) {
        return r;
    }
    func_00196048(S);
    func_001962A0(*(u8 **)O, S + 0x7B0, S);
    func_00151FB0(S);
    func_00195A90(*(u8 **)O, task, *(u8 **)(S + 0xA00));
    alive = func_00152200(*(u8 **)(S + 0xA00), S) != 0;
    func_001968B0(task);
    fl = *(u32 *)(S + 0xB70);
    if (!alive && (fl & 8) != 0) {
        func_00196B28(S);
        fl = *(u32 *)(S + 0xB70) | 0x10;
        *(u32 *)(S + 0xB70) = fl;
    }
    if ((fl & 0x20) != 0) {
        return BtlTask_SetDead(task);
    }
    if ((fl & 0x200) != 0) {
        return fl & 0x200;
    }
    return func_001961B8(task);
}
