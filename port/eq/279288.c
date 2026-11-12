#include "common.h"
#include "sys/gfx_ot.h"

void func_0028BB60(s32 arg0);

void func_00279288(void) {
    s32 off;
    s32 i;
    s32 v;

    off = 0x20;
    i = 1;
    do {
        v = *(s32 *)((u8 *)gOt + off);
        if (v != 0) {
            func_0028BB60(v);
            *(s32 *)((u8 *)gOt + off) = 0;
        }
        i -= 1;
        off += 4;
    } while (i >= 0);
}
