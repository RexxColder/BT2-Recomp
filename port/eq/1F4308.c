#include "common.h"

s32 BtlTaskList_AddTail(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_001F4300(s32 arg0, s32 arg1);
s32 func_001F49E8(s32 arg0, s32 arg1);
extern s32 D_00387920;

void func_001F4308(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 sp[4];
    s32 v;
    s32 t;
    u8 *p;
    s32 a1v;

    sp[0] = 0;
    v = func_001F4300(arg0, arg1);
    t = func_001F49E8(v, (s32)sp);
    if (t == 0) {
        return;
    }
    p = *(u8 **)(D_00387920 + arg1 * 4 + 4);
    if (p == NULL) {
        return;
    }
    a1v = *(s32 *)(t + arg1 * 12 + 4);
    if (a1v == 0) {
        return;
    }
    v = *(s32 *)(p + 0x24);
    if (v == 0) {
        return;
    }
    BtlTaskList_AddTail(v, a1v, arg0, arg3);
}
