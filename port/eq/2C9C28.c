#include "common.h"

s32 func_002C2FF0(s32 arg0, s32 arg1, s32 arg2);
s32 func_002C9D88(s32 arg0, s32 arg1);
void func_002CBED8(s32 arg0);
s32 func_002E03A0(void);
s32 func_002DDC20(s32 arg0, s32 arg1, s32 arg2);
void func_002CA340(s32 arg0, s32 arg1);
s32 func_002D07B0(s32 arg0, s32 arg1);
void func_002E05A8(s32 arg0, s32 arg1, s32 arg2);
s32 func_002CE750(void);
void func_002C5B00(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 D_00399CD8 __attribute__((section(".data")));
extern s32 D_00399CDC __attribute__((section(".data")));
extern s32 D_00399CE0 __attribute__((section(".data")));
extern u8 func_002CA170[] __attribute__((section(".data")));

s32 func_002C9C28(s32 arg0) {
    s32 s2;
    s32 t;
    s32 v0;

    s2 = arg0 + 0x23A8;
    v0 = func_002D07B0(arg0, 5);
    if (v0 == 0) {
        return 0;
    }
    *(s32 *)(arg0 + 0x1FC0) = s2;
    v0 = func_002C9D88(arg0, s2);
    if (v0 != 0) {
        return v0;
    }
    func_002CBED8(arg0);
    t = func_002E03A0();
    if (t == 0) {
        return func_002C2FF0(0, (s32)0xFF000F0A, arg0);
    }
    if (func_002DDC20(t, (s32)func_002CA170, arg0) != 0) {
        func_002CA340(t, 0);
        return func_002C2FF0(0, (s32)0xFF000F0B, 0);
    }
    v0 = func_002D07B0(arg0, 0);
    func_002E05A8(t, 1, v0);
    v0 = func_002D07B0(arg0, 1);
    func_002E05A8(t, 2, v0);
    func_002E05A8(t, 6, *(s32 *)(arg0 + 0x38));
    *(s32 *)s2 = t;
    if (func_002CE750() != 0) {
        func_002C5B00(arg0, D_00399CD8, D_00399CDC, D_00399CE0);
    }
    return 0;
}
