#include "common.h"

s32 func_00129C28(s32 arg0, s32 arg1);

void func_001804A0(u8 *arg0, s32 arg1) {
    u8 *p;
    s32 i;
    s32 v;

    p = arg0;
    for (i = 0x1D; i >= 0; i--) {
        v = *(s32 *)p;
        p += 4;
        if (v != 0) {
            func_00129C28(*(s32 *)((u8 *)v + 0x38), arg1);
        }
    }
}
