#include "common.h"

s32 func_0020C360(s32 arg0);
s32 func_0020C3B8(s32 arg0);
s32 func_0020C410(s32 arg0);
s32 func_0020C468(s32 arg0);
s32 func_0020C4C0(s32 arg0);
s32 func_0020C518(s32 arg0);

s32 func_00108DC0(s32 arg0, s32 arg1, s32 arg2) {
    s32 a2 = 0;

    if ((u32)arg0 < 8) {
        switch (arg0) {
        case 0:
            if (arg1 == 0) {
                a2 = func_0020C360(arg2);
            } else if (arg1 == 1) {
                a2 = func_0020C3B8(arg2);
            }
            break;
        case 1:
            if (arg1 == 0) {
                a2 = func_0020C410(arg2);
            } else if (arg1 == 1) {
                a2 = func_0020C468(arg2);
            }
            break;
        case 2:
            a2 = func_0020C4C0(arg2);
            break;
        case 7:
            a2 = func_0020C518(arg2);
            break;
        default:
            break;
        }
    }
    return a2;
}
