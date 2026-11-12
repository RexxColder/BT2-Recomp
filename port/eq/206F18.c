#include "common.h"

/* 0x00206F18: idx = a0->+0x142C; if (idx < 0 || !(idx < *(s32 *)(D_00387A40 + 0xC))) return;
   func_002070D8(a0, p + 0x9A0, p + 0x9B0) with p = a0->+0x1530; tail func_00260A50(*(D_00387A40 + 8) + idx * 0x1520). */
extern u8 *D_00387A40;
void func_002070D8(s32 arg0, s32 arg1, s32 arg2);
void func_00260A50(s32 arg0);

void func_00206F18(s32 a0) {
    u8 *p;
    s32 idx;

    idx = *(s32 *)((u8 *)a0 + 0x142C);
    if (idx < 0) {
        return;
    }
    if (!(idx < *(s32 *)(D_00387A40 + 0xC))) {
        return;
    }
    p = *(u8 **)((u8 *)a0 + 0x1530);
    func_002070D8(a0, (s32)(p + 0x9A0), (s32)(p + 0x9B0));
    idx = *(s32 *)((u8 *)a0 + 0x142C);
    func_00260A50(*(s32 *)(D_00387A40 + 0x8) + idx * 0x1520);
}
