#include "common.h"

void func_001F4288(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 farg0);
void func_001F42B8(s32 arg0, s32 arg1);
void func_00147FE8(s32 *arg0);
extern f32 D_00385778;
extern f32 D_0038577C;

void func_001F58C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 farg0) {
    s32 sp[8];

    sp[0] = 0;
    sp[1] = 4;
    sp[2] = 0;
    ((f32 *)sp)[3] = D_00385778;
    ((f32 *)sp)[4] = 100.0f;
    ((f32 *)sp)[5] = D_0038577C;
    sp[6] = 0;
    /* f12 is never written here: it is the function's own float parameter, passed through */
    func_001F4288(arg1, arg1, arg2, arg3, farg0);
    func_001F42B8(arg1, 1);
    func_00147FE8(sp);
}
