#include "common.h"

extern u8 D_00387F00[];
extern u8 *D_00387F2C;
void func_002F4F88(s32 arg0, s32 arg1, s32 arg2);
s32 func_00101578(s32 arg0, s32 arg1);
s32 func_002F52A8(s32 arg0, s32 arg1);
s32 func_002F7040(s32 arg0, s32 arg1, s32 arg2);

/* 0x00101608: p = D_00387F00[arg0]; func_002F4F88(p, 0, arg4), func_002F4F88(p, 1, arg4), r = func_00101578(arg3, 1),
 * func_002F52A8(p, r). x = 100*arg1 + arg2; v1 = x + (0x74F3 if D_00387F2C->0x1008 bit 0 else 0x3E43);
 * sel = v1 < 0x33B2 ? 0 : 4 (word at D_00387F00+0x20+sel); tail func_002F7040(p, that, v1 < 0x33B2 ? v1 : v1 - 0x33B2). */
s32 func_00101608(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 p;
    s32 r;
    s32 x;
    s32 v1;
    s32 sel;
    s32 a2v;

    p = *(s32 *)(D_00387F00 + arg0 * 4);
    func_002F4F88(p, 0, arg4);
    func_002F4F88(*(s32 *)(D_00387F00 + arg0 * 4), 1, arg4);
    r = func_00101578(arg3, 1);
    func_002F52A8(*(s32 *)(D_00387F00 + arg0 * 4), r);
    x = arg1 * 100 + arg2;
    if (*(s32 *)(D_00387F2C + 0x1008) & 1) {
        v1 = x + 0x74F3;
    } else {
        v1 = x + 0x3E43;
    }
    sel = (v1 < 0x33B2) ? 0 : 4;
    a2v = (v1 < 0x33B2) ? v1 : v1 - 0x33B2;
    return func_002F7040(*(s32 *)(D_00387F00 + arg0 * 4), *(s32 *)(D_00387F00 + 0x20 + sel), a2v);
}
