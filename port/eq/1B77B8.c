#include "common.h"

s32 BtlTaskList_AddTail(s32 arg0, s32 arg1, s32 arg2);
extern u8 *D_00387880;
extern u8 D_00342890[] __attribute__((section(".data")));
extern u8 D_003428A8[] __attribute__((section(".data")));
extern u8 D_003428C0[] __attribute__((section(".data")));

void func_001B77B8(u8 *arg0) {
    s64 loc[16];
    u8 *sp = (u8 *)loc;
    s32 sel;
    s32 r;
    s32 a0v;
    s32 a1v;
    s32 i;

    for (i = 0; i < 16; i++) {
        loc[i] = *(s64 *)(arg0 + i * 8);
    }
    *(s32 *)(sp + 0x74) = 0;
    *(s32 *)(sp + 0x68) = (s32)(D_00387880 + 0x10);
    sel = *(s32 *)(sp + 0x64);
    if (sel == 1) {
        a0v = *(s32 *)D_00387880;
        a1v = (s32)D_003428A8;
    } else if (sel == 0) {
        a0v = *(s32 *)D_00387880;
        a1v = (s32)D_00342890;
    } else if (sel == 2) {
        a0v = *(s32 *)D_00387880;
        a1v = (s32)D_003428C0;
    } else {
        return;
    }
    r = BtlTaskList_AddTail(a0v, a1v, (s32)sp);
    *(s32 *)(sp + 0x70) = r;
    *(s32 *)(arg0 + 0x70) = r;
}
