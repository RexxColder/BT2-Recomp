#include "common.h"

s32 func_002D7588(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
s32 sscanf();
s64 __muldi3(s64 arg0, s64 arg1);
extern s32 D_0037AC78 __attribute__((section(".data")));
extern s32 D_0037AC88 __attribute__((section(".data")));
extern s32 D_0037AC90 __attribute__((section(".data")));
extern s32 D_0037AC98 __attribute__((section(".data")));
extern s32 D_0037ACA0 __attribute__((section(".data")));

void func_002D7470(s32 arg0, s32 arg1, s32 *arg2, s32 *arg3) {
    s32 sp0;
    s32 sp4;
    s64 sp8;
    s64 sp10;
    s32 sp18;
    s32 sp20;

    func_002D7588(arg0, (s32)&D_0037AC88, (s32)&D_0037AC78, (s32)&sp0, (s32)&sp4);
    if (sp0 == 0) {
        *arg2 = 0;
        *arg3 = 0x7FFFFFFF;
        return;
    }
    sscanf(sp0, (s32)&D_0037AC90, (s32)&sp8);
    func_002D7588(arg0, (s32)&D_0037AC98, (s32)&D_0037AC78, (s32)&sp0, (s32)&sp4);
    if (sp0 == 0) {
        *arg2 = 0x7FFFFFFF;
        return;
    }
    sscanf(sp0 + (s32)__muldi3(sp8, (s64)arg1), (s32)&D_0037ACA0, (s32)&sp10, (s32)&sp18, (s32)&sp20);
    *arg2 = sp18;
    *arg3 = sp20;
}
