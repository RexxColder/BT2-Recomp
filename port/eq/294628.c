#include "common.h"

void func_00312650(void *arg0, void *arg1, void *arg2, f32 farg0, f32 farg1);
void func_00312680(f32 farg0, void *arg1, void *arg2);
void func_00312638(void *arg0, void *arg1, void *arg2);

void ColTri_GetPoint(void *arg0, void *arg1, f32 farg0, f32 farg1) {
    s32 buf[8];
    void *sp;
    void *sp10;

    sp = buf;
    sp10 = &buf[4];
    func_00312650(sp, (u8 *)arg1 + 0x10, arg1, farg0, farg1);
    func_00312680(farg0, sp, sp);
    func_00312638(sp, sp, arg1);
    func_00312650(sp10, (u8 *)arg1 + 0x20, arg1, 0.0f, 0.0f);
    func_00312680(farg1, sp10, sp10);
    func_00312638(arg0, sp, sp10);
}
