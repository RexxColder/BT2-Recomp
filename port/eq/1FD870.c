#include "common.h"

/* outer count takes the object (a0 pass-through); inner count takes no argument */
s32 func_00211270();
s32 func_00211288(s32 arg0);
void func_001FD460(s32 arg0, s32 arg1);
void func_001FD548(s32 arg0, s32 arg1);
void func_001FD718(s32 arg0, s32 arg1);

void func_001FD870(s32 arg0) {
    s32 a0;
    s32 s1;
    s32 s2;
    s32 count;
    s32 t;

    a0 = arg0;
    s2 = 0;
    while (s2 < func_00211270(a0)) {
        s1 = 0;
        for (;;) {
            count = func_00211270();
            a0 = s2;
            if (!(s1 < count)) {
                break;
            }
            if (s2 != s1) {
                t = func_00211288(s2);
                func_001FD460(t, func_00211288(s1));
                t = func_00211288(s2);
                func_001FD548(t, func_00211288(s1));
                t = func_00211288(s2);
                func_001FD718(t, func_00211288(s1));
            }
            s1 += 1;
        }
        a0 = s2;
        s2 += 1;
    }
}
