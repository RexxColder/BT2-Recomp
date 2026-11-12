#include "common.h"
#include "sys/gfx_ot.h"

void func_00278D78(void);
s32 func_0028BAA8(s32 arg0);

void func_00279220(void) {
    s32 i;
    s32 off;
    s32 t;
    s32 v;

    i = 0;
    off = 0x20;
    func_00278D78();
    do {
        t = i;
        i += 1;
        v = func_0028BAA8(0x30060);
        *(s32 *)((u8 *)gOt + off) = v;
        off += 4;
        Ot_BuildHeads(t);
    } while (i < 2);
}
