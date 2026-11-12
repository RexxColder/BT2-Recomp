#include "common.h"

extern s32 D_003B2654;
extern u8 D_003876A8;
void func_00261F38(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);

void func_00261080(s32 arg0, s32 arg1, s32 arg2) {
    if ((D_003B2654 & 0x100) == 0) {
        func_00261F38(D_003876A8, 0, arg0 & 0xFFFF, arg1, arg2, -1);
        if (D_003876A8 != 0) {
            D_003876A8 = 0;
        }
    }
}
