#include "m2c_macros.h"

extern void func_00260260(s32 arg0, s32 arg1);
extern void func_00260340(s32 arg0);
extern void func_00260490(s32 arg0);

void func_002605A0(s32 arg0, s32 arg1) {
    if (*(s32 *)(arg0 + 0x744) != 0) {
        switch (arg1) {
        case 0:
            func_00260260(arg0, arg0 + 0xEF0);
            break;
        case 1:
            func_00260340(arg0 + 0xEF0);
            break;
        case 2:
            func_00260490(arg0);
            break;
        }
    }
}
