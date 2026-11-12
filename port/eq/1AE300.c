#include "common.h"

s32 BtlTaskList_AddTail(s32 arg0, s32 arg1, s32 arg2);
void func_001B06D0(s32 arg0, s32 arg1, s32 arg2, f32 farg0);
void *memset(void *arg0, s32 arg1, u32 arg2);
extern u8 D_003427B8[] __attribute__((section(".data")));
extern f32 D_00384F28;
extern s32 D_0038785C;

void func_001AE300(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 fa, f32 fb) {
    s32 sp[24];
    u8 *b;
    f32 f20v;
    f32 f0;
    s32 s1;

    b = (u8 *)sp;
    f20v = fb;
    if (fb < 0.0f) {
        f20v = D_00384F28;
    }
    s1 = arg3 & 0xFF;
    memset(sp, 0, 0x60);
    func_001B06D0((s32)sp, arg1, arg0, fa);
    *(s32 *)(b + 0x20) = arg1;
    *(f32 *)(b + 0x2C) = fa;
    *(f32 *)(b + 0x30) = f20v;
    *(s32 *)(b + 0x24) = arg2;
    *(s32 *)(b + 0x28) = arg0;
    b[0x49] = (u8)s1;
    if (s1 != 0) {
        f0 = 0.5f;
    } else {
        f0 = -0.5f;
    }
    *(f32 *)(b + 0x34) = f0;
    *(s32 *)(b + 0x4C) = 0;
    BtlTaskList_AddTail(D_0038785C, (s32)D_003427B8, (s32)sp);
}
