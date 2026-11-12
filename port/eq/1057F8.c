#include "common.h"

/* GUESS arity: func_00105718 gets the object pointer in a0; ctx.h says void(void) */
void func_00105718(s32 arg0);
void func_00105500(s32 arg0, s32 arg1);
extern void *D_003876A0;
extern s32 *D_003876B4;

void func_001057F8(void) {
    s32 idx;
    u8 *base;

    if (*(s32 *)((u8 *)D_003876A0 + 0xB8) != 6) {
        idx = D_003876B4[0];
        if (idx == 3) {
            func_00105718((s32)D_003876B4);
            idx = D_003876B4[0];
            base = *(u8 **)((u8 *)D_003876B4 + 0x104);
        } else {
            base = *(u8 **)((u8 *)D_003876B4 + 0x104);
        }
    } else {
        idx = D_003876B4[0];
        base = *(u8 **)((u8 *)D_003876B4 + 0x104);
    }
    func_00105500(*(s32 *)(base + idx * 0x14 + 4), idx);
}
