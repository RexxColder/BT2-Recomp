#include "common.h"

void func_0019A670(s32 arg0, s32 arg1);
void func_0019A708(s32 arg0, s32 arg1);
void func_0019A798(s32 arg0, s32 arg1);
extern s32 gEftGlow;

s32 EftGlow_Request(s32 arg0, s32 arg1) {
    if (gEftGlow == 0) {
        return 0;
    }
    if (arg1 == 1) {
        func_0019A708(arg0, arg1);
    } else if (arg1 == 0) {
        func_0019A670(arg0, arg1);
    } else if (arg1 == 2) {
        func_0019A798(arg0, arg1);
    }
    return 1;
}
